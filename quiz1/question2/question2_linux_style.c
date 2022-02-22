#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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

struct list_head *create_list(){
    struct ListNode *head = malloc(sizeof(struct ListNode));
    head->val = 1;
    struct ListNode *node1 = malloc(sizeof(struct ListNode));
    node1->val = 1;
    (&head->node)->next = &node1->node;
    struct ListNode *node2 = malloc(sizeof(struct ListNode));
    node2->val = 2;
    (&node1->node)->next = &node2->node;
    struct ListNode *node3 = malloc(sizeof(struct ListNode));
    node3->val = 2;
    (&node2->node)->next = &node3->node;
    struct ListNode *node4 = malloc(sizeof(struct ListNode));
    node4->val = 2;
    (&node3->node)->next = &node4->node;
    return &head->node;
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
    struct list_head *head = create_list();
    head = deleteDuplicates(head);
    print_ListNodes(head);


    struct list_head *head_iter = create_list();
    head_iter = deleteDuplicates_iter(head_iter);
    print_ListNodes(head_iter);
}


