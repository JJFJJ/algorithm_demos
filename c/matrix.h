#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 螺旋输出矩阵
 *
 * @param matrix int整型二维数组
 * @param matrixRowLen 数组行数
 * @param matrixColLen 数组列数
 * @param returnSize 返回数组行数
 * @return int* int整型数组
 */
int *spiralOrder(int** matrix, int matrixRowLen, int* matrixColLen, int* returnSize)
{
    int upper = 0; // 上边界
    int bottom = matrixRowLen - 1; // 下边界
    int left = 0; // 左边界
    int right = *matrixColLen - 1; // 右边界

    int len = (*matrixColLen) * matrixRowLen;
    int *arr = (int *)malloc(len * sizeof(int));
    int count = 0;

    while (1) {
        // 从左到右
        for (int i = left; i <= right; i++) {
            arr[count++] = matrix[upper][i];
        }
        if (count >= len) {
            break;
        }
        // 上边界向下移动一位
        upper++;

        // 从上到下
        for (int i = upper; i <= bottom; i++) {
            arr[count++] = matrix[i][right];
        }
        if (count >= len) {
            break;
        }
        // 右边界向左移动一位
        right--;

        // 从右到左
        for (int i = right; i >= left; i--) {
            arr[count++] = matrix[bottom][i];
        }
        if (count >= len) {
            break;
        }
        // 下边界向上移动一位
        bottom--;

        // 从下到上
        for (int i = bottom; i >= upper; i--) {
            arr[count++] = matrix[i][left];
        }
        if (count >= len) {
            break;
        }
        // 左边界向右移动一位
        left++;
    }

    *returnSize = count;
    return arr;
}