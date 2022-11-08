#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief 对有序数组进行二分法查找目标对象并返回下表（下表从0开始）。
 *
 * @param nums
 * @param numsLen
 * @param target
 * @return int
 */
int bisection(int* nums, int numsLen, int target ) {
    if (!nums || numsLen <= 0) {
        return -1;
    }

    int left = 0;
    int right = numsLen - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

/**
 * @brief 在二维递增数组中查找（每一维数组的长度一样），且每一行从左到右递增，每一列从上到下递增。
 *
 * @param target
 * @param array
 * @param arrayRowLen
 * @param arrayColLen
 * @return true
 * @return false
 */
bool find(int target, int** array, int arrayRowLen, int* arrayColLen )
{
    if (!array || arrayRowLen == 0 || *arrayColLen == 0) {
        return false;
    }

#if 0
    /* 从左下角向上或向右查找，比target小，则向右移动下标(j++)；比target大，则向上移动下标(i--)  */
    for (int i = arrayRowLen - 1, j = 0; i >= 0 && j <= *arrayColLen - 1; ) {
        printf("arrary[%d][%d] = %d\n", i, j, array[i][j]);
        if (array[i][j] == target) {
            return true;
        } else if (array[i][j] < target) {
            j++;
        } else {
            i--;
        }
    }
#else
    /* 从右上角向下或向左查找，比target小，则向下移动下标（i++）；比target大，则向左移动下标(j--)  */
    for (int i = 0, j = *arrayColLen - 1; i <= arrayRowLen - 1 && j >= 0;) {
        printf("arrary[%d][%d] = %d\n", i, j, array[i][j]);
        if (array[i][j] == target) {
            return true;
        } else if (array[i][j] < target) {
            i++;
        } else {
            j--;
        }
    }
#endif
}

/**
 * @brief 寻找峰值，（峰值左右两边都小于它）。如果有多个峰值，返回其中一个即可。
 *
 * 思路：二分法，结合上升趋势和下降趋势。如果是上升趋势，则移动左下标；如果是下降趋势，则移动右下标。
 *
 * @param nums
 * @param numsLen
 * @return int
 */
int findPeakElement(int* nums, int numsLen)
{
    if (!nums || numsLen < 2) {
        return 0;
    }

    int left = 0;
    int right = numsLen - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        printf("%d <-> %d <-> %d\n", left, mid, right);
        if (nums[mid] < nums[mid + 1]) {
            left = mid + 1;
        } else if (nums[mid] >= nums[mid + 1]) {
            right = mid;
        }
    }

    return left;
}


/**
 * @brief 归并排序（排序并合并）
 *
 * @param data
 * @param tmp
 * @param left
 * @param mid
 * @param right
 */
void merge(int *data, int *tmp, int left, int mid, int right)
{
    int l_tmp = left; // 标记左半区域第一个未排序的下标
    int r_tmp = mid + 1; // 标记右半区域第一个未排序的下标
    int t_index = left; // 临时数组的下标

    /* 开始合并 */
    while (l_tmp <= mid && r_tmp <= right) {
        if (data[l_tmp] < data[r_tmp]) {
            tmp[t_index++] = data[l_tmp++];
        } else {

            // 如果只排序，不统计逆序对，则注释掉
            cnt += mid - l_tmp + 1;

            tmp[t_index++] = data[r_tmp++];
        }
    }

    /* 合并左半区域剩余元素 */
    while (l_tmp <= mid) {
        tmp[t_index++] = data[l_tmp++];
    }

    /* 合并右半区域剩余元素 */
    while (r_tmp <= right) {
        tmp[t_index++] = data[r_tmp++];
    }

    /* 将临时数组数据拷贝到原数组中 */
    while (left <= right) {
        data[left] = tmp[left];
        left++;
    }
}

/**
 * @brief 归并排序（划分）
 *
 * @param data
 * @param tmp
 * @param left
 * @param right
 */
void msort(int *data, int *tmp, int left, int right) {
    // 只有一个元素，就不需要继续划分，直接归并即可
    if (left < right) {
        // 找中间点
        int m_index = left + (right - left) / 2;
        // 递归划分左半区域
        msort(data, tmp, left, m_index);
        // 递归划分右半区域
        msort(data, tmp, m_index + 1, right);

        // 合并已经排序好的部分
        merge(data, tmp, left, m_index, right);
    }
}

/**
 * @brief 归并排序入口
 *
 * @param data
 * @param dataLen
 */
void merge_sort(int *data, int dataLen)
{
    // 分配辅助数组的空间
    int *tmp = (int *)calloc(dataLen, sizeof(int));
    if (tmp) {
        msort(data, tmp, 0, dataLen - 1);
        free(tmp);
    }
}

/**
 * @brief 数组中的逆序对个数
 *
 * @param data
 * @param dataLen
 * @return int
 */
static long cnt = 0;
int InversePairs(int* data, int dataLen )
{
    if (data && dataLen > 1) {
        return 0;
    }

    int *tmp = (int *)calloc(dataLen, sizeof(int));
    if (tmp) {
        msort(data, tmp, 0, dataLen - 1);

        free(tmp);

        return cnt % 1000000007;
    } else {
        return -1;
    }
}

/**
 * @brief 查找旋转数组中的最小数。
 * 旋转数组：有一个长度为 n 的非降序数组，比如[1,2,3,4,5]，将它进行旋转，即把一个数组最开始的若干个元素搬到数组的末尾，
 *          变成一个旋转数组，比如变成了[3,4,5,1,2]，或者[4,5,1,2,3]这样的。
 *
 * 思路：二分法逼近，根据条件限制，始终用中间位置和右边相比较即可。
 * 如果中间位置大于右边的数，那么最小值在右边区域，左边下标右移到 mid+1 位置；
 * 如果中间位置小于右边的数，那么最小值在左边，右边下标左移到 mid 位置（mid可能是最小，所以不是mid-1）。
 * 如果中间位置等于右边的数，那么右边下标左移一个位置。
 *
 * @param rotateArray
 * @param rotateArrayLen
 * @return int
 */
int minNumberInRotateArray(int* rotateArray, int rotateArrayLen )
{
    // 检查参数的有效性
    if (!rotateArray || rotateArrayLen <= 0) {
        return -1;
    }
    if (rotateArrayLen == 1) {
        return rotateArray[0];
    }

    int left = 0;
    int right = rotateArrayLen - 1;
    int mid = 0;

    while (left < right) {
        mid = left + (right - left) / 2;

        if (rotateArray[mid] > rotateArray[right]) {
            left = mid + 1;
        } else if (rotateArray[mid] < rotateArray[right]) {
            right = mid;
        } else {
            right--;
        }
    }

    return rotateArray[left];
}

/**
 * @brief 比较两个版本信息的字符串。
 * version1 > version2 返回1，如果 version1 < version2 返回-1，不然返回0.
 *
 * @param version1
 * @param version2
 * @return int
 */
int compareVersionString(char* version1, char* version2 )
{
    int len1 = strlen(version1);
    int len2 = strlen(version2);

    int v1 = 0;
    int v2 = 0;

    while (v1 < len1 || v2 < len2) {
        int num1 = 0;
        while (v1 < len1 && version1[v1] != '.') {
            num1 = num1 * 10 + version1[v1] - '0';
            v1++;
        }

        v1++;

        int num2 = 0;
        while (v2 < len2 && version2[v2] != '.') {
            num2 = num2 * 10 + version2[v2] - '0';
            v2++;
        }

        v2++;

        if (num1 < num2) {
            return -1;
        } else if (num1 > num2) {
            return 1;
        }
    }

    return 0;
}