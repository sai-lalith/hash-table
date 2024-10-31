#include <stdlib.h>
#include <string.h>
#include <math.h>


#define HT_PRIME_1 997
#define HT_PRIME_2 359
static ht_item HT_DELETED_ITEM = {NULL, NULL};


static ht_item* ht_new_item(const char* k, const char* v) {
	ht_item* i = malloc(sizeof(ht_item));
	i->key = strdup(k);
	i->value = strdup(v);
	return i;
}

ht_hash_table* ht_new() {
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));

	ht->size = 53;
	ht->count = 0;
	ht->item = calloc((size_t)ht->size, sizeof(ht_item*));
	return ht;
}

static void ht_del_item(ht_item* i) {
	free(i->key);
	free(i->value);
	free(i);
}

static void ht_del_hash_table(ht_hash_table* ht) {
	for (int i = 0; i < ht->size; i++) {
		ht_item* item = ht->item[i];
		if (item != NULL) {
			ht_del_item(item);
		}
	}
	free(ht->item);
	free(ht);
}

static int ht_hash(const char* s, const int a, const int num_buckets){
	int hash = 0;
	int len_s = strlen(s);
	for (int i = 0; i < len_s; i++){
		hash += (long)pow(a, (len_s - (i+1))) * s[i];
		hash = hash % num_buckets;
	}
	return (int)hash;
}

static int ht_get_hash(
	const char* s, const int num_buckets, const int attempt
){
	const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
	const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
	return (hash_a + attempt * (hash_b + 1)) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value){
	ht_item* item = ht_new_item(key, value);
	int index = ht_get_hash(item->key, ht->size, 0);
	ht_item* curr_item = ht->item[index];
	int i = 1;
	while (curr_item != NULL && curr_item != &HT_DELETED_ITEM){
		if (strcmp(curr_item->key, key) == 0) {
            ht_del_item(curr_item);
            ht->item[index] = item;
            return;
        }
		index = ht_get_hash(item->key, ht->size, i);
		curr_item = ht->item[index];
		i++;
	}
	ht->item[index] = item;
	ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key){
	// Todo key not in array could loop
	int index = ht_get_hash(key, ht->size, 0);
	ht_item* item = ht->item[index];
	int i = 1;
	while (item != NULL)
	{
		if (item != &HT_DELETED_ITEM){
			if(strcmp(item->key, key) == 0){
				return item->value;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->item[index];
		i++;
	}
	return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key){
	// behaviour when the key's deleted?
	// behaviour when doesn't exist?
	int index = ht_get_hash(key, ht->size, 0);
	ht_item* item = ht->item[index];
	int i = 0;
	while (item != NULL)
	{
		if(strcmp(item->key, key) == 0){
			ht->item[index] = &HT_DELETED_ITEM;
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->item[index];
		i++;
	}
	ht->count--;
}

