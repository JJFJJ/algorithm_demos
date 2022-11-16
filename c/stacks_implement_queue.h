/**
 * @file impl_queue_2_stacks.h
 * @author mysunxianbin@163.com
 * @brief 用俩个栈实现队列
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000
typedef struct MyStack {
    int size;
    int length;
    int *base;
} MyStack;

static MyStack *g_stack1 = NULL;
static MyStack *g_stack2 = NULL;

void CreateStack()
{
    if (!g_stack1) {
        g_stack1 = (MyStack *)calloc(1, sizeof(MyStack));
        int *arr = (int *)calloc(MAX_SIZE, sizeof(int));
        g_stack1->size = MAX_SIZE;
        g_stack1->base = arr;
        g_stack1->length = 0;
    }
    if (!g_stack2) {
        g_stack2 = (MyStack *)calloc(1, sizeof(MyStack));
        int *arr = (int *)calloc(MAX_SIZE, sizeof(int));
        g_stack2->size = MAX_SIZE;
        g_stack2->base = arr;
        g_stack2->length = 0;
    }
}

void push(int node)
{
    CreateStack();

    if (g_stack1->length >= g_stack1->size) {
        printf("stack is full\n");
        return;
    }

    g_stack2->length = 0; // 清空g_stack2
    // g_stack1全部出栈进到g_stack2，node进站，然后g_stack2再全部出栈进入g_stack1
    for (int i = 0; i < g_stack1->length; i++) {
        g_stack2->base[i] = g_stack1->base[i];
    }
    g_stack2->length = g_stack1->length;
    g_stack1->length = 0;

    g_stack1->base[0] = node;
    g_stack1->length++;

    for (int i = 0; i < g_stack2->length; ) {
        g_stack1->base[g_stack1->length++] = g_stack2->base[i++];
    }
}

int pop() {
    int top = g_stack1->base[g_stack1->length - 1];
    g_stack1->length--;
    return top;
}