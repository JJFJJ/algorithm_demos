#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * @brief 反转一个给的单链表
 *
 * @param pHead
 * @return struct ListNode*
 */
struct ListNode * reverseList(struct ListNode * pHead)
{
    if (!pHead) {
        return NULL;
    }

    struct ListNode *pre = NULL;
    struct ListNode *cur = pHead;

    struct ListNode *tmp = NULL;
    while (cur) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}


/**
 * @brief 链表内指定区域内反转
 *
 * @param head
 * @param m
 * @param n
 * @return struct ListNode*
 */
struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    // 加个虚拟头结点，作用是固定好头结点head的位置（即dummy.next）
    struct ListNode dummy = {
        .val = -1,
        .next = head
    };

    struct ListNode *pre = &dummy;
    for (int i = 0; i < m - 1; i++) {
        pre = pre->next;
    }
    // 找到m结点
    struct ListNode *cur = pre->next;

    // 从m反转到n
    struct ListNode *tmp = NULL;
    for (int i = 0; i < n - m; i++) {
        /* 抽书法 */
        tmp = cur->next;
        cur->next = tmp->next;
        tmp->next = pre->next; // 注：这里不用cur
        pre->next = tmp;
    }

    return dummy.next;
}

/**
 * @brief 链表中的结点，每K个一组反转
 *
 * @param head
 * @param k
 * @return struct ListNode*
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
    struct ListNode *tail = head;

    // 1. 判断递归结束的点
    for (int i = 0; i < k; i++) {
        if (tail) {
            tail = tail->next;
        } else {
            return head;
        }
    }

    // 2. 每次递归的操作过程
    struct ListNode *pre = NULL;
    struct ListNode *cur = head;
    struct ListNode *tmp = NULL;
    while (cur != tail) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    // 3. 下一次递归
    head->next = reverseKGroup(tail, k);

    return pre;
}


/**
 * @brief 合并两个递增链表，合并后依然保持递增排序
 *
 * @param pHead1
 * @param pHead2
 * @return struct ListNode*
 */
struct ListNode * merge(struct ListNode* pHead1, struct ListNode* pHead2)
{
    struct ListNode dummy = {
        .val = -1,
        .next = NULL
    };
    struct ListNode *cur = &dummy;

    while (pHead1 && pHead2) {
        if (pHead1->val <= pHead2->val) {
            // cur->next指向值小的结点
            cur->next = pHead1;
            // cur后移
            cur = pHead1;
            // 链表1的指针也后移
            pHead1 = pHead1->next;
        } else {
            // 同理
            cur->next = pHead2;
            cur = pHead2;
            pHead2 = pHead2->next;
        }
    }
    // 当其中一个链表提前结束时
    cur->next = pHead1 ? pHead1 : pHead2;
    return dummy.next;
}


struct ListNode * divideMerge(struct ListNode ** lists, int left, int right)
{
    if (left > right) {
        return NULL;
    } else if (left == right) {
        return lists[left];
    }

    int mid = left + (right - left) / 2;
    return merge(divideMerge(lists, left, mid), divideMerge(lists, mid + 1, right));
}
/**
 * @brief 合并2个以上的已排序的链表
 *
 * 思路：分治法，将多个列表，按照二分法逐渐划分到最小单元，直到俩俩合并。
 *
 * @param lists
 * @param listsLen
 * @return struct ListNode*
 */
struct ListNode * mergeKLists(struct ListNode** lists, int listsLen)
{
    return divideMerge(lists, 0, listsLen - 1);
}


/**
 * @brief 检查单向链表中是否有循环。
 *
 *  思路：使用快慢指针，如果有环，则俩个指针一定会相遇。否则快指针先到尾结点。
 *
 * @param head
 * @return true
 * @return false
 */
bool hasCycle(struct ListNode* head ) {
    // write code here
    struct ListNode *fast = head;
    struct ListNode *slow = head;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) {
            return true;
        }
    }
    return false;
}


/**
 * @brief 如果链表中有环，则返回环的入口结点，否则返回NULL
 *
 * 思路：按照检查链表是否有环的方法，利用快慢指针。
 * 当快慢指针相遇时，将快指针移到链表的入口，慢指针的速度移动快指针。
 * 当他们再次相遇时，相遇点就是环的入口。
 *
 * 数学逻辑：假设快的速度为2，慢的速度为1，经过单位时间n后相遇。
 * 则快的距离为2n，慢的距离为n。快比慢多移动的距离也为n。
 * 假设第一次相遇点距离环的入口点为x, 那么环的入口与链表的入口距离为：n-x。
 * 所以当快从链表入口以速度1移动时，经过n-x的时间，到达环的入口，
 * 此时慢也整哈移动的距离为n-x。所以当他们再次相遇时，必是环的入口。
 *
 * @param pHead
 * @return struct ListNode*
 */
struct ListNode* entryNodeOfLoop(struct ListNode* pHead ) {
    struct ListNode *fast = pHead;
    struct ListNode *slow = pHead;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) {
            fast = pHead;
            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;
            }
            return fast;
        }
    }
    return NULL;
}


/**
 * @brief 返回链表里最后K个结点
 *
 * 思路：还是快慢指针，这里是快指针先走K步后，慢指针才开始走。俩个移动速度相同。
 *
 * @param pHead
 * @param k
 * @return struct ListNode*
 */
struct ListNode* findKthToTail(struct ListNode* pHead, int k )
{
    if (!pHead) {
        return NULL;
    }

    struct ListNode *fast = pHead;
    struct ListNode *slow = pHead;

    for (int i = 0; i < k; i++) {
        if (!fast) {
            return NULL;
        }
        fast = fast->next;
    }

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}


/**
 * @brief 删除聊表的倒数第N个结点
 *
 * 思路：使用快慢指针，这里需要考虑到N可能指向头结点的位置。
 * 这里添加一个Dummy头结点，始终返回Dummy.next。
 *
 * @param head
 * @param n
 * @return struct ListNode*
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    if (!head) {
        return NULL;
    }
    struct ListNode dummy = {
        .val = -1,
        .next = head
    };
    struct ListNode *fast = &dummy;
    struct ListNode *slow = &dummy;

    for (int i = 0; i < n + 1; i++) {
        if (!fast) {
            return head;
        }
        fast = fast->next;
    }

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    slow->next = slow->next->next;

    return dummy.next;
}


/**
 * @brief 查找两个链表第一个公共结点
 *
 * 思路：定义俩个指针，以相同的速度从两个链表向尾结点移动。当分别移动到尾结点时，再交换链表接续移动。
 * 当他们第一次相遇时，就是两个链表第一个公共结点。
 * 原因是：交换链表移动后，他们最终的移动距离是一样的，那么公共结点的部分就是二者重叠的。
 * 第一次相遇即是第一个公共结点。
 *
 * @param pHead1
 * @param pHead2
 * @return struct ListNode*
 */
struct ListNode* FindFirstCommonNode(struct ListNode* pHead1, struct ListNode* pHead2)
{
    if (!pHead1 || !pHead2) {
        return NULL;
    }

    struct ListNode *p1 = pHead1;
    struct ListNode *p2 = pHead2;

    while (p1 != p2) {
        p1 = p1 ? p1->next : pHead2;
        p2 = p2 ? p2->next : pHead1;
    }

    return p1;
}


/**
 * @brief 两个链表值相加，每个结点的值范围0～9，超过9项前一个结点进一。
 *
 * 思路：链表的方向是从头到尾，但加法运算是从为到头。所以先反转链表，方向与加法一致。
 * 还有一种思路是利用栈结构，两个链表先入栈，然后再出栈。（栈的数据：先进后出，相当于反转的链表）
 * C语言需要自己实现栈，不如直接反转链表。
 *
 * @param head1
 * @param head2
 * @return struct ListNode*
 */
struct ListNode* addInList(struct ListNode* head1, struct ListNode* head2 ) {
    struct ListNode *reP1 = reverseList(head1);
    struct ListNode *reP2 = reverseList(head2);
    if (!reP1 && !reP2) {
        printf("line: %d\n", __LINE__);
        return NULL;
    }

    struct ListNode *head = NULL;
    int carry = 0;
    while (reP1 || reP2 || (0 != carry)) { // 当链表遍历到尾时，如果进位不为0，则需要继续加。
        int val1 = reP1 ? reP1->val : 0;
        int val2 = reP2 ? reP2->val : 0;

        // 新建一个结点存储相加后的值
        struct ListNode *newNode = (struct ListNode *)calloc(0, sizeof(struct ListNode));
        newNode->val = (val1 + val2 + carry) % 10;
        carry = (val1 + val2 + carry) / 10;
        printf("newNode: %p, val: %d\n", newNode, newNode->val);

        // 新结点的next指向之前的新建结点
        newNode->next = head;
        // head头指针指向当前新建结点，保证head始终指向头结点。
        head = newNode;
        printf("head: %p, next: %p\n", head, head->next);

        reP1 = reP1 ? reP1->next : NULL;
        reP2 = reP2 ? reP2->next : NULL;
    }

    return head;
}


/**
 * @brief 在一个单链表里进行排序（按照升序）。
 *
 * 思路：使用分治方法，将链表里每个结点当作一个链表处理，然后按照升序俩俩合并。
 * 这样处理保证了合并后的链表是升序的。然后就回归到之前合并有序链表的操作了。
 * 合并使用递归处理，合并对象分治开。
 *
 * @param head
 * @return struct ListNode*
 */
struct ListNode * sortInList(struct ListNode *head)
{
    // 1.递归的结束条件（将链表拆分到只有一个结点时）
    if (!head || !head->next) {
        return head;
    }

    // 2. 使用左右指针，分别按照不同速率去移动拆分链表
    struct ListNode *left = head;
    struct ListNode *mid = head->next;
    struct ListNode *right = head->next->next;

    while (right && right->next) {
        left = left->next;
        mid = mid->next;
        right = right->next->next;
    }
    left->next = NULL; // 从left指向的结点后续差分开两个

    return merge(sortInList(head), sortInList(mid));
}

/**
 * @brief 判断一个链表是否为回文结构（回文结构：正序和逆序字符信息一致）
 *
 * 思路：由于单链表是单向的，不能从尾到头。可以采用反转链表的方式，那么需要反转的是后一半的链表。
 * 继续利用快慢指针找到中间结点的位置，然后反转后一半。
 * 然后遍历比较前半段链表和反转的后半段链表每个结点是否一致。
 *
 * @param head
 * @return true
 * @return false
 */
bool isPail(struct ListNode* head)
{
    // 检查链表：如果链表为空，或者只有一个结点
    if (!head) {
        return false;
    }
    if (!head->next) {
        return true;
    }

    // 创建快慢指针，快指针每次移动2个单位，慢指针每次移动1个单位
    struct ListNode *fast = head;
    struct ListNode *slow = head;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct ListNode *revsHead = reverseList(slow);
    fast = head;
    slow = revsHead;
    while ((fast != revsHead) && (slow)) { // 此处“fast!=revsHead”的条件和“slow != NULL”一样，判断一个即可
        if (fast->val != slow->val) {
            return false;
        }
        fast = fast->next;
        slow = slow->next;
    }
    return true;
}

/**
 * @brief 链表的奇偶序列结点重新排列，比奇数序号的结点排在链表的前面，偶数序号的结点排在链表的后面
 *
 * 思路：
 *
 * @param head
 * @return struct ListNode*
 */
struct ListNode* oddEvenList(struct ListNode* head) {
    if (!head) {
        return NULL;
    }

    struct ListNode *j = head;
    struct ListNode *o = head->next;
    struct ListNode *o_head = head->next;

    // 偶数序号结点不为空，且后续的奇数序号也不为空，则继续执行循环
    while (o && o->next) {
        j->next = o->next;
        j = j->next;
        o->next = j->next;
        o = o->next;
    }
    j->next = o_head;
    return head;
}


/**
 * @brief 删除有序链表里的重复结点，链表中所有的元素都只出现一次（重复的结点只保留一个）。
 *
 * @param head
 * @return struct ListNode*
 */
struct ListNode* deleteDuplicatesLeftOne(struct ListNode* head)
{
    if (!head) {
        return NULL;
    }

    struct ListNode *cur = head;

    struct ListNode *tmp = NULL;
    while (cur->next) {
        if (cur->val == cur->next->val) {
            tmp = cur->next;
            cur->next = cur->next->next;
            free(tmp);
            tmp = NULL;
        } else {
            cur = cur->next;
        }
    }

    return head;
}

/**
 * @brief 删除有序链表里的重复结点，重复的结点全部删除。
 *
 * 思路：头结点也可能由于重复而被删掉，为了固定头结点的位置，添加一个Dummy结点，Dummy->next指向头结点。
 * 利用cur指向Dummy, 通过cur->next逐步后移，检查结点是否重复。
 * 如果重复cur指向不变，cur->next则不断后移。
 *
 * @param head
 * @return struct ListNode*
 */
struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (!head) {
        return NULL;
    }

    struct ListNode dummy = {
        .val = -1,
        .next = head
    };

    struct ListNode *cur = &dummy;
    struct ListNode *tmp = NULL;

    while (cur->next && cur->next->next) {
        if (cur->next->val == cur->next->next->val) {
            int val = cur->next->val;
            while (cur->next && val == cur->next->val) {
                // 循环找相同结点时，cur指向的结点不变，cur->next依次向后移动指向相同的结点。
                tmp = cur->next;
                cur->next = cur->next->next;
                free(tmp);
                tmp = NULL;
            }
        } else {
            cur = cur->next;
        }
    }

    return dummy.next;
}