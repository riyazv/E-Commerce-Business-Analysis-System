#ifndef Q3_LINKED_LIST_FILTER_HPP
#define Q3_LINKED_LIST_FILTER_HPP

#include <iostream>
#include <iomanip>
#include "Q3LinkedListHashSearch.hpp"

// split list into front/back halves
inline void splitList(WordNode* source,
                      WordNode** frontRef, WordNode** backRef) {
    WordNode* slow = source;
    WordNode* fast = source ? source->next : nullptr;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef  = slow ? slow->next : nullptr;
    if (slow) slow->next = nullptr;
}

// merge two sorted lists (by count desc)
inline WordNode* sortedMerge(WordNode* a, WordNode* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->count >= b->count) {
        a->next = sortedMerge(a->next, b);
        return a;
    } else {
        b->next = sortedMerge(a, b->next);
        return b;
    }
}

// main mergeSort entry
inline void mergeSort(WordNode** headRef) {
    WordNode* head = *headRef;
    if (!head || !head->next) return;
    WordNode *a, *b;
    splitList(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headRef = sortedMerge(a, b);
}

//Q3 -> Linked List Sort Algorithm
inline void sortAndDisplayWordCounts(WordNode* head, int topN) {
    
    mergeSort(&head);

    //design
    const int wordCol = 15;
    const int countCol = 7;
    const std::string sep = "+" + std::string(wordCol + 2, '-') + "+" + std::string(countCol + 2, '-') + "+";

    std::cout << "\n Top " << topN << " Frequent Words (Linked-List Sort)\n"
            << sep << "\n" << "| " << std::left << std::setw(wordCol) 
            << "Word" << " | " << std::right << std::setw(countCol) 
            << "Count" << " |\n" << sep << "\n";

    //Print topN rows
    WordNode* cur = head;
    for (int i = 0; cur && i < topN; ++i, cur = cur->next) {
        std::cout << "| " << std::left << std::setw(wordCol) << cur->word
                  << " | " << std::right << std::setw(countCol) << cur->count
                  << " |\n";
    }

    // 5) Footer line
    std::cout << sep << "\n";

    // 6) Free the list
    while (head) {
        WordNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}


#endif // Q3_LINKED_LIST_SORT_HPP
