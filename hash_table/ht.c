#include "ht.h"

#include <malloc.h>
#include <string.h>

typedef struct HTEntry {
    char *key;
    void *val;
    struct HTEntry *next;
} HTEntry;

struct HT {
    uint32_t size;
    hash_func hash;
    HTEntry **elements;
};

static size_t ht_index(HT *ht, const char *key) {
    if (!ht->size)
        return SIZE_MAX;
    size_t res = (ht->hash(key, strlen(key)) % ht->size);
    return res;
}

static uint64_t sdbm_hash(const char *in, size_t size) {
    uint64_t hash_val = 0;
    char ch;
    while ((ch = *in++))
        hash_val = ch + (hash_val << 6) + (hash_val << 16) - hash_val;
    return hash_val;
}

HT *ht_create(uint32_t size, hash_func hf) {
    HT *ht = malloc(sizeof(*ht));
    ht->size = size;
    ht->hash = hf ? hf : sdbm_hash;
    ht->elements = calloc(ht->size, sizeof(HTEntry));
    return ht;
}

void ht_destroy(HT *ht) {
    for (size_t i = 0; i < ht->size; ++i) {
        while (ht->elements[i]) {
            HTEntry *tmp = ht->elements[i];
            ht->elements[i] = ht->elements[i]->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(ht->elements);
    free(ht);
}

// returns true if a value was inserted
bool ht_set(HT *ht, const char *key, void *val) {
    if (!val)
        return false;
    if (ht_get(ht, key))
        return false;

    size_t idx = ht_index(ht, key);
    HTEntry *new_entry = malloc(sizeof(*new_entry));
    new_entry->val = val;
    new_entry->key = strdup(key);
    new_entry->next = ht->elements[idx];
    ht->elements[idx] = new_entry;
    return true;
}

void *ht_get(HT *ht, const char *key) {
    size_t idx = ht_index(ht, key);
    HTEntry *entry = ht->elements[idx];
    while (entry && strcmp(entry->key, key))
        entry = entry->next;
    return entry ? entry->val : NULL;
}

void *ht_remove(HT *ht, const char *key) {
    size_t idx = ht_index(ht, key);
    HTEntry *entry = ht->elements[idx];
    HTEntry *prev = NULL;
    while (entry && strcmp(entry->key, key)) {
        prev = entry;
        entry = entry->next;
    }
    if (!entry)
        return NULL;
    if (!prev) // deleting head
        ht->elements[idx] = entry->next;
    else
        prev->next = entry->next;
    void *removed_val = entry->val;
    free(entry);
    return removed_val;
}

