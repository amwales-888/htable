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

int 
myHashFunc(void *a, int size) {

	char* ptr = ((struct myItem_s*)a)->name;
	int hash = 0;

	while (*ptr) {
		hash += *ptr;
		ptr++;
	}
	return hash % size;
}

int 
myCmpFunc(void* a, void* b) {

	return strcmp(((struct myItem_s*)a)->name, ((struct myItem_s*)b)->name);
}


int 
main(int argc, char **argv)
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
}
