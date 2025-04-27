#include "Class.hpp"
using namespace std;

Book::Book(const std::string &title, const std::string &author,
           const std::string &publisher, const std::string &ISBN,
           const std::string &year, int isAvailable,
           const std::string &borrower, const std::string &date)
    : title(title), author(author), publisher(publisher),
      ISBN(ISBN), year(year), isAvailable(isAvailable),
      borrower(borrower), latest_borrowed_date(date) {}
Book::~Book() {}
void Book::displayBook()
{
    cout << "----------------------------------------\n";
    cout << " Book Details\n";
    cout << "----------------------------------------\n";
    cout << " Title       : " << title << "\n";
    cout << " Author      : " << author << "\n";
    cout << " Publisher   : " << publisher << "\n";
    cout << " Year        : " << year << "\n";
    cout << " ISBN        : " << ISBN << "\n";
    cout << " Status      : ";

    if (isAvailable == 1)
    {
        cout << "Available\n";
    }
    else if (isAvailable == 0)
    {
        cout << "Not Available\n";
        cout << " Last Borrowed : " << latest_borrowed_date << "\n";
        cout << " Borrower      : " << borrower << "\n";
    }
    else // if (isAvailable == 2)
    {
        cout << "Reserved\n";
    }

    cout << "----------------------------------------\n";
}

string Book::getAuthor() const
{
    return author;
}
string Book::getTitle() const
{
    return title;
}
string Book::getPublisher() const
{
    return publisher;
}
string Book::getYear() const
{
    return year;
}
string Book::getISBN() const
{
    return ISBN;
}
int Book::getAvailability() const
{
    return isAvailable;
}
string Book::getBorrower() const
{
    return borrower;
}
string Book::getLatestDate() const
{
    return latest_borrowed_date;
}
void Book::changeLatestDate(const string &date)
{
    latest_borrowed_date = date;
}
void Book::changeAvailability(const int &availability)
{
    isAvailable = availability;
}
void Book::changeTitle(const string &newTitle)
{
    title = newTitle;
}
void Book::changeAuthor(const string &newAuthor)
{
    author = newAuthor;
}
void Book::changePublisher(const string &newPublisher)
{
    publisher = newPublisher;
}
void Book::changeYear(const string &newYear)
{
    year = newYear;
}
void Book::changeISBN(const string &newISBN)
{
    ISBN = newISBN;
}
void Book::changeBorrower(const string &username)
{
    borrower = username;
}