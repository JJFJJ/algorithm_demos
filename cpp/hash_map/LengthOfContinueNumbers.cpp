/*
    求一个乱序的数组里，数值大小上连续的数字，最大的长度
    比如：{100, 4, 3, 200, 5}, 连续的几个数是：3, 4, 5。长度为3。
    要求时间复杂度为O(n)，即不能进行排序。
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int longestConsecutive(const vector<int> &numbers)
{
    // vector里面的数字作为map的key,
    // value为bool
    map<int, bool> nums_map;
    for (int i = 0; i <numbers.size(); i++) {
        nums_map[numbers[i]] = false;
    }

    int longest = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (nums_map[numbers[i]]) {
            continue;
        }

        int length = 1;
        for (int j = numbers[i] + 1; nums_map.find(j) != nums_map.end(); j++) {
            // 以当前数组里元素的值+1向上查找，在map里查找，如果有就将map里这个key对应的value置为true.
            nums_map[j] = true;
            length++;
        }
        for (int j = numbers[i] - 1; nums_map.find(j) != nums_map.end(); j--) {
            // 以当前数组里的元素的值-1向下查找，在map里查找，如果有就将map里这个key对的value置为ture.
            nums_map[j] = true;
            length++;
        }
        if (longest < length) {
            longest = length;
        }
    }
    return longest;
}