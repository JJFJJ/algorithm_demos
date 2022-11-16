/**
 * @file stack_valid_bracket.h
 * @author mysunxianbin@163.com
 * @brief 给出一个仅包含字符'(',')','{','}','['和']',的字符串，判断给出的字符串是否是合法的括号序列
 *        括号必须以正确的顺序关闭，"()"和"()[]{}"都是合法的括号序列，但"(]"和"([)]"不合法。
 *        数据范围：字符串长度 0\le n \le 100000≤n≤10000
 *        要求：空间复杂度 O(n)，时间复杂度 O(n)
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStack {
    int size;
    int length;
    char *base;
} MyStack;

#define MAX_SIZE 10000

MyStack *getStacKInstance()
{
    static MyStack *g_stack = NULL;
    if (!g_stack) {
        g_stack = (MyStack *)calloc(1, sizeof(MyStack));
        g_stack->base = (char *)calloc(MAX_SIZE, sizeof(char));
        g_stack->size = MAX_SIZE;
    }
    return g_stack;
}

bool stack_push(MyStack *st, char value)
{
    if (!st) {
        return false;
    }
    if (st->length >= st->size) {
        printf("stack is full\n");
        return false;
    }

    st->base[st->length++] = value;
    return true;
}

void stack_pop(MyStack *st)
{
    if (!st) {
        return;
    }
    if (st->length <= 0) {
        printf("stack is empty\n");
        return;
    }
    st->length--;
}

bool stack_top(MyStack *st, char *value)
{
    if (!st || !value) {
        return false;
    }
    if (st->length <= 0) {
        printf("stack is empty\n");
        return false;
    }
    *value = st->base[st->length - 1];
    return true;
}

bool stack_empty(MyStack *st)
{
    if (!st) {
        return true;
    }
    return (st->length == 0);
}

bool isValid(char* s ) {
    if (!s || (0 != strlen(s)%2)) {
        return false;
    }
    MyStack *st = getStacKInstance();
    // 清空一下栈
    st->length = 0;
    for (int i = 0; i < strlen(s); i++) {
        switch (s[i]) {
        case '(':
        case '[':
        case '{':
            stack_push(st, s[i]);
            break;
        case ')':
            {
                char top_char;
                if (!stack_top(st, &top_char)) {
                    return false;
                } else {
                    if (top_char != '(') {
                        return false;
                    } else {
                        stack_pop(st);
                    }
                }
            }
            break;
        case ']':
            {
                char top_char;
                if (!stack_top(st, &top_char)) {
                    return false;
                } else {
                    if (top_char != '[') {
                        return false;
                    } else {
                        stack_pop(st);
                    }
                }
            }
            break;
        case '}':
            {
                char top_char;
                if (!stack_top(st, &top_char)) {
                    return false;
                } else {
                    if (top_char != '{') {
                        return false;
                    } else {
                        stack_pop(st);
                    }
                }
            }
            break;
        default:
            printf("Unknow character '%c'\n", s[i]);
            return false;
        }
    }

    return stack_empty(st);
}