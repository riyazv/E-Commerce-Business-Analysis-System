// CSVReader.cpp
#include "CSVReader.hpp"
#include <sstream>
#include <fstream>

// --- Transaction implementations ---
Transaction::Transaction()
  : customerID(), product(), category(),
    price(), date(), paymentMethod()
{ }

Transaction::Transaction(const std::string& custID,
                         const std::string& prod,
                         const std::string& cat,
                         const std::string& prc,
                         const std::string& dt,
                         const std::string& pay)
  : customerID(custID)
  , product(prod)
  , category(cat)
  , price(prc)
  , date(dt)
  , paymentMethod(pay)
{ }

void Transaction::setData(const std::string& custID,
                          const std::string& prod,
                          const std::string& cat,
                          const std::string& prc,
                          const std::string& dt,
                          const std::string& pay)
{
    customerID    = custID;
    product       = prod;
    price         = prc;
    date          = dt;
    category      = cat;
    paymentMethod = pay;
}

std::string Transaction::getCustomerID()    const { return customerID;    }
std::string Transaction::getProduct()       const { return product;       }
std::string Transaction::getCategory()      const { return category;      }
std::string Transaction::getPrice()         const { return price;         }
std::string Transaction::getDate()          const { return date;          }
std::string Transaction::getPaymentMethod() const { return paymentMethod; }

// --- Review implementations ---
Review::Review()
  : productID(), customerID(), rating(), reviewText()
{ }

Review::Review(const std::string& prodID,
               const std::string& custID,
               const std::string& rt,
               const std::string& rev)
  : productID(prodID)
  , customerID(custID)
  , rating(rt)
  , reviewText(rev)
{ }

void Review::setData(const std::string& prodID,
                     const std::string& custID,
                     const std::string& rt,
                     const std::string& rev)
{
    productID  = prodID;
    customerID = custID;
    rating     = rt;
    reviewText = rev;
}

std::string Review::getProductID()  const { return productID; }
std::string Review::getCustomerID() const { return customerID; }
std::string Review::getRating()     const { return rating;     }
std::string Review::getReviewText() const { return reviewText; }

// --- CSVReader implementations ---
CSVReader::CSVReader()
  : transactions(new Transaction[MAX_ROWS])
  , reviews     (new Review     [MAX_ROWS])
  , transactionCount(0)
  , reviewCount     (0)
{ }

CSVReader::~CSVReader()
{
    delete[] transactions;
    delete[] reviews;
}

void CSVReader::readTransactions(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);  // skip header

    while (std::getline(file, line) && transactionCount < MAX_ROWS) {
        std::stringstream ss(line);
        std::string custID, prod, prc, dt, cat, pay;

        // Read in CSV order:
        std::getline(ss, custID, ',');  // CustomerID
        std::getline(ss, prod,   ',');  // Product
        std::getline(ss, cat,    ','); //Category
        std::getline(ss, prc,    ',');  // Price
        std::getline(ss, dt,     ',');  // Date
        std::getline(ss, pay,    ',');  // PaymentMethod

        // Store in the order Transaction expects:
        transactions[transactionCount++].setData(
            custID,  // customerID
            prod,    // product
            cat,     // category
            prc,     // price
            dt,      // date
            pay      // paymentMethod
        );
    }
    file.close();
}

void CSVReader::readReviews(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open reviews file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);  // skip header

    while (std::getline(file, line) && reviewCount < MAX_ROWS) {
        std::stringstream ss(line);
        std::string prodID, custID, rating, revText;

        std::getline(ss, prodID, ',');
        std::getline(ss, custID, ',');
        std::getline(ss, rating, ',');
        std::getline(ss, revText, ',');

        reviews[reviewCount++].setData(prodID, custID, rating, revText);
    }
    file.close();
}

Transaction* CSVReader::getTransactions()     const { return transactions;     }
int          CSVReader::getTransactionCount() const { return transactionCount; }
Review*      CSVReader::getReviews()          const { return reviews;          }
int          CSVReader::getReviewCount()      const { return reviewCount;      }
