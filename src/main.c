#include<stdio.h>
#include "hash_table.h"
#include "hash_table.c"

int main() {
	ht_hash_table* ht = ht_new();

	ht_insert(ht, "key", "primeagen");
	ht_insert(ht, "key", "dotneagen");
	printf("%s", ht_search(ht, "key"));
	ht_del_hash_table(ht);
	return 0;
}
