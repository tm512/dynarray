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

#include "dynarray.h"

typedef struct
{
	int a;
	int b;
} test_t;

int main (void)
{
	srand (42);

	dynarray_t *arr = dynarray_create (sizeof (test_t), 4, 1);

	// Add 10 random elements...
	int i;
	for (i = 0; i < 10; i++)
	{
		test_t heh = { rand (), rand () };
		dynarray_push (arr, &heh);
	}

	// Change one element to something different
	test_t something = { 1, 2 };
	dynarray_insert (arr, &something, 0);

	// Pop top element, print out its numbers...
	test_t popped;
	dynarray_pop (arr, &popped);
	printf ("Pop test: %i and %i\n", popped.a, popped.b);

	// Clear 6th element
	dynarray_clear (arr, 5);

	// Now loop and get the rest of the elements, avoiding NULLs
	for (i = 0; i < 16; i++)
	{
		test_t *t = (test_t *)arr->index [i];
		if (t && i < arr->e_max)
			printf ("%i: %i and %i\n", i, t->a, t->b);
	}

	// Free:
	dynarray_delete (arr);
	return 0;
}
