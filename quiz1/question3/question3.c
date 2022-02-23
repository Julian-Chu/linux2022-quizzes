#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

typedef struct{
    int capacity, count;
    struct list_head dhead, hheads[];
} LRUCache;

typedef struct{
    int key, value;
    struct list_head hlink, dlink;
} LRUNode;

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *obj = malloc(sizeof(*obj) + capacity * sizeof(struct list_head));
    obj->count = 0;
    obj->capacity = capacity;
    INIT_LIST_HEAD(&obj->dhead);
    for (int i = 0; i < capacity; i++)
        INIT_LIST_HEAD(&obj->hheads[i]);
    return obj;
}

void lRUCacheFree(LRUCache *obj)
{
    LRUNode *lru, *n;
    list_for_each_entry_safe(lru, n, &obj->dhead, dlink){
        list_del(&lru->dlink);
        free(lru);
    }
    free(obj);
}

int lRUCacheGet(LRUCache *obj, int key){
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry(lru, &obj->hheads[hash], hlink){
        if(lru->key == key){
            list_move(&lru->dlink, &obj->dhead);
            return lru->value;
        }
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value){
    LRUNode *lru;
    int hash = key% obj->capacity;
    list_for_each_entry(lru, &obj->hheads[hash], hlink){
        if(lru->key == key){
            list_move(&lru->dlink, &obj->dhead);
            lru->value = value;
            return;
        }
    }

    if(obj->count == obj->capacity){
        lru = list_last_entry(&obj->dhead, LRUNode, dlink);
        list_del(&lru->dlink);
        list_del(&lru->hlink);
    }else{
        lru = malloc(sizeof(LRUNode));
        obj->count++;
    }
    lru->key = key;
    list_add(&lru->dlink, &obj->dhead);
    list_add(&lru->hlink, &obj->hheads[hash]);
    lru->value = value;
}

int main(void){
    printf("testing LRUCache with capacity 4\n");
    LRUCache *cache = lRUCacheCreate(4);
    printf("put kvs: (1,1), (2,2), (3,3), (4,4)\n");
    lRUCachePut(cache, 1,1);
    lRUCachePut(cache, 2,2);
    lRUCachePut(cache, 3,3);
    lRUCachePut(cache, 4,4);
    LRUNode *lru;
    lru = list_last_entry(&cache->dhead, LRUNode, dlink);
    assert(lru->key==1);
    printf("now least recently key is 1\n");
    assert(lRUCacheGet(cache, 1) == 1);
    printf("get key 1 with its value 1\n");
    lru = list_last_entry(&cache->dhead, LRUNode, dlink);
    assert(lru->value==2);
    printf("now least recently key is 2\n");
    printf("put kv: (5,5)\n");
    lRUCachePut(cache, 5, 5);
    lru = list_first_entry(&cache->dhead, LRUNode, dlink);
    assert(lru->value==5);
    assert(lRUCacheGet(cache, 2)==-1);
    lru = list_last_entry(&cache->dhead, LRUNode, dlink);
    assert(lru->value==3);
    printf("now least recently key is 3, 2 is removed\n");
    printf("test passed\n");
}
