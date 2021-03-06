/*

The MIT License(MIT)
Copyright ? 2021 Angelo Masci

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated
documentation files(the ?Software?), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED ?AS IS?, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#ifndef __HTABLE_H__
#define __HTABLE_H__

#include <stdint.h>

#define HTABLEDELETED UINT32_MAX

struct hitem_s {

	union {
		void *userItem;
	};
};

struct htable_s {

	int (*hash)(void* a, int size);
	int (*cmp)(void* a, void* b);

	int free;
	int size;

	struct hitem_s* htable;
};

void hashInsert(void* userItem, struct htable_s* htable);
struct hitem_s* hashFind(void* userItem, struct htable_s* htable);
void hashDelete(struct htable_s* htable, struct hitem_s* hitem);
void hashCopy(struct htable_s* htable, struct htable_s* newTable);

#endif /* __HTABLE_H__ */