#ifndef Q2Q3SEARCHPERFORMANCE_HPP
#define Q2Q3SEARCHPERFORMANCE_HPP

#include "CSVReader.hpp"

void runQ2ArraySequentialTest(Transaction* all, int total);
void runQ2LinkedListTest(Transaction* all, int total);

//Q2 Perf Opt -> Array Sort Algorithm
void runQ2ArraySortTest(Transaction* transaction, int total);

//Q2 Perf Opt -> Linked List Sort Algorithm
void runQ2LinkedListSortTest(Transaction* transactions, int total);

void runQ3ArrayTest(Review* all, int total);
void runQ3LinkedListTest(Review* all, int total);

//Q3 Word Freq Perf -> Array Sort Algorithm
void runQ3ArraySortTest(Review* ewview, int total);

//Q3 Word Freq Perf -> Linked List Sort Algorithm
void runQ3LinkedListSortTest(Review* reviews, int total);

#endif
