#ifndef Q1_SORT_PERFORMANCE_HPP
#define Q1_SORT_PERFORMANCE_HPP

#pragma once
#include "CSVReader.hpp"

//Prints avg time and memory used for the array sorting
void runQ1ArraySortTest(Transaction* all, int total);

//Prints avg time and memory used for the linked list
void runQ1LinkedListSortTest(Transaction* all, int total);

#endif