#include "Q3ReviewWordSort.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

void Q3ArraySort::processOneStarReviews(Review* reviews, int count) {
    WordCount wordCounts[1000];
    int wordCountSize = 0;

    for (int i = 0; i < count; ++i) {
        if (reviews[i].getRating() == "1") {
            countWords(reviews[i].getReviewText(), wordCounts, wordCountSize);
        }
    }

    quickSort(wordCounts, 0, wordCountSize - 1);
    displayTopWords(wordCounts, wordCountSize, 10); // Top 10 words
}

void Q3ArraySort::countWords(const string& text, WordCount* wordCounts, int& wordCountSize) {
    istringstream stream(text);
    string word;
    while (stream >> word) {
        string cleanWord = "";
        for (char ch : word) {
            if (isalpha(ch)) cleanWord += tolower(ch);
        }

        if (cleanWord.empty()) continue;

        int index = findWordIndex(wordCounts, wordCountSize, cleanWord);
        if (index != -1) {
            wordCounts[index].count++;
        }
        else {
            wordCounts[wordCountSize++] = { cleanWord, 1 };
        }
    }
}

int Q3ArraySort::findWordIndex(WordCount* wordCounts, int size, const string& word) {
    for (int i = 0; i < size; ++i) {
        if (wordCounts[i].word == word)
            return i;
    }
    return -1;
}

void Q3ArraySort::swap(WordCount& a, WordCount& b) {
    WordCount temp = a;
    a = b;
    b = temp;
}

int Q3ArraySort::partition(WordCount arr[], int low, int high) {
    int pivot = arr[high].count;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].count > pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Q3ArraySort::quickSort(WordCount arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void Q3ArraySort::displayTopWords(WordCount* wordCounts, int wordCountSize, int topN) {
    cout << "Top " << topN << " most frequent words in 1-star reviews:\n";
    for (int i = 0; i < topN && i < wordCountSize; ++i) {
        cout << wordCounts[i].word << ": " << wordCounts[i].count << endl;
    }
}
