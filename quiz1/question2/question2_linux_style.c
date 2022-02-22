#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define container_of(ptr, type, member)               \
    ({                                                \
        void *__mptr = (void *) (ptr);                \
        ((type *) (__mptr - offsetof(type, member))); \
    })

struct list_head {
	struct list_head *next, *prev;
};

struct ListNode{
    int val;
    struct list_head node;
};

struct list_head *deleteDuplicates(struct list_head *head)
{
    if(!head)
        return NULL;

    struct ListNode *headNode = container_of(head, struct ListNode, node);
    if(head->next){
        struct ListNode *nextNode = container_of(head->next, struct ListNode, node);
        while(head->next && headNode->val == nextNode->val){
            head = head->next;
            headNode = nextNode;
            if(head->next)
                nextNode = container_of(head->next, struct ListNode, node);
        }
    }
   
    head->next = deleteDuplicates(head->next);
    return head;
}


struct list_head *deleteDuplicates_iter(struct list_head *head)
{
    if(!head)
        return NULL;

    struct list_head *cur = head;
    struct ListNode *curNode, *nextNode;
    curNode = container_of(head, struct ListNode, node);

    while(cur->next){
        nextNode = container_of(cur->next, struct ListNode, node);
        if(curNode->val == nextNode->val){
            cur->next = cur->next->next; 
        }else{
            cur = cur->next;
            curNode = nextNode;
        }
    }
   
    return head;
}

struct list_head *create_list(int *nums, int nums_size){
    if(nums_size == 0) return NULL;

    struct ListNode *head = malloc(sizeof(struct ListNode));
    head->val = nums[0];
    struct ListNode *cur, *next;
    cur = head;

    for(int i =1; i < nums_size;i++){
        next = malloc(sizeof(struct ListNode));
        next->val = nums[i];
        (&cur->node)->next = &next->node;
        cur = next;
    }


    return &head->node;
}

int list_equal(struct list_head *h1, struct list_head *h2){
    struct ListNode *Node1, *Node2;
    while(h1 && h2){
        Node1 = container_of(h1, struct ListNode, node);
        Node2 = container_of(h2, struct ListNode, node);
        if(Node1->val != Node2->val)
            return 0;
        h1 = h1->next;
        h2 = h2->next;
    } 

    if(!h1 && !h2) 
        return 1;

    return 0;
}

void print_ListNodes(struct list_head *head){
    if(!head)
        return;
    
    struct ListNode *cur;
    while(head){
        cur = container_of(head, struct ListNode, node);
        printf("%d\n", cur->val);
        head = head->next;
    }
}

int main(void){
    struct list_head *expect = create_list((int[]){1,2,3}, 3);

    printf("testing deleteDuplicates_iter\n");
    struct list_head *head = create_list((int[]){1,2,2,3,3,3}, 6);
    head = deleteDuplicates(head);
    assert(list_equal(expect, head));


    printf("testing deleteDuplicates\n");
    struct list_head *head_iter = create_list((int[]){1,2,2,3,3,3}, 6);
    head_iter = deleteDuplicates_iter(head_iter);
    assert(list_equal(expect, head_iter));

    printf("all tests passed\n");
}


