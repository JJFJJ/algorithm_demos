#include <vector> // std::vector
#include <queue> // std::priority_queue

using namespace std;

/**
 * @brief 给定一个长度为 n 的可能有重复值的数组，找出其中不去重的最小的 k 个数。
 *        例如数组元素是4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4(任意顺序皆可)。
 *        数据范围：0 <= k,n <= 100000，数组中每个数的大小 0 <= val <= 1000
 *        要求：空间复杂度 O(n)，时间复杂度 O(nlogk)
 *
 * @param input
 * @param k
 * @return vector<int>
 */
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    vector<int> result;
    if (k <= 0 || k > input.size()) {
        return result;
    }

    // 构建大根堆，栈顶元素最大（默认）
    priority_queue<int> pri_q;
    int i = 0;
    for (; i < k; i++) {
        pri_q.push(input[i]);
    }

    // 遍历后续元素和栈顶比较：后序元素比栈顶大，不需要丢弃；
    // 后序元素比栈顶小，栈顶出栈，后序元素插入
    for (; i < input.size(); i++) {
        if (pri_q.top() > input[i]) {
            pri_q.pop();
            pri_q.push(input[i]);
        }
    }

    for (i = 0; i < k; ++i) {
        result.push_back(pri_q.top());
        pri_q.pop();
    }
    return result;
}

/**
 * @brief 有一个整数数组，请你根据快速排序的思路，找出数组中第 k 大的数。
 *        给定一个整数数组 a ,同时给定它的大小n和要找的 k ，请返回第 k 大的数(包括重复的元素，不用去重)，保证答案存在。
 *        要求：时间复杂度 O(nlogn)O(nlogn)，空间复杂度 O(1)O(1)
 *        数据范围：0 ≤ n ≤ 1000，1 ≤ K ≤ n，数组中每个元素满足0 ≤ val ≤ 10000000
 *
 * @param a
 * @param n
 * @param K
 * @return int
 */
int findMaxKth(vector<int> a, int n, int K) {
    priority_queue<int>pri_q(a.begin(), a.end());

    for (int i = 0; i < K - 1; ++i) {
        pri_q.pop();
    }
    return pri_q.top();
}