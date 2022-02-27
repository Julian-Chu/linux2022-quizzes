#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

struct hlist_node { struct hlist_node *next, **pprev; };
struct hlist_head { struct hlist_node *first; };

#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static inline void INIT_HLIST_NODE(struct hlist_node *h)
{
	h->next = NULL;
	h->pprev = NULL;
}

struct seq_node{
    int num;
    struct hlist_node hnode;
};


static inline void hlist_del(struct hlist_node *n)
{
	struct hlist_node *next = n->next;
	struct hlist_node **pprev = n->pprev;
}


#define hlist_entry(ptr, type, member) container_of(ptr,type,member)


#define hlist_for_each_entry(pos, head, member)				\
	for (pos = hlist_entry((head)->first, typeof(*(pos)), member);\
	     pos;							\
	     pos = hlist_entry((pos)->member.next, typeof(*(pos)), member))

static struct seq_node *find(int num, int size, struct hlist_head *heads)
{
    struct seq_node *node;
    int hash = num < 0? -num%size:num%size;
    hlist_for_each_entry(node, &heads[hash], hnode){
        if (node->num == num)
            return node;
        if (!(&node->hnode)->next){
            return NULL;
        }
    }
    return NULL;
}

int longestConsecutive(int *nums, int n_size){
    int hash, length = 0;
    struct seq_node *node;
    struct hlist_head *heads = malloc(n_size * sizeof(struct hlist_head));
    struct hlist_node *n, *first;
    struct hlist_head *h;

    for (int i = 0; i<n_size; i++)
        INIT_HLIST_HEAD(&heads[i]);

    for(int i = 0; i < n_size; i++){
       node = malloc(sizeof(*node));
       node->num = nums[i];
       n = &node->hnode;

       hash = nums[i] < 0? -nums[i] % n_size:nums[i] % n_size;
       h = &heads[hash];
       first = h->first;

       n->next = first;
       if(first)
           first->pprev = &n->next;
       h->first = n;
       n->pprev = &h->first;
    }

    for (int i = 0; i < n_size; i++){
        int len = 0;
        int num;
        node = find(nums[i], n_size, heads);
        while(node){
            len++;
            num = node->num;
            hlist_del(&node->hnode);

            int left = num, right = num;
            while ((node = find(--left, n_size, heads))){
                len++;
                hlist_del(&node->hnode);
            }

            while ((node = find(++right, n_size, heads))){
                len++;
                hlist_del(&node->hnode);
            }

            length = len > length ? len:length;
        }
    }

    return length;
}

int main(void){
    int nums1[4] = {0, 1, 2, 4};
    assert(longestConsecutive(nums1, 4)== 3);

    int nums2[5] = {-1, 0, 1, 3, 4};
    assert(longestConsecutive(nums2, 5)== 3);
    printf("tests passed\n");
}

