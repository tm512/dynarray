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

#ifndef DYNARRAY_H__
#define DYNARRAY_H__

typedef struct
{
	// Element properties
	uint32_t e_size;
	uint32_t e_max;

	// >0 if we want to resize array
	uint8_t resize;

	void **index;
	void *elements;
} dynarray_t;

dynarray_t *dynarray_create (uint32_t size, uint32_t max, uint8_t resize);
void dynarray_delete (dynarray_t *arr);
dynarray_t *dynarray_resize (dynarray_t *arr);
void *dynarray_push (dynarray_t *arr, void *new);
void dynarray_clear (dynarray_t *arr, uint32_t ele);
void dynarray_pop (dynarray_t *arr, void *dest);

#endif // DYNARRAY_H__
