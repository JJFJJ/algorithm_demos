/* 算术表达式的求值，输入负数要用（0-正数）表示

思路：考虑到运算符优先级的问题，先读取到的运算符不一定立刻就运算。
不参与运算的运算符和相邻的运算数就分别入栈（俩个栈：运算符栈和运算数栈）。
每读取到一个运算符就和运算符栈的栈顶进行优先级比较，
比栈顶的优先级高的则立刻运算；比栈顶底的，则栈顶出栈进行运算，相等则都出栈丢弃。

对于俩个运算符的处理关系如下表（运算符1处于栈顶，运算2是当前正读取的字符）
运算符1 | 运算符2 | +,- | *,/ | (   | )   | #
--------------------------------------------------
+,-             |  >  |  <  | <   | >   | >
*,/             |  >  |  >  | <   | >   | >
 (              |  <  |  <  | <   | =   | 非法
 )              |  >  |  >  | 非法 | >   | >
 #              |  <  |  <  | <   | 非法 | =

处理逻辑（优先级比较）：
运算符1 < 运算符2，运算符2入栈；
运算符1 > 运算符2，运算符1出栈和俩个运算数运算，结果入栈（运算数栈）；
运算符1 = 运算符2，如果是'('和')'，丢弃运算符1和2。如果是'#'和'#'，表示运算结束退出while循环。

*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

template<typename T>
class Evaluate
{
private:

    /**
     * @brief 比较两个运算符优先级，返回'<','>','='或者程序退出
     *
     * @param op1 处于运算符栈栈顶的运算符。
     * @param op2 当前正处理的运算符。
     * @return char
     */
    char precede(char op1, char op2)
    {
        char result;
        switch (op2) {
        case '+':
        case '-':
            if ('(' == op1 || '#' == op1) {
                result = '<'; // op1 < op2
            } else {
                result = '>'; // op1 > op2
            }
            break;
        case '*':
        case '/':
            if ('*' == op1 || '/' == op1 || ')' == op1) {
                result = '>'; // op1 > op2
            } else {
                result = '<'; // op1 < op2
            }
            break;
        case '(':
            if (')' == op1) {
                cout << "( and ) don't match, exit." << endl;
                abort();
            } else {
                result = '<'; // op1 < op2
            }
            break;
        case ')':
            if ('(' == op1) {
                result = '='; // op1 = op2
            } else if ('#' == op1) {
                cout << "miss \"(\", exit." << endl;
                abort();
            } else {
                result = '>'; // op1 > op2
            }
            break;
        case '#':
            if ('(' == op1) {
                cout << "miss \")\", exit." << endl;
                abort();
            } else if ('#' == op1) {
                result = '='; // op1 = op2
            } else {
                result = '>'; // op1 > op2
            }
            break;
        default:
            cout << "Unspported " << op2 << endl;
            abort();
        }

        return result;
    }

    /**
     * @brief 检查字符是否为运算符，是返回true；否则返回false。
     *
     * @param c
     * @return true
     * @return false
     */
    bool isOperator(char c)
    {
        switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '#':
            return true;
        default:
            return false;
        }
    }

    /**
     * @brief 对俩个操作数进行运算
     *
     * @param a
     * @param op
     * @param b
     * @return T
     */
    T operate(T a, char op, T b)
    {
        switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            cout << "Unspported " << op << endl;
            abort();
        }
    }

public:

    /**
     * @brief 对表达式s进行运算，返回运算结果
     *
     * @param s 表达式的字符串
     * @return T
     */
    T expression(string s)
    {
        // 创建运算符栈和运算数栈
        stack<char> opStack;
        stack<int> numStack;

        // 在运算符栈底添加特殊标识符'#'，用于出栈结束判断
        opStack.push('#');
        // 同样在表达式的字符串后添加特殊表示符'#'，用于判断字符读取结束
        s += '#';

        // 读取表达式的第一个字符
        int i = 0;
        char c = s[i++];

        // 分别记录栈顶运算符，和运算数栈的最上层两个运算数
        int a, b;

        // 开始循环比较表达式的字符和运算符栈顶字符
        while ('#'  != c || '#' != opStack.top()) {
            // 1. 判断表达式的字符是否为运算符
            if (isOperator(c)) {
                // 1.1 c是运算符，和栈顶运算符判断优先级
                switch (precede(opStack.top(), c)) {
                case '>':
                    b = numStack.top();
                    numStack.pop();
                    a = numStack.top();
                    numStack.pop();

                    // 运算结果入栈
                    {
                        cout << "numStack pop " << a << " and " << b << endl;
                        int tmp = operate(a, opStack.top(), b);
                        cout << "numStack push " << tmp << endl;
                        numStack.push(tmp);
                    }

                    opStack.pop();
                    break;
                case '<':
                    opStack.push(c);

                    if (i < s.length()) {
                        c = s[i++];
                    }
                    break;
                case '=':
                    opStack.pop();

                    if (i < s.length()) {
                        c = s[i++];
                    }
                    break;
                default:
                    cout << "Unknow the result of precede" << endl;
                    abort();
                }
            } else {
                // 1.2 c是运算数，记录运算数的值
                if ('0' <= c && c <= '9') {
                    // 连续多位数
                    int d = 0;
                    while ('0' <= c && c <= '9') {
                        d = d * 10 + c - '0';
                        c = s[i++];
                    }
                    cout << "numStack push " << d << endl;
                    numStack.push(d);
                } else {
                    // 既不是运算符也不是运算数
                    cout << "Invalid " << c << endl;
                    abort();
                }
            } // end of if()
        } // end of while()

        a = numStack.top();
        numStack.pop();
        if (!numStack.empty()) {
            cout << "无效的表达式" << endl;
            abort();
        }
        return a;
    }
};

int main()
{
    string s;
    cout << "输入一个算术表达式：" << endl;
    cin >> s;
    Evaluate<int> e;
    cout << " = " << e.expression(s) << endl;

    return 0;
}