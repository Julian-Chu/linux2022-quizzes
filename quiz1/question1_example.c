#include <stdlib.h>
static int cmp(const void *lhs, const void *rhs){
    if (*(int *) lhs == *(int *) rhs)
        return 0;
    return *(int *) lhs < *(int *) rhs? -1 : 1;
}

static int *allocwrapper(int a, int b, int *returnSize){
    *returnSize = 2;
    int *res = (int *) malloc(size(int) * 2);
    res[0]= a, res[1] = b;
    return res;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize){
    *returnSize = 2;
    int arr[numsSize][2];
    for (int i = 0; i < numsSize; ++i){
        arr[i][0] = nums[i];
        arr[i][1] = i;
    }
    qsort(arr, numsSize, sizeof(arr[0]), cmp);
    for (int i = 0, j = numsSize - 1; i < j;){
        if (arr[i][0] + arr[j][0] == target)
            return allocwrapper(arr[i][1], arr[j][1], returnSize);
        if(arr[i][0] + arr[j][0] < target)
            ++i;
        else
            --j;
    }
    *returnSize = 0;
    return NULL;
    
}
