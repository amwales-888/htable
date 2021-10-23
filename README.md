# htable

Simple C file that implements hashtable.
Functions included

```
void hashInsert(void* userItem, struct htable_s* htable);
struct hitem_s* hashFind(void* userItem, struct htable_s* htable);
void hashDelete(struct htable_s* htable, struct hitem_s* hitem);
void hashCopy(struct htable_s* htable, struct htable_s* newTable);
```
