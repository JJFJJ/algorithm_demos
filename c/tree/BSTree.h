#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int val;
    TreeNode *lchild;
    TreeNode *rchild;
} TreeNode;

/**
 * @brief 从二叉搜索树中删除某个结点，并重接其左或右子树，重接后仍是一个二叉搜索树
 *
 * @param node 带删除结点
 */
void DeleteBSTreeNode(TreeNode *node)
{
    TreeNode *tmp = node;   // 指向待删除结点

    if (NULL == node->lchild) {
        node = node->rchild;
        free(tmp);
    } else if (NULL == node->rchild) {
        node = node->lchild;
        free(tmp);
    } else {
        // 从待删除结点的左子树中寻找前驱结点
        TreeNode *pre = node->lchild;
        while (pre->rchild) {
            tmp = pre; // tmp指向pre的父结点
            pre = pre->rchild;
        }
        // pre结点已经没有右子树了，此时pre是待删除结点的前驱
        node->val = pre->val;

        if (tmp != node) {
            // 左孩子有右子树
            tmp->rchild = pre->lchild;
        } else {
            // 左孩子没有右子树
            node->lchild = pre->lchild;
        }
        free(pre); // 删除前驱结点
    }
}

bool DeleteBSTree(TreeNode *root, const int val)
{
    if (!root) {
        return false;
    }

    if (val == root->val) {
        // 找到该结点，并删除
        DeleteBSTreeNode(root);
        return true;
    } else if (val < root->val) {
        // 递归从左子树中继续查找该结点
        return DeleteBSTree(root->lchild, val);
    } else {
        // 递归从右子树中继续查找该结点
        return DeleteBSTree(root->rchild, val);
    }
}