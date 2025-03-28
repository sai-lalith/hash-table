typedef struct {
	char* key;
	char* value;
} ht_item;

typedef struct {
	int size;
	int count;
	ht_item** item;
} ht_hash_table;

void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);
