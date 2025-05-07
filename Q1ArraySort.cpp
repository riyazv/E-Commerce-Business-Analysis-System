#include "Q1ArraySort.hpp"
#include <iostream>
#include <string> 

int partition(Transaction* arr, int low, int high) {
    std::string pivot = arr[high].getDate();
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j].getDate() < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Transaction* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sortTransactionsByDate(Transaction* transactions, int count) {
    quickSort(transactions, 0, count - 1);
}

void printTransactions(const Transaction* transactions, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << transactions[i].getDate() << " | "
            << transactions[i].getCustomerID() << " | "
            << transactions[i].getProduct() << std::endl;
    }
}
