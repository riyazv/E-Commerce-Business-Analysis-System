#include <iostream>
#include <iomanip>
#include "CSVReader.hpp"
#include "DataPreprocessing.hpp"
#include "Q2ArraySearch.hpp"
#include "Q3ArraySearch.hpp"
#include "Q2LinkedListHashSearch.hpp"
#include "Q3LinkedListHashSearch.hpp"
#include "PerformanceHelper.hpp"
#include "Q2Q3SearchPerformance.hpp"
#include "Q1ArraySort.hpp"
#include "Q2SortHelper.hpp"
#include "Q3ReviewWordSort.hpp"
#include "Q1LinkedListSort.hpp"
#include "Q2_LinkedListFilter.hpp"
#include "Q3_LinkedListFilter.hpp"
#include "Q3ReviewWordSort.hpp"
#include "stringUtils.hpp"
#include "Q1_SortPerformance.hpp"

void displayMainMenu() 
{
    std::cout << "\n=========== E-Commerce System Main Menu ============\n";
    std::cout << "1. Access Questions (Q1-Q3)\n";
    std::cout << "2. Performance Comparison\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void displayQuestionMenu() 
{
    std::cout << "\n========= Questions Menu =========\n";
    std::cout << "1. Question 1: Sort transactions by date\n";
    std::cout << "2. Question 2: Filter Electronics + Credit Card\n";
    std::cout << "3. Question 3: 1-star review word analysis\n";
    std::cout << "4. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayQuestion1Menu() 
{
    std::cout << "\n--- Question 1 Options ---\n";
    std::cout << "1. Array Sort Algorithm\n";
    std::cout << "2. Linked List Sort Algorithm\n";
    std::cout << "3. Back to Question Menu\n";
    std::cout << "4. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayQuestion2Menu() 
{
    std::cout << "\n--- Question 2 Options ---\n";
    std::cout << "1. Array Sequential Search Algorithm\n";
    std::cout << "2. LinkedList Hash Table Search Algorithm\n";
    std::cout << "3. Array Sort Algorithm\n";
    std::cout << "4. Linked List Sort Algorithm\n";
    std::cout << "5. Back to Question Menu\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayQuestion3Menu() 
{
    std::cout << "\n--- Question 3 Options ---\n";
    std::cout << "1. Array Hash Table Search Algorithm\n";
    std::cout << "2. LinkedList Hash Table Search Algorithm\n";
    std::cout << "3. Array Sort Algorithm\n";
    std::cout << "4. Linked List Sort Algorithm\n";
    std::cout << "5. Back to Question Menu\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayPerformanceMenu() 
{
    std::cout << "\n========= Performance Comparison Menu =========\n";
    std::cout << "1. Question 1: Sort Comparison\n";
    std::cout << "2. Question 2: Search & Sort Comparison\n";
    std::cout << "3. Question 3: Search & Sort Comparison\n";
    std::cout << "4. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayQ1PerformanceMenu() 
{
    std::cout << "\n--- Q1 Sort Performance ---\n";
    std::cout << "1. Array Sort Algorithm\n";
    std::cout << "2. Linked List Sort Algorithm\n";
    std::cout << "3. Back to Performance Menu\n";
    std::cout << "4. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayQ2PerformanceMenu() 
{
    std::cout << "\n--- Q2 Performance Options ---\n";
    std::cout << "1. Array Sequential Search Algorithm\n";
    std::cout << "2. LinkedList Hash Table Search Algorithm\n";
    std::cout << "3. Array Sort Algorithm\n";
    std::cout << "4. Linked List Sort Algorithm\n";
    std::cout << "5. Back to Performance Menu\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayQ3PerformanceMenu() 
{
    std::cout << "\n--- Q3 Word Frequency Performance ---\n";
    std::cout << "1. Array Hash Table Search Algorithm\n";
    std::cout << "2. LinkedList Hash Table Search Algorithm\n";
    std::cout << "3. Array Sort Algorithm\n";
    std::cout << "4. Linked List Sort Algorithm\n";
    std::cout << "5. Back to Performance Menu\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayAllTransactions(Transaction* arr, int size) {
    std::cout << std::left
              << std::setw(12) << "Date"
              << std::setw(15) << "CustomerID"
              << std::setw(20) << "Product"
              << std::setw(10) << "Price"
              << std::setw(15) << "Category"
              << std::setw(20) << "Payment"
              << "\n"
              << std::string(92, '-') << "\n";
    for (int i = 0; i < size; ++i) {
        auto& t = arr[i];
        std::cout << std::left
                  << std::setw(12) << t.getDate()
                  << std::setw(15) << t.getCustomerID()
                  << std::setw(20) << t.getProduct()
                  << std::setw(10) << t.getPrice()
                  << std::setw(15) << t.getCategory()
                  << std::setw(20) << t.getPaymentMethod()
                  << "\n";
    }
    std::cout << std::string(92, '-') << "\n";
}


int main() 
{
    CSVReader reader;
    reader.readTransactions("transactions.csv");
    std::cout << "transactions.csv imported and read successfully!" << std::endl;

    reader.readReviews("reviews.csv");
    std::cout << "reviews.csv imported and read successfully!" << std::endl;

    std::cout << "\nStarting data preprocessing..." << std::endl;

    DataPreprocessing preprocessor;
    preprocessor.cleanTransactions(reader.getTransactions(), reader.getTransactionCount());
    preprocessor.cleanReviews(reader.getReviews(), reader.getReviewCount());

    int originalTrans = reader.getTransactionCount();
    int cleanedTrans = preprocessor.getCleanedTransactionCount();
    int removedTrans = originalTrans - cleanedTrans;

    int originalReviews = reader.getReviewCount();
    int cleanedReviews = preprocessor.getCleanedReviewCount();
    int removedReviews = originalReviews - cleanedReviews;

    std::cout << "Transactions: After data cleaning, total rows = "
        << cleanedTrans << " (Removed " << removedTrans << " rows)" << std::endl;
    std::cout << "Reviews: After data cleaning, total rows = "
        << cleanedReviews << " (Removed " << removedReviews << " rows)" << std::endl;
    std::cout << "Data preprocessing completed!\n" << std::endl;

    Transaction* cleanedTransList = preprocessor.getCleanedTransactions();
    Review* cleanedReviewList = preprocessor.getCleanedReviews();

    int mainChoice, qChoice, qSubChoice;
    do 
    {
        displayMainMenu();
        std::cin >> mainChoice;
        std::cin.ignore();

        switch (mainChoice) 
        {
        case 1:
            do 
            {
                displayQuestionMenu();
                std::cin >> qChoice;
                std::cin.ignore();

                switch (qChoice) 
                {
                case 1:
                    do 
                    {
                        displayQuestion1Menu();
                        std::cin >> qSubChoice;
                        std::cin.ignore();
                        switch (qSubChoice) 
                        {
                        case 1:
                            Q1ArrayDateSort sorter;
                            sorter.quickSortByDate(cleanedTransList, 0, cleanedTrans - 1);
                            std::cout << "Top 5 transactions after sorting by date (Array):\n";
                            for (int i = 0; i < 5 && i < cleanedTrans; ++i) {
                                cleanedTransList[i].displayTransaction();  // Using displayTransaction() from Transaction class
                            }
                            break;
                        case 2:
                            std::cout << "\n--- Q1: Linked List Sort by Date ---\n";
                            sortTransactionsLinkedList(cleanedTransList, cleanedTrans);
                            displayAllTransactions(cleanedTransList, cleanedTrans);
                            break;
                        case 3:
                            break;
                        case 4:
                            qChoice = 4;
                            break;
                        default:
                            std::cout << "Invalid option. Try again.\n";
                        }
                    } while (qSubChoice != 3 && qSubChoice != 4);
                    break;
                case 2:
                    do 
                    {
                        displayQuestion2Menu();
                        std::cin >> qSubChoice;
                        std::cin.ignore();
                        switch (qSubChoice) 
                        {
                            case 1:
                            {
                                double percentage = calculateElectronicsCreditCardPercentage(cleanedTransList, cleanedTrans);
                                std::cout << "\nPercentage of Electronics purchases made with Credit Card: "
                                    << std::fixed << std::setprecision(2)
                                    << percentage << "%\n";
                                displayMatchingTransactions(cleanedTransList, cleanedTrans);
                            }
                            break;
                            case 2:
                            {
                                LinkedListHashSearchQ2 hashSearchQ2;
                                for (int i = 0; i < cleanedTrans; ++i) 
                                {
                                    hashSearchQ2.insert(cleanedTransList[i]);
                                }
                                hashSearchQ2.searchElectronicsCreditCard();
                            }
                            break;
                            case 3:
                            {  
                                sortAndDisplayQ2Array(cleanedTransList, cleanedTrans);
                                break;
                            }
                            case 4:
                            {
                                std::cout << "\n-------------- Q2: Electronics + Credit Card Sorted by Date [Linked List Sort] -------------\n";
                                sortAndDisplayQ2List(cleanedTransList, cleanedTrans);
                                break;
                            }
                            case 5:
                            {
                                break;
                            }
                            case 6:
                            {
                                qChoice = 4;
                                break;
                            }
                            default:
                            {
                                std::cout << "Invalid option. Try again.\n";
                            }
                        }
                    } while (qSubChoice != 5 && qSubChoice != 6);
                    break;
                case 3:
                    do 
                    {
                        displayQuestion3Menu();
                        std::cin >> qSubChoice;
                        std::cin.ignore();
                        switch (qSubChoice) 
                        {
                        case 1:
                            analyzeArrayReviews(cleanedReviewList, cleanedReviews);
                            break;
                        case 2:
                        {
                            LinkedListHashSearchQ3 hashSearchQ3;
                            hashSearchQ3.processOneStarReviews(cleanedReviewList, cleanedReviews);
                            hashSearchQ3.displayTopWords(10);
                        }
                        break;
                        case 3:
                            Q3ArraySort arraySortQ3;
                            arraySortQ3.processOneStarReviews(cleanedReviewList, cleanedReviews);
                            break;
                        case 4: 
                        {
                            //Build the hash table of 1-star words
                            LinkedListHashSearchQ3 hashQ3;
                            hashQ3.processOneStarReviews(cleanedReviewList, cleanedReviews);

                            //Pull all WordNode chains into a single list
                            WordNode* head = hashQ3.releaseWordList();

                            //Display the top 10 and free the nodes
                            sortAndDisplayWordCounts(head, 10);
                            break;
                        }

                        case 5:
                            break;
                        case 6:
                            qChoice = 4;
                            break;
                        default:
                            std::cout << "Invalid option. Try again.\n";
                        }
                    } while (qSubChoice != 5 && qSubChoice != 6);
                    break;
                case 4:
                    break;
                default:
                    std::cout << "Invalid option. Try again.\n";
                }
            } while (qChoice != 4);
            break;
        case 2:
            do 
            {
                displayPerformanceMenu();
                std::cin >> qChoice;
                std::cin.ignore();
                switch (qChoice) 
                {
                case 1:
                    do 
                    {
                        displayQ1PerformanceMenu();
                        std::cin >> qSubChoice;
                        std::cin.ignore();
                        switch (qSubChoice) 
                        {
                        case 1:
                            runQ1ArraySortTest(cleanedTransList, cleanedTrans);
                            break;
                        case 2:
                            runQ1LinkedListSortTest(cleanedTransList, cleanedTrans);
                            break;
                        case 3:
                            break;
                        case 4:
                            qChoice = 4;
                            break;
                        default:
                            std::cout << "Invalid Option, try again(1-4).\n" << std::endl;
                        }
                    } while (qSubChoice != 3 && qSubChoice != 4);
                    break;
                case 2:
                    do 
                    {
                        displayQ2PerformanceMenu();
                        std::cin >> qSubChoice;
                        std::cin.ignore();
                        switch (qSubChoice) 
                        {
                        case 1:
                            runQ2ArraySequentialTest(cleanedTransList, cleanedTrans);
                            break;
                        case 2:
                            runQ2LinkedListTest(cleanedTransList, cleanedTrans);
                            break;
                        case 3:
                            runQ2ArraySortTest(cleanedTransList, cleanedTrans);
                            break;
                        case 4:
                            runQ2LinkedListSortTest(cleanedTransList, cleanedTrans);
                            break;
                        case 5:
                            break;
                        case 6:
                            qChoice = 4;
                            break;
                        }
                    } while (qSubChoice != 5 && qSubChoice != 6);
                    break;
                case 3:
                    do 
                    {
                        displayQ3PerformanceMenu();
                        std::cin >> qSubChoice;
                        std::cin.ignore();
                        switch (qSubChoice) 
                        {
                        case 1:
                            runQ3ArrayTest(cleanedReviewList, cleanedReviews);
                            break;
                        case 2:
                            runQ3LinkedListTest(cleanedReviewList, cleanedReviews);
                            break;
                        case 3:
                            runQ3ArraySortTest(cleanedReviewList, cleanedReviews);
                            break;
                        case 4:
                            runQ3LinkedListSortTest(cleanedReviewList, cleanedReviews);
                            break;
                        case 5:
                            break;
                        case 6:
                            qChoice = 4;
                            break;
                        }
                    } while (qSubChoice != 5 && qSubChoice != 6);
                    break;
                case 4:
                    break;
                default:
                    std::cout << "Invalid option. Try again.\n";
                }
            } while (qChoice != 4);
            break;
        case 3:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid option. Try again.\n";
        }
    } while (mainChoice != 3);

    return 0;
}
