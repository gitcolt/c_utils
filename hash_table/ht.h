/*
 * Example usage:
 *
 * typedef struct { int x; int y; } Point;
 *
 * int main() {
 *      HT *ht = ht_create(10, NULL);
 *
 *      Point p_a = { 1, 1 };
 *      Point p_b = { 2, 2 };
 *      Point p_c = { 3, 3 };
 *
 *      ht_set(ht, "a", &p_a);
 *      ht_set(ht, "b", &p_b);
 *      ht_set(ht, "c", &p_c);
 *
 *      Point *p = ht_get(ht, "b");
 *      assert(p == &p_b);
 *
 *      ht_remove(ht, "b");
 *      assert(ht_get(ht, "b") == NULL);
 *
 *      ht_destroy(ht);
 *
 *      return 0;
 * }
 */

#ifndef HT_H
#define HT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct HT HT;
typedef uint64_t (*hash_func) (const char *, size_t);

HT *ht_create(uint32_t size, hash_func hf);
void ht_destroy(HT *ht);
bool ht_set(HT *ht, const char *key, void *obj);
void *ht_get(HT *ht, const char *key);
void *ht_remove(HT *ht, const char *key);

#endif
