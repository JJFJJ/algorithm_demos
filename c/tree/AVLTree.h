/**
 * @file AVLTree.h
 * @author sunxianbin@gmail.com or mysunxianbin@163.com
 * @brief 二叉平衡树的一些常见算法实现
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "BiTree.h"


int balancedSubTree(struct TreeNode *node)
{
    if (!node) {
        return 0;
    }
    int left_h = balancedSubTree(node->lchild);
    if (left_h < 0) {
        return -1;
    }
    int right_h = balancedSubTree(node->rchild);
    if (right_h < 0) {
        return -1;
    }
    if (abs(left_h - right_h) > 1) {
        return -1;
    }
    return left_h >= right_h ? left_h : right_h;
}

/**
 * @brief 判断一个二叉树是否为平衡二叉树
 *
 * 平衡二叉树定义：一棵空树，或者它左右子树的高度绝对值不超过1，并且左右子树也是一个平衡二叉树。
 *
 * 思路：树和子树都得时二叉树，明显用递归来实现。
 *      递归每个子树，然后返回子树的最大高度，再和相邻的子树递归返回的高度比较。
 *
 * @param pRoot
 * @return true
 * @return false
 */
bool isBalancedTree(struct TreeNode* pRoot)
{
    if (balancedSubTree(pRoot) < 0) {
        return false;
    } else {
        return true;
    }
}