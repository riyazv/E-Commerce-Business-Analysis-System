#ifndef Q1_LINKED_LIST_SORT_HPP
#define Q1_LINKED_LIST_SORT_HPP

#include "CSVReader.hpp"

struct ListNode {
    Transaction data;
    ListNode*   next;
    ListNode(const Transaction& t) : data(t), next(nullptr) {}
};

inline ListNode* buildList(Transaction* arr, int size) {
    if (size <= 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* tail = head;
    for (int i = 1; i < size; ++i) {
        tail->next = new ListNode(arr[i]);
        tail = tail->next;
    }
    return head;
}

inline ListNode* merge(ListNode* a, ListNode* b) {
    ListNode dummy{ Transaction() };

    ListNode* tail = &dummy;
    while (a && b) {
        if (a->data.getDate() < b->data.getDate()) {
            tail->next = a; a = a->next;
        } else {
            tail->next = b; b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

inline ListNode* mergeSortNode(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* mid = slow->next;
    slow->next = nullptr;
    return merge(mergeSortNode(head), mergeSortNode(mid));
}

//Q1 -> Linked List Sort Alg
inline void sortTransactionsLinkedList(Transaction* arr, int size) {
    ListNode* head = buildList(arr, size);
    head = mergeSortNode(head);
    for (int i = 0; i < size && head; ++i, head = head->next) {
        arr[i] = head->data;
    }
}

#endif // Q1_LINKED_LIST_SORT_HPP
