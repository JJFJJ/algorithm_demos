/* 将一个十进制数，转换为十六进制数
思路：将这个数除以16，得倒商和余数，记住余数，商继续除以16，等到新的商和新的余数。
重复上面操作，直到商为0。
那么最早得到的余数，在十六进制数的地位；最后得到的余数，在十六进制数的高位。
这个逻辑可以利用栈的先进后出来实现。
*/

#include <iostream>
#include <stack>

using namespace std;

void outputHex(int dec)
{
    stack<int> s;
    int r = 0;
    int d = dec;
    do {
        r = d % 16;
        s.push(r);
        d = d / 16;
    } while (d != 0);

    int i = 0;
    while (!s.empty()) {
        i = s.top();
        s.pop();

        if (i <= 9) {
            cout << i;
        } else {
            char c = 'A' + (i - 10);
            cout << c;
        }
    }
    cout << endl;
}

int main()
{
    int i;
    cout << "Input a decimal positive integer: ";
    cin >> i;
    outputHex(i);

    return 0;
}