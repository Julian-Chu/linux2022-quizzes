#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode *deleteDuplicates(struct ListNode *head){
    if(!head)
        return NULL;

    if(head->next && head->val == head->next->val){
        while(head->next && head->val == head->next->val)
            head = head->next;
        //return deleteDuplicates(head->next);
    }

    head->next = deleteDuplicates(head->next);
    return head;
}


struct ListNode *deleteDuplicates_iter(struct ListNode *head){
    if(!head)
        return NULL;
    struct ListNode *cur = head;
    while(cur && cur->next){
        if(cur->val == cur->next->val){
            struct ListNode *next = cur->next->next;
            cur->next = next;
        }
        cur = cur->next;
    }
    return head;
}


void print_list_node(struct ListNode *h){
    printf("list: ");
    while(h){
        printf("%d ", h->val);
        h = h->next;
    }
    printf("\n");
}

int list_equal(struct ListNode *h1, struct ListNode *h2){
    //print_list_node(h1);
    //print_list_node(h2);
    while(h1 && h2){
        if(h1->val != h2->val)
            return 0;
        h1 = h1->next;
        h2 = h2->next;
    } 

    if(!h1 && !h2) 
        return 1;

    return 0;
}

struct ListNode *create_list_from_array(int *nums, int numsSize){
    struct ListNode *head = malloc(sizeof(struct ListNode));
    head->val = nums[0];
    struct ListNode *cur = head;

    for (int i = 1; i < numsSize; ++i){
        struct ListNode *next = malloc(sizeof(struct ListNode));
        next->val = nums[i];
        cur->next = next;
        cur = next;
    }

    return head;
}

void test_deleteDuplicates(int *input_arr, int input_arr_size, int *expected, int expected_size){
    struct ListNode *h1 = deleteDuplicates(create_list_from_array(input_arr, input_arr_size));
    struct ListNode *h2 = create_list_from_array(expected, expected_size);
    assert(list_equal(h1, h2));
}

void test_deleteDuplicates_iter(int *input_arr, int input_arr_size, int *expected, int expected_size){
    struct ListNode *h1 = deleteDuplicates_iter(create_list_from_array(input_arr, input_arr_size));
    struct ListNode *h2 = create_list_from_array(expected, expected_size);
    assert(list_equal(h1, h2));
}

int main(void){
    int input[6] = {1,1,2,2,3,3};
    int input_size = 6;
    int expect[3] = {1,2,3};
    int expect_size = 3;
    printf("testing deleteDuplicates_iter\n");
    test_deleteDuplicates_iter(input, input_size, expect, expect_size);
    printf("testing deleteDuplicates\n");
    test_deleteDuplicates(input, input_size, expect, expect_size);
    printf("all tests passed\n");
}

