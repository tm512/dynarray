/* [c] 2011 by tm512 (Kyle Davis)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "dynarray.h"

// Create the array on the heap, initialize.
dynarray_t *dynarray_create (unsigned int max, unsigned int size, unsigned char resize)
{
	dynarray_t *ret = (dynarray_t *) malloc (sizeof (dynarray_t));

	if (!ret)
		return NULL;

	memset (ret, 0, sizeof (dynarray_t));

	ret->e_size = size;
	ret->e_max = max;
	ret->resize = resize;
	ret->index = (void **) malloc (max * sizeof (void *));
	ret->elements = malloc (size * max);

	if (!ret->index || !ret->elements)
	{
		dynarray_delete (&ret);
		return NULL;
	}

	memset (ret->index, 0, max * sizeof (void *));
	memset (ret->elements, 0, size * max);

	return ret;
}

// Destroy dynarray
void dynarray_delete (dynarray_t **arr)
{
	if (!arr || !*arr)
		return;

	if ((*arr)->index)
		free ((*arr)->index);

	if ((*arr)->elements)
		free ((*arr)->elements);

	free (*arr);
	*arr = NULL;

	return;
}

// Resize array
// returns arr on success, NULL on failure
dynarray_t *dynarray_resize (dynarray_t *arr, unsigned int new_size)
{
	void *tmp;

	if (!(tmp = realloc (arr->index, new_size * sizeof (void *))))
		return NULL;
	else
		arr->index = tmp;

	if (!(tmp = realloc (arr->elements, new_size * arr->e_size)))
		return NULL;

	// Adjust index if necessary
	void *oldel = arr->elements;
	arr->elements = tmp;
	if (arr->elements != oldel)
	{
		int i;
		for (i = 0; i < arr->e_max; i++)
			if (arr->index [i])
				arr->index [i] = ((char*)arr->elements) + arr->e_size * i;
	} 

	// Initialize new memory
	if (new_size > arr->e_max)
	{
		memset (arr->index + arr->e_max, 0, (new_size - arr->e_max) * sizeof (void *));
		memset ((char*)arr->elements + arr->e_max * arr->e_size, 0, (new_size - arr->e_max) * arr->e_size);
	}

	arr->e_max = new_size;

	return arr;
}

// Add element to array, returns pointer to new element or NULL on failure
void *dynarray_insert (dynarray_t *arr, void *new, unsigned int pos)
{
	if (pos > arr->e_max || !new || !arr)
		return NULL;

	return arr->index [pos] = memcpy ((char*)arr->elements + arr->e_size * pos, new, arr->e_size);
}

// Push element
void *dynarray_push (dynarray_t *arr, void *new)
{
	// Valid?
	if (!arr || !new)
		return NULL;

	// Find empty slot
	int i;
	for (i = 0; i < arr->e_max; i++)
		if (arr->index [i] == NULL)
			break;

	if (i == arr->e_max) // Out of room, resize!
	{
		if (arr->resize)
		{
			return dynarray_push (dynarray_resize (arr, arr->e_max + arr->resize), new);
		}
		else
			return NULL;
	}

	return dynarray_insert (arr, new, i);
}

// Clear element from array
void dynarray_clear (dynarray_t *arr, unsigned int ele)
{
	if (!arr || ele > arr->e_max)
		return;

	arr->index [ele] = NULL;
	memset ((char*)arr->elements + ele * arr->e_size, 0, arr->e_size);

	return;
}

// Pop top element from array, write it to a pointer
void dynarray_pop (dynarray_t *arr, void *dest)
{
	if (!arr)
		return;

	int i;
	for (i = arr->e_max - 1; i >= 0; i--)
		if (arr->index [i])
			break;

	if (dest)
		memcpy (dest, arr->index [i], arr->e_size);

	dynarray_clear (arr, i);

	return;
}
