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
 * 利用队列的先进先出
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