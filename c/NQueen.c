#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**
    用二维数组来记录放置皇后的位置，棋盘初始值为-1。
    当array[x][y]位置放置皇后时，x行和y列都全部置为x，斜线也置为x。
    当array[x][y]位置移除皇后时，x行、y列、斜线为x的全部恢复为-1.
*/

static int N = 0;
static int **ARRAY = NULL;
static int solve_count = 0;

// 在[x][y]位置放置（flag=true）或移除（flag=true）皇后时，
// 在所在的行，列，斜线做标记。
void Mark(int x, int y, bool flag)
{
    int target; // 寻找的目标值
    int flag_value; // 对应的标记值
    if (flag) {
        target = -1;
        flag_value = x;
    } else {
        target = x;
        flag_value = -1;
    }

    // 更新皇后(x, y)所在行的标记
    for (int i = 0; i < N; ++i) {
        // 固定行，更新列
        if (ARRAY[x][i] == target) {
            ARRAY[x][i] = flag_value;
        }
    }

    // 更新皇后(x, y)所在列和斜线的标记
    for (int i = x + 1; i < N; ++i) {
        // 固定列，更新行
        if (ARRAY[i][y] == target) {
            ARRAY[i][y] = flag_value;
        }
        // 更新"\"方向斜线
        if (0 <= (y + (i - x)) && (y + (i - x)) < N
                && ARRAY[i][y + (i - x)] == target) {
            ARRAY[i][y + (i - x)] = flag_value;
        }
        // 更新"/"方向斜线
        if (0 <= (y - (i - x)) && (y - (i - x) < N)
                && ARRAY[i][y - (i - x)] == target) {
            ARRAY[i][y - (i - x)] = flag_value;
        }
    }
}

void QueenByRecursion(int x) {
    if (x < N) {
        for (int i = 0; i < N; ++i) {
            if (ARRAY[x][i] == -1) {
                Mark(x, i, true);
                QueenByRecursion(x + 1);
                Mark(x, i, false);
            }
        }
    } else {
        solve_count++;
    }
}

void QueueNoRecursion()
{
    int x = 0;
    int y = 0;
    int *solution = (int *)calloc(N, sizeof(int)); // 用于存放皇后放置的列坐标
    while (x >= 0) {
        while (y < N) {
            // 寻找某一行，放置皇后的位置
            if (ARRAY[x][y] == -1) {
                // 找到放置皇后的位置
                break;
            } else {
                y++;
            }
        }

        if (y < N) {
            Mark(x, y, true);
            solution[x] = y;

            if (x == N - 1) {
                // 放完最后一个皇后
                solve_count++;
                // 移除最后一个皇后
                Mark(x, y, false);

                // 回退到上一个皇后放置并移除
                x--;
                if (x >= 0) {
                    y = solution[x];
                    Mark(x, y, false);
                    // 行不变，列继续往后寻找
                    y++;
                }
            } else {
                // 寻找一下行放置皇后的位置
                x++;
                y = 0;
            }
        } else {
            // 该行的所有列都无法放置皇后，回退到上一行，并移除皇后
            x--;
            if (x >= 0) {
                y = solution[x];
                Mark(x, y, false);
                y++; // 列往后移，继续寻找
            }
        }
    }
}


/**
 *
 * @param n int整型 the n
 * @return int整型
 */
int Nqueen(int n ) {
    // 初始化棋盘
    N = n;
    ARRAY = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < N; ++i) {
        ARRAY[i] = (int *)malloc(n * sizeof(int *));
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ARRAY[i][j] = -1;
        }
    }

#if 0
    QueenByRecursion(0);
#else
    QueueNoRecursion();
#endif

    return solve_count;
}

int main()
{
    int n;
    printf("Input the Queens' number: ");
    scanf("%d", &n);
    int result = Nqueen(n);
    printf("And It has %d solution%s.\n", result, result == 1 ? "" : "s");

    return 0;
}