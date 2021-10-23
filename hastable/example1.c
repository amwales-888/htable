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

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "htable.h"

struct myItem_s {

	char name[10];
	int age;
};

typedef struct myItem_s myitem_t;

static uint32_t
jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {

	size_t i = 0;
	uint32_t hash = 0;

	while (i != length) {
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return hash;
}

static int
myHashFunc(void* a, int size) {

	char* name = ((struct myItem_s*)a)->name;
	int len = strlen(name);

	return jenkins_one_at_a_time_hash(name, len) % size;
}

static int
myCmpFunc(void* a, void* b) {

	return strcmp(((struct myItem_s*)a)->name, ((struct myItem_s*)b)->name);
}

int
example1(int argc, char** argv)
{
#define TSIZE 5
	static struct hitem_s items[TSIZE];
	static struct htable_s htable = { myHashFunc, myCmpFunc, TSIZE - 1, TSIZE, items };

	struct myItem_s people[4] = {

		{ "bill", 42 },
		{ "bob", 31 },
		{ "dave", 52 },
		{ "fred", 10 }
	};

	struct hitem_s key[] = { (void*)5 };

	hashInsert(&people[0], &htable);
	hashInsert(&people[1], &htable);
	hashInsert(&people[2], &htable);
	hashInsert(&people[3], &htable);

	{
		struct myItem_s person[1] = { "dave", 0 };
		struct myItem_s* ptr;

		ptr = hashFind(person, &htable)->userItem;

		printf("%s %d\n", ptr->name, ptr->age);
	}

	return 0;
}
