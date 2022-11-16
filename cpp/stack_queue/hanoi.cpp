/**
 * @file hanoi.cpp
 * @author mysunxianbin@163.com
 * @brief 汉诺塔问题，利用递归方法和C++ stack容器俩中方式解决。
 * @version 0.1
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <stack>

using namespace std;

class Hanoi
{
private:

    /**
     * @brief 非递归实现需要用的栈元素结构
     *
     */
    struct HanoiData
    {
        int x; // 盘子初始所在的塔柱编号（1～3）
        int y; // 盘子最终所在的塔柱编号（1～3），与x不同
        int n; // 盘子数
    };
    HanoiData m_hd;
    static int m_cnt; // 搬动次数
    stack<HanoiData> m_st; // 辅助搬运的栈

    inline void printInfo(int x, int z, int n) const
    {
        cout << "第" << ++m_cnt << "步：将" << n << "号盘从" << x << "住移到" << z << "柱" << endl;
    }

public:

    /**
     * @brief 将塔柱x上编号为1到n的n个圆盘，按照规定移到塔柱z上，y用作辅助塔柱。
     *
     * @param n 初始塔柱上圆盘的个数
     * @param x 初始塔柱的编号
     * @param y 辅助塔柱的编号
     * @param z 最终塔柱的编码
     */
    void hanoi(int n, int x, int y, int z) const
    {
        if (1 == n) {
            // 剩最后一个圆盘，直接挪动不用递归
            move(x, z, 1);
            return;
        }

        hanoi(n - 1, x, z, y);
        move(x, z, n);
        hanoi(n - 1, y, x, z);
    }

    void hanoi(int n, int x, int y)
    {
        assert(n > 0 && x != y);
        m_hd.n = n;
        m_hd.x = x;
        m_hd.y = y;
        m_cnt = 0;

        while (m_hd.n || !m_st.empty()) {
            while (m_hd.n) {
                m_hd.n--;
                m_st.push(m_hd);
                m_hd.y ^= m_hd.x;
            }
            if (!m_st.empty()) {
                m_hd = m_st.top();
                move(m_hd.x, m_hd.y, m_hd.n+1);
                m_st.pop();
                m_hd.x ^= m_hd.y;
            }
        }
    }
};

int Hanoi::m_cnt = 0;

int main()
{
    Hanoi H;
    int n;
}