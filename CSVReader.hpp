// CSVReader.hpp
#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <string>
#include <fstream>
#include <iostream>

static constexpr int MAX_ROWS = 5001;

class Transaction {
private:
    std::string customerID;
    std::string product;
    std::string category;
    std::string price;
    std::string date;
    std::string paymentMethod;

public:
    Transaction();
    Transaction(const std::string& custID,
                const std::string& prod,
                const std::string& cat,
                const std::string& prc,
                const std::string& dt,
                const std::string& pay);

    void setData(const std::string& custID,
                 const std::string& prod,
                 const std::string& cat,
                 const std::string& prc,
                 const std::string& dt,
                 const std::string& pay);

    std::string getCustomerID()    const;
    std::string getProduct()       const;
    std::string getCategory()      const;
    std::string getPrice()         const;
    std::string getDate()          const;
    std::string getPaymentMethod() const;

    void displayTransaction() const {
        std::cout << "Customer ID: "   << customerID
                  << ", Product: "     << product
                  << ", Category: "    << category
                  << ", Price: "       << price
                  << ", Date: "        << date
                  << ", Payment: "     << paymentMethod
                  << std::endl;
    }
};

class Review {
private:
    std::string productID;
    std::string customerID;
    std::string rating;
    std::string reviewText;

public:
    Review();
    Review(const std::string& prodID,
           const std::string& custID,
           const std::string& rt,
           const std::string& rev);

    void setData(const std::string& prodID,
                 const std::string& custID,
                 const std::string& rt,
                 const std::string& rev);

    std::string getProductID()  const;
    std::string getCustomerID() const;
    std::string getRating()     const;
    std::string getReviewText() const;
};

class CSVReader {
private:
    Transaction* transactions;
    Review*      reviews;
    int          transactionCount;
    int          reviewCount;

public:
    CSVReader();
    ~CSVReader();

    void readTransactions(const std::string& filename);
    void readReviews(const std::string& filename);

    Transaction* getTransactions()     const;
    int          getTransactionCount() const;
    Review*      getReviews()          const;
    int          getReviewCount()      const;
};

#endif // CSVREADER_HPP
