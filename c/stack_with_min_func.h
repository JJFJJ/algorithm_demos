/**
 * @file stack_with_min_func.h
 * @author mysunxianbin@163.com
 * @brief 定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的 min 函数，
 *        输入操作时保证 pop、top 和 min 函数操作时，栈中一定有元素。
 *        进阶：栈的各个操作的时间复杂度是 O(1)  ，空间复杂度是 O(n).
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct MyStack {
    int size;
    int length;
    int *base;
    struct ListNode *head;
} MyStack;

#define MAX_SIZE 300

MyStack *getStackInstance()
{
    static MyStack *g_stack = NULL;
    if (!g_stack) {
        g_stack = (MyStack *)calloc(1, sizeof(MyStack));
        g_stack->base = (int *)calloc(MAX_SIZE, sizeof(int));
        g_stack->size = MAX_SIZE;
        g_stack->length = 0;
        g_stack->head = (struct ListNode *)calloc(1, sizeof(struct ListNode));
    }
    return g_stack;
}

void push(int value ) {
    MyStack *s = getStackInstance();
    if (s->length >= s->size) {
        printf("stack is full\n");
        return;
    }
    s->base[s->length++] = value;
    printf("push %d\n", value);

    struct ListNode *node = (struct ListNode *)calloc(1, sizeof(struct ListNode));
    node->val = value;
    struct ListNode *pre = s->head;
    struct ListNode *tmp = pre->next;
    while (tmp) {
        if (value <= tmp->val) {
            pre->next = node;
            node->next = tmp;
            return;
        } else {
            pre = pre->next;
            tmp = pre->next;
        }
    }
    pre->next = node;
}

void pop() {
    MyStack *s = getStackInstance();
    if (s->length <= 0) {
        printf("stack is empty\n");
        return;
    }
    int value = s->base[s->length - 1];
    s->length--;
    printf("pop %d and ...\n", value);
    struct ListNode *pre = s->head;
    struct ListNode *tmp = pre->next;
    while (tmp) {
        printf("\t compare with %d ...\n", tmp->val);
        if (value == tmp->val) {
            printf("\t\t and match to free it\n");
            pre->next = tmp->next;
            free(tmp);
            return;
        } else {
            pre = pre->next;
            tmp = pre->next;
        }
    }
}

int top() {
    MyStack *s = getStackInstance();
    if (s->length <= 0) {
        printf("stack is empty\n");
        abort();
    }
    return s->base[s->length - 1];
}

int min() {
    MyStack *s = getStackInstance();
    if (s->length <= 0) {
        printf("stack is empty\n");
        abort();
    }
    return s->head->next->val;
}