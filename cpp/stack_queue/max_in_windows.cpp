#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
    vector<int> result;
    if (size > num.size() || (0 == size)) {
        return result;
    }

    for (int i = 0; i <= num.size() - size; i++) {
        // 用于存放每个窗口内的元素。
        // 存放规则为，后一个大于前一个的值，入栈。否则抛弃。
        // 存放完一个窗口后，返回栈顶元素。
        stack<int> st;

        for (int j = 0; j < size; j++) {
            if (st.empty()) {
                printf("(line: %d) window[%d]: %d\n", __LINE__, j, num[i+j]);
                st.push(num[i+j]);
            } else {
                if (num[i+j] > st.top()) {
                    printf("(line: %d) window[%d]: %d\n", __LINE__, j, num[i+j]);
                    st.push(num[i+j]);
                } else {
                    // do nothing, next for
                }
            }
        }

        result.push_back(st.top());
    }

    return result;
}

int main()
{
    int arr[] = { 2,3,4,2,6,2,5,1 };
    vector<int> num(arr, arr + sizeof(arr)/sizeof(int));
    cout << "Input the window size: ";
    int size;
    cin >> size;
    vector<int> max_in_window = maxInWindows(num, size);
    cout << "size: " << max_in_window.size() << endl;
    for (vector<int>::iterator iter = max_in_window.begin(); iter != max_in_window.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
    return 0;
}