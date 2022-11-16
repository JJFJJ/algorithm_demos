#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * @brief 二叉树的层序遍历
 *
 * 利用队列的先进先出（每次出队数目和队列出队前的大小一致，新入队的不算），直到下一次出队。
 *
 * @param root
 * @return vector<vector<int> >
 */
vector<vector<int> > levelOrder(TreeNode* root)
{
    vector<vector<int> > whole;
    if (!root) {
        return whole;
    }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();
        vector<int> level;
        for (int i = 0; i < n; i++) {
            TreeNode *node = q.front();
            level.push_back(node->val);
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
            q.pop();
        }
        whole.push_back(level);
    }

    return whole;
}

/**
 * @brief 以之字形输出二叉树
 *
 * 思路：利用层序遍历二叉树，出队后做一次反转（交替反转）即可。
 *
 * @param root
 * @return vector<vector<int> >
 */
vector<vector<int> > printZigzg(TreeNode *root)
{
    vector<vector<int> > whole;
    if (!root) {
        return whole;
    }

    queue<TreeNode *> q;
    q.push(root);

    bool flag = false; // false: ->; true: <-
    TreeNode *tmp = NULL;

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++) {
            tmp = q.front();
            if (tmp->left) {
                q.push(tmp->left);
            }
            if (tmp->right) {
                q.push(tmp->right);
            }
            level.push_back(tmp->val);
            q.pop();
        }

        if (flag) {
            std::reverse(level.begin(), level.end());
        }
        whole.push_back(level);
        flag = !flag;
    }

    return whole;
}

/**
 * @brief 给定一个二叉树，判断是否为完全二叉树
 *
 * 完全二叉树的定义：若二叉树的深度为h，除第h层外，其他各层的结点数都达到最大个数，
 *                第h层所有的叶子结点都连续集中在最左边。（第h层可能包含[1~2h]个结点）
 *
 * 思路：利用层序遍历，一层层遍历检查（注：层序遍历需要利用到队列）
 *
 * @param root
 * @return true
 * @return false
 */
bool isCompleteTree(TreeNode* root)
{
    queue<TreeNode *> q;
    q.push(root);

    TreeNode *tmp = NULL;
    bool flag = false; // 是否遇到NULL结点，false：没有，true：遇到

    while (!q.empty()) {
        tmp = q.front();
        if (!tmp) {
            flag = true;
            q.pop(); // 当前NULL结点出队，队列大小-1
            continue; // 继续查抄该层的后续结点
        }

        // 如果是完全二叉树，那么遇到NULL结点后，该层从左到右不会有其他的结点
        if (flag) {
            // NULL结点右边还有非NULL结点，则不是完全二叉树
            return false;
        }
        q.push(tmp->left);
        q.push(tmp->right);
        q.pop();
    }

    return true;
}

/**
 * @brief 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 * 对于该题的最近的公共祖先定义:对于有根树T的两个节点p、q，最近公共祖先LCA(T,p,q)表示一个节点x，
 * 满足x是p和q的祖先且x的深度尽可能大。在这里，一个节点也可以是它自己的祖先.
 *
 * 思路：分别从根结点往下寻找到给定的两个结点的路径，然后路径最后一个相同的结点即是最近公共祖先。
 *
 * @param root
 * @param p
 * @param q
 * @return int
 */
int lowestCommonAncestorBST(TreeNode* root, int p, int q)
{
    vector<int> path_p = getPathBST(root, p);
    vector<int> path_q = getPathBST(root, q);

    int result = -1; // TODO: 也可以用结点来代替结点的值
    for (int i = 0; i < path_p.size() && i < path_q.size(); i++) {
        if (path_p[i] == path_q[i]) {
            // 每次记录最新的公共结点的值
            result = path_p[i];
            continue;
        } else {
            // 没有公共结点了，退出循环
            break;
        }
    }

    return result;
}

vector<int> getPathBST(TreeNode *root, int target)
{
    vector<int> path;
    if (!root) {
        // path is empty
        return path;
    }
    path.push_back(root->val);
    TreeNode *tmp = root;
    while (target != tmp->val) {
        path.push_back(tmp->val);
        if (target > tmp->val) {
            // 根结点小于目标值，继续往右边查找
            tmp = tmp->right;
        } else if (target < tmp->val) {
            // 根结点大于目标值，继续往左边查找
            tmp = tmp->left;
        }
    }
    // 找到目标结点，路径应该包括目标结点自身
    path.push_back(tmp->val);
    return path;
}

/**
 * @brief 请根据二叉树的前序遍历，中序遍历恢复二叉树，并打印出二叉树的右视图
 *
 * @param xianxu
 * @param zhongxu
 * @return vector<int>
 */
vector<int> rightView(vector<int>& xianxu, vector<int>& zhongxu) {
    vector<int> result;
    TreeNode *root = reConstructBinaryTree(xianxu.data(), xianxu.size(), zhongxu.data(), zhongxu.size());
    if (!root) {
        return result;
    }

    queue<TreeNode *> q;
    q.push(root);
    TreeNode *tmp = NULL;
    int size = 0;
    while (!q.empty()) {
        vector<int> layer;
        size = q.size();
        for (int i = 0; i < size; i++) {
            tmp = q.front();
            layer.push_back(tmp->val);
            if (tmp->left) {
                q.push(tmp->left);
            }
            if (tmp->right) {
                q.push(tmp->right);
            }
            q.pop();
        }
        result.push_back(layer[layer.size() - 1]);
    }

    return result;
}
TreeNode* reConstructBinaryTree(int* pre, int preLen, int* vin, int vinLen )
{
    printf("pre: %d, preLen: %d, vin: %d, vinLen: %d\n", *pre, preLen, *vin, vinLen);
    if (!pre || !vin || preLen <= 0 || vinLen <= 0 || (preLen != vinLen)) {
        return NULL;
    }

    TreeNode *node = NULL;

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
}