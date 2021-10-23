/*

The MIT License(MIT)
Copyright © 2021 Angelo Masci

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated
documentation files(the “Software”), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <stdint.h>

#include "htable.h"

void
hashInsert(void* userItem, struct htable_s* htable) {

	/* This fnction MUST only be called if free > 0
	 * This functin MUST only be called if key does not already exist in the table
	 */

	struct hitem_s* hitem = &htable->htable[htable->hash(userItem, htable->size)];
	struct hitem_s* litem = &htable->htable[htable->size];

	while (1) {

		if ((hitem->userItem == (void*)0) || (hitem->userItem == (void *)HTABLEDELETED)) {
			hitem->userItem = userItem;
			htable->free--;
			break;
		}

		/* Collision, move to next available space, repeat unti
		 * we find a free slot.
		 */
		if (++hitem == litem) {
			hitem = htable->htable;
		}
	}
}

struct hitem_s*
hashFind(void* userItem, struct htable_s* htable) {

	/* This function returns 0 if the item cannot be found
	 * or the address of the item if it is found
	 */

	struct hitem_s* hitem = &htable->htable[htable->hash(userItem, htable->size)];
	struct hitem_s* litem = &htable->htable[htable->size];

	while (1) {

		if (hitem->userItem == (void*)0) {
			return (struct hitem_s*)0;
		}

		if (((hitem->userItem != (void*)HTABLEDELETED)) && (htable->cmp(hitem->userItem, userItem) == 0)) {
			return hitem;
		}

		/* We didnt find our item, keep searching 
		 */
		if (++hitem == litem) {
			hitem = htable->htable;
		}
	}
}

void
hashDelete(struct htable_s* htable, struct hitem_s* hitem) {


	hitem->userItem = (void*)HTABLEDELETED;
	htable->free++;
}

void
hashCopy(struct htable_s* htable, struct htable_s *newTable) {

	/* newTable MUST be initialised, sized and allocated
	 * all entries MUST be zeroed
	 */

	struct hitem_s* litem = htable->htable;
	int i;

	for (i = 0; i < htable->size; i++) {

		if ((litem->userItem == (void*)0) || (litem->userItem == (void*)HTABLEDELETED)) {
			continue;
		}

		hashInsert(litem->userItem, newTable);
		litem++;
	}
}
