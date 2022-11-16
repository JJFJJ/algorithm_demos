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
int* inorderTraversal(struct TreeNode* root, int* returnSize )
{
    int *arr = (int *)calloc(1000, sizeof(int));
    if (root && arr) {
        *returnSize = 0;
        inorderNode(root, arr, returnSize);
    }

    return arr;
}

// 层序遍历二叉树参考C++实现：vector<vector<int> > levelOrder(TreeNode* root)
// TODO: C实现

/**
 * @brief 求给的二叉树的最大深度
 *
 * @param root
 * @return int
 */
int maxDepth(struct TreeNode *root)
{
    if (!root) {
        return 0;
    }
    int maxDepath_left = maxDepth(root->left);
    int maxDepath_right = maxDepth(root->right);
    return (maxDepath_left > maxDepath_right ? (maxDepath_left + 1) : (maxDepath_right + 1));

    // 非递归实现：利用队列进行层序遍历，记录下最深层次。
}

// 以之字形输出二叉树参考C++实现：vector<vector<int> > printZigzg(TreeNode *root)
// TODO: C实现

/**
 * @brief 给定一个二叉树root和一个值 sum ，判断是否有从根节点到叶子节点的节点值之和等于 sum 的路径。
 *
 * 1.该题路径定义为从树的根结点开始往下一直到叶子结点所经过的结点
 * 2.叶子节点是指没有子节点的节点
 * 3.路径只能从父节点到子节点，不能从子节点到父节点
 * 4.总节点数目为n
 *
 * @param root
 * @param sum
 * @return true
 * @return false
 */
bool hasPathSum(struct TreeNode* root, int sum )
{
    if (!root) {
        return false;
    }
    // 利用递归来实现，递归退出的条件：
    // 1. 是叶子结点；
    // 2. 叶子结点的值 等于 余数。（注：该余数为sum减去每一次递归的根结点的值。
    if (!root->left && !root->right && (0 == sum - root->val)) {
        return true;
    }

    return (hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val));
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
    Tree2DLinkedList(pRoot->left);

    if (!cur) {
        // 2.1 递归到最底层的最左结点时，pre == NULL, cur == NULL.
        pre = pRoot;
        cur = pRoot;
    } else {
        // 2.2 当pRooT指向根结点时，连接cur和pRoot，cur后移
        cur->right = pRoot;
        pRoot->left = cur;
        cur = pRoot;
    }

    // 3. 遍历右子树（递归降阶）
    Tree2DLinkedList(pRoot->right);

    return pre;
}



bool recursive(struct TreeNode *left, struct TreeNode *right)
{
    // 1. 递归结束条件
    if (!left && !right) {
        // 左叶子和右叶子都为NULL，对称
        return true;
    }
    if (!left || !right || (left->val != right->val)) {
        // 左叶子或右叶子不为空，或者值不相等，不对称
        return false;
    }

    // 2. 递归（降阶）
    return recursive(left->left, right->right) && recursive(left->right, right->left);
}

/**
 * @brief 给定一棵二叉树，判断其是否是自身的镜像（即：是否对称）
 *
 * @param pRoot
 * @return true
 * @return false
 */
bool isSymmetrical(struct TreeNode* pRoot ) {
    if (!pRoot) {
        return true;
    }
    return recursive(pRoot, pRoot);
}

/**
 * @brief 合并俩个二叉树，
 *  合并规则是：都存在的结点，就将结点值加起来，否则空的位置就由另一个树的结点来代替。
 *
 * @param t1
 * @param t2
 * @return struct TreeNode*
 */
struct TreeNode *mergeTrees(struct TreeNode *t1, struct TreeNode *t2)
{
    if (NULL == t1) {
        return t2;
    }
    if (NULL == t2) {
        return t1;
    }
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (NULL == node) {
        printf("malloc failure\n");
        abort();
    }
    node->val = t1->val + t2->val;
    node->left = mergeTrees(t1->left, t2->left);
    node->right = mergeTrees(t1->right, t2->right);
    return node;
}

/**
 * @brief 镜像一个二叉树
 *
 * @param pRoot
 * @return struct TreeNode*
 */
struct TreeNode* mirrorTree(struct TreeNode* pRoot )
{
    // 1. 递归结束的条件
    if (!pRoot) {
        return NULL;
    }

    // 2. 递归降阶
    struct TreeNode *left = mirrorTree(pRoot->left);
    struct TreeNode *right = mirrorTree(pRoot->right);

    // 3. 找到最小的结点（只有左右叶子），开始交换。
    pRoot->left = right;
    pRoot->right = left;

    return pRoot;
}

/**
 * @brief 给定一个二叉树根节点，请你判断这棵树是不是二叉搜索树。
 * 二叉搜索树满足每个节点的左子树上的所有节点均小于当前节点且右子树上的所有节点均大于当前节点。
 *
 * @param root
 * @return true
 * @return false
 */

static struct TreeNode *pre = NULL; // 用于记录当前遍历结点的前一个结点
bool isValidBST(struct TreeNode* root)
{
    // 利用递归，加上 左 < 根 < 右 这种要求，正好符合中序遍历

    // 1. 递归结束条件
    if (!root) {
        return true;
    }

    // 2. 按照中序遍历的顺序（左 -> 中 -> 右）开始递归判断每一个子树
    if (!isValidBST(root->left)) {
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

    if (!isValidBST(root->right)) {
        return false;
    }
    return true;
}


int balancedSubTree(struct TreeNode *node)
{
    if (!node) {
        return 0;
    }
    int left_h = balancedSubTree(node->left);
    if (left_h < 0) {
        return -1;
    }
    int right_h = balancedSubTree(node->right);
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

/**
 * @brief 给定一棵二叉树(保证非空)以及这棵树上的两个节点对应的val值 o1 和 o2，
 *        请找到 o1 和 o2 的最近公共祖先节点
 *
 * 思路：因为不是二叉搜索树，无法利用其左树小于根小于右树的特性。
 * 利用递归去遍历
 *
 * @param root
 * @param o1
 * @param o2
 * @return int
 */
int lowestCommonAncestor(struct TreeNode* root, int o1, int o2 )
{
    if (!root) {
        return -1;
    }
    if (root->val == o1 || root->val == o2) {
        return root->val;
    }

    int left = lowestCommonAncestor(root->left, o1, o2);
    int right = lowestCommonAncestor(root->right, o1, o2);
    if (-1 == left) {
        // o1和o2一个都不在左子树，那么一定都在右子树
        return right;
    }
    if (-1 == right) {
        // o1和o2一个都不在右子树，那么一定都在左子树
        return left;
    }
    // 一个在左，一个在右，那么公共祖先就是root
    return root->val;
}

/**
 * @brief 序列化一个给定的二叉树，然后在反序列化恢复这个二叉树
 * 序列化格式自定义。
 *
 * 思路：利用'#'表示空结点，结点之间用','分隔。
 * 序例化和反序列化使用相同的遍历方式：比如前序遍历。
 *
 */
void SerializeFunc(struct TreeNode *node, char *str, int size)
{
    // 前序遍历：根->左->右

    size_t len = strlen(str);
    if (!node) {
        snprintf(str + len, size - len, "#,");
    } else {
        snprintf(str + len, size - len, "%d,", node->val);
        SerializeFunc(node->left, str, size);
        SerializeFunc(node->right, str, size);
    }
}
char* Serialize(struct TreeNode* root ) {
    // write code here
    char *str = (char *)calloc(400, sizeof(char));
    if (!root) {
        str[0] = '#';
    } else {
        SerializeFunc(root, str, 400);
    }
    printf("Tree to String: \"%s\"\n", str);
    return str;
}
struct TreeNode* Deserialize(char* str ) {
    static int index = 0;
    if (str[index] == '#') {
        index += 2; // skip the '#' and ','
        return NULL;
    }

    int value = 0;
    while (str[index] != ',' && index < strlen(str)) {
        value = value * 10 + (str[index] - '0');
        index++;
    }
    index++; // skip the ','
    struct TreeNode *node = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
    node->val = value;
    node->left = Deserialize(str);
    node->right = Deserialize(str);
    return node;
}

/**
 * @brief 给定节点数为 n 的二叉树的前序遍历和中序遍历结果，请重建出该二叉树并返回它的头结点。
 *
 * 思路：前序遍历是：根->左->右；而中序遍历是：左->根->右
 * 从前序遍历数组中拿第一个数，在中序遍历中查找到该数值，
 * 该数值前面的则是左子树，后面的是右子树。
 * 那么分别对左子树和右子树进行递归。
 *
 * @param pre
 * @param preLen
 * @param vin
 * @param vinLen
 * @return struct TreeNode*
 */
struct TreeNode* reConstructBinaryTree(int* pre, int preLen, int* vin, int vinLen ) {
    printf("pre: %d, preLen: %d, vin: %d, vinLen: %d\n", *pre, preLen, *vin, vinLen);
    if (!pre || !vin || preLen <= 0 || vinLen <= 0 || (preLen != vinLen)) {
        return NULL;
    }

    struct TreeNode *node = NULL;

    for (int i = 0; i < vinLen; i++) {
        printf("\tpre[0]: %d, vin[%d]: %d\n", pre[0], i, vin[i]);
        if (pre[0] == vin[i]) {
            // 找到根结点，分别对左右子树进行递归
            node = (struct TreeNode *)calloc(1, sizeof(struct TreeNode *));
            node->val = pre[0];

            node->left = reConstructBinaryTree(pre + 1, i, vin, i);
            node->right = reConstructBinaryTree(pre + i + 1, (preLen - i - 1), vin + i + 1, (vinLen - i - 1));
            break;
        }
    }


    return node;
}