#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


void preNode(struct TreeNode* root, int *arr, int *arrSize)
{
    if (!root) {
        return;
    }

    // 根结点
    arr[*arrSize] = root->val;
    (*arrSize)++;

    // 左结点
    if (root->left) {
        preNode(root->left, arr, arrSize);
    }

    // 右结点
    if (root->right) {
        preNode(root->right, arr, arrSize);
    }
}

/**
 * @brief 前序遍历二叉树（前序遍历：根->左->右）
 *
 * 思路：使用递归方法，先记录根结点，
 *      然后将每个结点当作根结点传递给下一次，直到没有叶子结点。
 *
 * @param root
 * @param returnSize
 * @return int*
 */
int * preorderTraversal(struct TreeNode* root, int* returnSize)
{
    int *arr = (int *)calloc(100, sizeof(int));
    if (root && arr) {
        *returnSize = 0;
        preNode(root, arr, returnSize);
    }

    return arr;
}


void inorderNode(struct TreeNode *root, int *arr, int *arrSize)
{
    if (!root) {
        return;
    }

    // 左结点
    if (root->left) {
        inorderNode(root->left, arr, arrSize);
    }

    // 根结点
    arr[*arrSize] = root->val;
    (*arrSize)++;

    // 右结点
    if (root->right) {
        inorderNode(root->right, arr, arrSize);
    }
}

/**
 * @brief 中序遍历二叉树（中序遍历：左->根->右）
 *
 * @param root
 * @param returnSize
 * @return int*
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize ) {
    int *arr = (int *)calloc(1000, sizeof(int));
    if (root && arr) {
        *returnSize = 0;
        inorderNode(root, arr, returnSize);
    }

    return arr;
}