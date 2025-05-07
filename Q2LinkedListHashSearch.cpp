#include "Q2LinkedListHashSearch.hpp"
#include "stringUtils.hpp"    // <-- for ::trim() and ::toLower()
#include <iostream>
#include <iomanip>
#include <chrono>

// Step 1: Constructor for HashNodeQ2 to store transaction data
HashNodeQ2::HashNodeQ2(Transaction t) 
{
    data = t;
    next = nullptr;
}

// Step 2: Constructor for LinkedListHashSearchQ2 initializes empty table
LinkedListHashSearchQ2::LinkedListHashSearchQ2() 
{
    for (int i = 0; i < HASH_TABLE_SIZE_Q2; ++i)
        table[i] = nullptr;
}

// Step 3: Destructor calls clear() to release memory
LinkedListHashSearchQ2::~LinkedListHashSearchQ2() 
{
    clear();
}

// Step 4: Hash function using basic polynomial rolling technique
int LinkedListHashSearchQ2::hash(const std::string& key) 
{
    int hashVal = 0;
    for (char c : key)
        hashVal = (hashVal * 31 + c) % HASH_TABLE_SIZE_Q2;
    return hashVal;
}

// Step 5: Combine category and payment as the key
std::string LinkedListHashSearchQ2::toKey(const std::string& category,
                                          const std::string& payment) 
{
    // <-- trim & lowercase both sides before concatenating
    return ::toLower(::trim(category))
         + "+" 
         + ::toLower(::trim(payment));
}

// Step 6: Convert string to lowercase for consistent matching
//    (we keep your member-lowercase for any internal uses, but all keying
//     and matching now goes through stringUtils)
std::string LinkedListHashSearchQ2::toLower(const std::string& s) 
{
    std::string result;
    for (char c : s) result += std::tolower(c);
    return result;
}

// Step 7: Insert transaction into hash table based on category+payment key
void LinkedListHashSearchQ2::insert(Transaction t) 
{
    std::string key = toKey(t.getCategory(), t.getPaymentMethod());
    int index = hash(key);

    HashNodeQ2* newNode = new HashNodeQ2(t);
    newNode->next = table[index];
    table[index] = newNode;
}

// Step 8: Search and display Electronics + Credit Card transactions and percentage
void LinkedListHashSearchQ2::searchElectronicsCreditCard() 
{
    // <-- build the lookup index using the same trimmed/lowercase rule:
    std::string key   = "electronics+credit card";
    int         index = hash(key);

    HashNodeQ2* node              = table[index];
    bool        found             = false;
    int         totalElectronics  = 0;
    int         electronicsCredit = 0;

    // Step 9: First pass to count total Electronics transactions
    for (int i = 0; i < HASH_TABLE_SIZE_Q2; ++i) {
        for (HashNodeQ2* curr = table[i]; curr; curr = curr->next) {
            // <-- trim & lowercase before comparing
            std::string cat = ::toLower(::trim(curr->data.getCategory()));
            if (cat == "electronics") {
                totalElectronics++;
            }
        }
    }

    // Step 10: Count matching Electronics + Credit Card and display percentage
    std::cout << std::fixed << std::setprecision(2);
    if (totalElectronics > 0) 
    {
        for (HashNodeQ2* countPtr = table[index]; countPtr; countPtr = countPtr->next) 
        {
            std::string cat = ::toLower(::trim(countPtr->data.getCategory()));
            std::string pay = ::toLower(::trim(countPtr->data.getPaymentMethod()));
            if (cat == "electronics" && pay == "credit card") {
                electronicsCredit++;
            }
        }

        double percentage = (100.0 * electronicsCredit) / totalElectronics;
        std::cout << "\nPercentage of Electronics purchases made with Credit Card: "
                  << percentage << "%\n\n";
    }
    else 
    {
        std::cout << "\nNo Electronics transactions found in the dataset.\n";
        return;
    }

    // Step 11: Display table header
    std::cout << "Matching Transactions (Electronics + Credit Card):\n"
              << "---------------------------------------------------------------------------------------------\n"
              << std::left
              << std::setw(15) << "Customer ID"
              << std::setw(20) << "Product"
              << std::setw(15) << "Category"
              << std::setw(10) << "Price"
              << std::setw(15) << "Date"
              << std::setw(20) << "Payment Method" << "\n"
              << "---------------------------------------------------------------------------------------------\n";

    // Step 12: Loop and print matching transactions
    for (; node; node = node->next) 
    {
        auto cat = ::toLower(::trim(node->data.getCategory()));
        auto pay = ::toLower(::trim(node->data.getPaymentMethod()));
        if (cat == "electronics" && pay == "credit card") 
        {
            std::cout << std::left
                      << std::setw(15) << node->data.getCustomerID()
                      << std::setw(20) << node->data.getProduct()
                      << std::setw(15) << node->data.getCategory()
                      << std::setw(10) << node->data.getPrice()
                      << std::setw(15) << node->data.getDate()
                      << std::setw(20) << node->data.getPaymentMethod()
                      << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No Electronics transactions paid by Credit Card found.\n";
    }

    std::cout << "---------------------------------------------------------------------------------------------\n";
}

// Step 13: Clear all hash table nodes to free memory
void LinkedListHashSearchQ2::clear() 
{
    for (int i = 0; i < HASH_TABLE_SIZE_Q2; ++i) 
    {
        HashNodeQ2* current = table[i];
        while (current) 
        {
            HashNodeQ2* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}
