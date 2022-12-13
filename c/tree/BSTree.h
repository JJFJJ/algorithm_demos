/**
 * @file BSTree.h
 * @author sunxianbin@gmail.com or mysunxianbin@163.com
 * @brief 二叉搜索树（Binary Search Tree）一些常见的算法实现
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _BS_TREE_
#define _BS_TREE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "BiTree.h"

/**
 * @brief 往二叉搜索树中插入一个结点，该结点值为val
 *
 * @param p 二叉搜索树的根结点
 * @param val 待插入结点的值
 * @return true 树中没有相同值的结点，插入成功
 * @return false 树中有相同值的结点，插入失败
 */
bool InsertBST(TreeNode **p, int val)
{
#if 0
    // 递归实现插入

    if (NULL == *p) {
        *p = (TreeNode *)calloc(1, sizeof(TreeNode));
        assert(NULL != *p);
        (*p)->val = val;
        return true;
    }
    if (val == (*p)->val) {
        return false;
    }

    if (val < (*p)->val) {
        return InsertBST(&((*p)->lchild), val);
    } else {
        return InsertBST(&((*p)->rchild), val);
    }
#else
    // 非递归实现插入

    TreeNode *node = (TreeNode *)calloc(1, sizeof(TreeNode));
    assert(NULL != node);
    node->val = val;

    if (NULL == *p) {
        *p = node;
        return true;
    }

    TreeNode **tmp = p;
    while (*tmp) {
        if (val == (*tmp)->val) {
            free(node);
            return false;
        }
        if (val < (*tmp)->val) {
            tmp = &(*tmp)->lchild;
        } else {
            tmp = &(*tmp)->rchild;
        }
    }
    // while结束时，tmp = NULL，tmp指向叶子结点孩子
    *tmp = node;
    return true;
#endif
}

/**
 * @brief 从二叉搜索树中删除某个结点，并重接其左或右子树，重接后仍是一个二叉搜索树
 *
 * @param node 带删除结点
 */
void DeleteBSTreeNode(TreeNode **node)
{
    TreeNode *tmp = *node;   // 指向待删除结点

    if (NULL == (*node)->lchild) {
        *node = (*node)->rchild;
        free(tmp);
    } else if (NULL == (*node)->rchild) {
        *node = (*node)->lchild;
        free(tmp);
    } else {
        // 从待删除结点的左子树中寻找前驱结点
        TreeNode *pre = (*node)->lchild;
        while (pre->rchild) {
            tmp = pre; // tmp指向pre的父结点
            pre = pre->rchild;
        }
        // pre结点已经没有右子树了，此时pre是待删除结点的前驱
        (*node)->val = pre->val;

        if (tmp != *node) {
            // 左孩子有右子树
            (tmp)->rchild = pre->lchild;
        } else {
            // 左孩子没有右子树
            (*node)->lchild = pre->lchild;
        }
        free(pre); // 删除前驱结点
    }
}

/**
 * @brief 删除二叉平衡树中某个结点
 *
 * @param root 二叉平衡树的根结点
 * @param val 目标结点的值
 * @return true 树中存在相同值的结点，删除成功
 * @return false 树中不存在相同值的结点，删除失败
 */
bool DeleteBSTree(TreeNode **root, const int val)
{
    if (!root || !(*root)) {
        return false;
    }

    if (val == (*root)->val) {
        // 找到该结点，并删除
        DeleteBSTreeNode(root);
        return true;
    } else if (val < (*root)->val) {
        // 递归从左子树中继续查找该结点
        return DeleteBSTree(&(*root)->lchild, val);
    } else {
        // 递归从右子树中继续查找该结点
        return DeleteBSTree(&(*root)->rchild, val);
    }
}

/**
 * @brief 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表
 *
 * 思路：中序遍历+递归
 *
 * @param pRoot
 * @return struct TreeNode*
 */
struct TreeNode* Tree2DLinkedList(struct TreeNode* pRoot)
{
    static struct TreeNode *pre = NULL;
    static struct TreeNode *cur = NULL;

    // 1. 递归退出的条件
    if (!pRoot) {
        return NULL;
    }

    // 2. 遍历左子树（递归降阶）
    Tree2DLinkedList(pRoot->lchild);

    if (!cur) {
        // 2.1 递归到最底层的最左结点时，pre == NULL, cur == NULL.
        pre = pRoot;
        cur = pRoot;
    } else {
        // 2.2 当pRooT指向根结点时，连接cur和pRoot，cur后移
        cur->rchild = pRoot;
        pRoot->lchild = cur;
        cur = pRoot;
    }

    // 3. 遍历右子树（递归降阶）
    Tree2DLinkedList(pRoot->rchild);

    return pre;
}

/**
 * @brief 给定一个二叉树根节点，请你判断这棵树是不是二叉搜索树。
 * 二叉搜索树满足每个节点的左子树上的所有节点均小于当前节点且右子树上的所有节点均大于当前节点。
 *
 * @param root
 * @return true
 * @return false
 */
bool isValidBST(struct TreeNode* root, struct TreeNode *pre)
{
    // 利用递归，加上 左 < 根 < 右 这种要求，正好符合中序遍历

    // 1. 递归结束条件
    if (!root) {
        return true;
    }

    // 2. 按照中序遍历的顺序（左 -> 中 -> 右）开始递归判断每一个子树
    if (!isValidBST(root->lchild, pre)) {
        return false;
    }

    if (!pre) {
        pre = root;
    } else {
        if (pre->val >= root->val) {
            return false;
        }
        pre = root;
    }

    if (!isValidBST(root->rchild, pre)) {
        return false;
    }
    return true;
}

#endif // _BS_TREE_