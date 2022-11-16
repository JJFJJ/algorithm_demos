/**
 * @file Mid_Value_in_Numbers.cpp
 * @author mysunxianbin@163.com
 * @brief 如何得到一个数据流中的中位数？
 *        如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
 *        如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
 *        我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>

using namespace std;

static vector<int> v;

void Insert(int num) {
    cout << "Insert " << num << endl;
    int left_index = 0;
    int right_index = v.size() - 1;
    int mid_index = 0;

    if (0 == v.size()) {
        v.push_back(num);
        goto exit;
    }

    mid_index = left_index + (right_index - left_index) / 2;
    while (left_index <= right_index) {

        // printf("mid_index: %d\n", mid_index);

        if (num == v[mid_index]) {
            // printf("[line: %d] mid_index: %d, value: %d\n", __LINE__, mid_index, *(v.begin()+mid_index));
            v.insert(v.begin() + mid_index, num);
            goto exit;
        } else if (num < v[mid_index]){
            right_index = mid_index - 1;
        } else {
            left_index = mid_index + 1;
        }
        mid_index = left_index + (right_index - left_index) / 2;
    }
    // printf("[line: %d] mid_index: %d, value: %d\n", __LINE__, mid_index, *(v.begin()+mid_index));
    v.insert(v.begin() + mid_index, num);

exit:
    cout << "The current numbers is {";
    for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << ", ";
    }
    cout << "}" << endl;
}

double GetMedian()
{
    if (0 == v.size() % 2) {
        return (v[v.size()/2 - 1] + v[v.size()/2]) / 2.0;
    } else {
        return v[v.size()/2] / 1.0;
    }
}

int main()
{
    cout << "Input a integer: ";
    int i;
    cin >> i;
    do {
        Insert(i);
        cout << "The mid-value is " << GetMedian() << endl;
        cout << "Continue input or Ctrl-C to exit" << endl;
    } while (cin >> i);

    return 0;
}