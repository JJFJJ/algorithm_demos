#include "BSTree.h"

void printTree(TreeNode *node)
{
    if (!node) {
        return;
    }
    printf("%d\t", node->val);
}

int main()
{
    TreeNode *root = NULL;
    TreeNode *pre = NULL;
    int vals[10] = {9, 3, 5, 7, 8, 1, 0, 2, 6, 4};
    for (int i = 0; i < sizeof(vals)/sizeof(vals[0]); i++) {
        if (!InsertBST(&root, vals[i])) {
            printf("Insert %d into BST failure\n", vals[i]);
        }
    }
    if (!isValidBST(root, pre)) {
        printf("After inserting, it's not a valid BST\n");
    }

    printf("Inorder: ");
    InorderTraverse(root, printTree);
    printf("\nPreOrder: ");
    PreorderTraverse(root, printTree);
    printf("\n");

    if (!DeleteBSTree(&root, 10)) {
        printf("remove val=10 node failure\n");
    }
    if (!DeleteBSTree(&root, 6)) {
        printf("remove val=6 node failure\n");
    }

    pre = NULL;
    if (!isValidBST(root, pre)) {
        printf("After deleting, it's not a valid BST\n");
    }

    printf("Inorder: ");
    InorderTraverse(root, printTree);
    printf("\nPreOrder: ");
    PreorderTraverse(root, printTree);
    printf("\n");

    return 0;
}