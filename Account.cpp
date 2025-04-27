#include "Class.hpp"
using namespace std;

    Account::Account() : fine(0) {}
    Account::~Account() {}
    void Account::borrowBookAccount(string ISBN, string title)
    {
        borrowedBooks.insert({ISBN, title});
    }
    void Account::returnBookAccount(string ISBN, string title)
    {
        borrowedBooks.erase({ISBN, title});
    }
    void Account::addHistory(string ISBN, string title, string start, string end)
    {
        history.push_back({{ISBN, title}, {start, end}});
    }

    void Account::displayCurrentBooks()
    {
        cout << "========================================\n";
        cout << "          Currently Borrowed Books      \n";
        cout << "========================================\n";

        if (borrowedBooks.empty())
        {
            cout << " No books are currently borrowed.\n";
        }
        else
        {
            for (const auto &book : borrowedBooks)
            {
                cout << " ISBN   : " << book.first << "\n";
                cout << " Title  : " << book.second << "\n";
                cout << "----------------------------------------\n";
            }
        }
        
        cout << endl;
    }

    void Account::displayHistory()
    {
        cout << "========================================\n";
        cout << "         Borrowed Books History         \n";
        cout << "========================================\n";

        if (history.empty())
        {
            cout << " No borrowing history available.\n";
            cout << "----------------------------------------\n";
            cin.ignore();
        }
        else
        {
            for (const auto &entry : history)
            {
                cout << " ISBN           : " << entry.first.first << "\n";
                cout << " Title          : " << entry.first.second << "\n";
                cout << " Borrowed From  : " << entry.second.first << "\n";
                cout << " Returned On    : " << entry.second.second << "\n";
                cout << "----------------------------------------\n";
            }
        }

        cout << endl;
    }

    int Account::calculateFine(vector<Book> &allBooks)
    {
        fine = 0;

        string today = getCurrentDate();

        for (auto &borrowed : borrowedBooks)
        {
            string isbn = borrowed.first;
            for (auto &book : allBooks)
            {
                if (book.getISBN() == isbn)
                {
                    string lastDate = book.getLatestDate();
                    // cout<<lastDate<<endl;
                    int overdueDays = daysBetweenDates(lastDate, today);
                    // cout<<overdueDays<<endl;
                    if (overdueDays > 15)
                    {
                        fine += (overdueDays - 15) * 10; // 10 rupees per day fine
                    }
                    break;
                }
            }
        }
        return fine;
    }
    int Account::getFine() const
    {
        return fine;
    }
    void Account::payFine(int amount)
    {
        fine -= amount;
        if (fine < 0)
        {
            fine = 0;
        }
        cout << "----------------------------------------\n";
        cout << " Payment Successful\n";
        cout << "----------------------------------------\n";
        cout << " Fine Amount Paid: " << amount << " rupees\n";
        cout << " Your outstanding balance is now cleared.\n";
        cout << "----------------------------------------\n";
        cin.ignore();
    }
    bool Account::returnMaxDaysFaculty(vector<Book> &allBooks)
    {
        int maxBorrowPeriod = 60;
        for (auto &borrowed : borrowedBooks)
        {
            string isbn = borrowed.first;
            for (auto &book : allBooks)
            {
                if (book.getISBN() == isbn)
                {
                    int days = daysBetweenDates(book.getLatestDate(), getCurrentDate());
                    if (days > maxBorrowPeriod)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
