# htable

Simple C file that implements hashtable.
Functions included

```
void hashInsert(void* userItem, struct htable_s* htable);
struct hitem_s* hashFind(void* userItem, struct htable_s* htable);
void hashDelete(struct htable_s* htable, struct hitem_s* hitem);
void hashCopy(struct htable_s* htable, struct htable_s* newTable);
```

- Example1 - A simple user implementation that uses minimal memory but recomputes the hash.
- Example2 - Extends example1 by caching the hash value but requires and additional uint32_t to be saved in the user structure.
