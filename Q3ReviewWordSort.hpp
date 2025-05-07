#ifndef Q3REVIEWWORDSORT_HPP
#define Q3REVIEWWORDSORT_HPP

#include "CSVReader.hpp"
#include "DataPreprocessing.hpp"

struct WordCount {
    std::string word;
    int count;
};

class Q3ArraySort {
public:
    void processOneStarReviews(Review* reviews, int count);
    void countWords(const std::string& text, WordCount* wordCounts, int& wordCountSize);
    void quickSort(WordCount arr[], int low, int high);
    void displayTopWords(WordCount* wordCounts, int wordCountSize, int topN);

private:
    int findWordIndex(WordCount* wordCounts, int size, const std::string& word);
    void swap(WordCount& a, WordCount& b);
    int partition(WordCount arr[], int low, int high);
};

#endif
