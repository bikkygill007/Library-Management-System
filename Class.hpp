#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "utils.cpp"
using namespace std;

class Book
{
private:
    std::string title;
    std::string author;
    std::string publisher;
    std::string ISBN;
    std::string year;
    int isAvailable;
    std::string borrower;
    std::string latest_borrowed_date;

public:
    // Public constructor to initialize Car object
    Book(const std::string &title, const std::string &author,
         const std::string &publisher, const std::string &ISBN,
         const std::string &year, int isAvailable,
         const std::string &borrower, const std::string &date);
    ~Book();
    void displayBook();
    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getPublisher() const;
    std::string getYear() const;
    std::string getISBN() const;
    int getAvailability() const;
    std::string getBorrower() const;
    std::string getLatestDate() const;
    void changeLatestDate(const std::string &date);
    void changeAvailability(const int &availability);
    void changeTitle(const std::string &newTitle);
    void changeAuthor(const std::string &newAuthor);
    void changePublisher(const std::string &newPublisher);
    void changeYear(const std::string &newYear);
    void changeISBN(const std::string &newISBN);
    void changeBorrower(const std::string &username);
    
};
class Account
{
public:
    int fine;
    set<pair<std::string, std::string>> borrowedBooks;                          // set of pairs to store the currently borrowed books
    vector<pair<pair<std::string, std::string>, pair<std::string, std::string>>> history; // a vector of one pair and one std::string to store the history, pair for the book and std::string for the date;

    Account();
    ~Account();
    void borrowBookAccount(std::string ISBN, std::string title);
    void returnBookAccount(std::string ISBN, std::string title);
    void addHistory(std::string ISBN, std::string title, std::string start, std::string end);

    void displayCurrentBooks();

    void displayHistory();

    int calculateFine(vector<Book> &allBooks);
    int getFine() const;
    void payFine(int amount);
    bool returnMaxDaysFaculty(vector<Book> &allBooks);
};
class User;
class Library
{
public:
    vector<Book> books;
    vector<User *> users;
    Book *findBookByISBN(const std::string &ISBN);
    static vector<User *> loadUserData(const string &filename);
    static void saveUserData(const vector<User *> &users);
    static vector<Book> loadBookData(const std::string &filename);
    static void saveBookData(const vector<Book> &books);
};
class User
{
protected:
    std::string userName;

    std::string password;
    int usertype; // 0 for student, 1 for faculty, 2 for librarian
    int userID;

public:
    Account A;
    User();
    User(const std::string &usrname, const std::string &pswd, const int &id, const int &type);
    virtual ~User() {}

    virtual void borrowBook(const std::string &ISBN, Library &L) = 0;
    virtual void returnBook(const std::string &ISBN, Library &L) = 0;
    int getUserType() const;
    int getUserID() const;
    std::string getUserName() const;
    std::string getPassword() const;
    void changeUserName(std::string newName, Library &L);
    void changeUserID(int newID);
    void changePassword(std::string newPassword);
    void changeUserType(int newType);
    bool authenticate(const std::string &enteredPassword) const;
};

class Student : public User
{

public:
    static const int maxBooks = 3;
    static const int maxDays = 15;
    static const int fineRate = 10;
    Student(const std::string &usrname, const std::string &pswd, const int &id);
    Student();
    ~Student();
    int getCurrentFine();
    void borrowBook(const std::string &ISBN, Library &L);
    void returnBook(const std::string &ISBN, Library &L);
};

class Faculty : public User
{
private:
    const int maxBooks = 5;
    const int maxDays = 30;

public:
    Faculty(const std::string &usrname, const std::string &pswd, const int &id);
    Faculty();
    ~Faculty();

    void borrowBook(const std::string &ISBN, Library &L);

    void returnBook(const std::string &ISBN, Library &L);
};
class Librarian : public User
{
public:
    Librarian(const std::string &usrname, const std::string &pswd, const int &id);

    Librarian();
    ~Librarian();
    static void addNewUser(vector<User *> &users, const std::string &username, const int &newUserID);

    static void addNewBook(vector<Book> &books, const std::string &ISBN);
    static void removeUser(vector<User *> &users, const std::string &username);
    static void removeBook(vector<Book> &books, const std::string &ISBN);
    static void updateBook(vector<Book> &books, const std::string &ISBN);
    static void searchUser(vector<User *> &users, const std::string &username);
    static void searchBook(vector<Book> &books, const string &title);
    void borrowBook(const std::string &ISBN, Library &L);
    void returnBook(const std::string &ISBN, Library &L);
};
