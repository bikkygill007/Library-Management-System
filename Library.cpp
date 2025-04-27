#include "Class.hpp"
Book *Library::findBookByISBN(const string &ISBN)
{
    for (auto &book : books)
    {
        if (book.getISBN() == ISBN)
        {
            return &book;
        }
    }
    return nullptr; // Book not found
}


vector<Book> Library::loadBookData(const string &filename)
{
    vector<Book> books;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string title, author, publisher, ISBN, year, borrower, date;
        int isAvailable;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, ISBN, ',');
        getline(ss, year, ',');
        ss >> isAvailable;
        ss.ignore(); // Skip comma
        getline(ss, borrower, ',');
        getline(ss, date, ',');

        books.push_back(Book(title, author, publisher, ISBN, year, isAvailable, borrower, date));
    }

    file.close();
    return books;
}

// Save book data to file
void Library::saveBookData(const vector<Book> &books)
{
    ofstream file("books.txt", ios::trunc);
    for (const auto &book : books)
    {
        file << book.getTitle() << "," << book.getAuthor() << "," << book.getPublisher() << ","
             << book.getISBN() << "," << book.getYear() << "," << book.getAvailability() << ","
             << book.getBorrower() << "," << book.getLatestDate() << "\n";
    }
    file.close();
}

vector<User *> Library::loadUserData(const string &filename)
{
    vector<User *> users;
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error: Could not open file " << filename << endl;
        return users;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string userName, password;
        int usertype, userID, fine, numBooks = 0, numHistory = 0;

        // Read basic user details
        if (!getline(ss, userName, ',') ||
            !getline(ss, password, ',') ||
            !(ss >> usertype) || ss.get() != ',' ||
            !(ss >> userID) || ss.get() != ',' ||
            !(ss >> fine) || ss.get() != ',')
        {
            cout << "Error: Malformed data in line - " << line << endl;
            continue;
        }

        // Create appropriate user object
        User *user = nullptr;
        if (usertype == 0)
            user = new Student(userName, password, userID);
        else if (usertype == 1)
            user = new Faculty(userName, password, userID);
        else if (usertype == 2)
            user = new Librarian(userName, password, userID);
        else
        {
            cout << "Error: Invalid user type in line - " << line << endl;
            continue;
        }

        user->A.fine = fine; // Assign fine

        // Read borrowed books
        if (ss >> numBooks && ss.get() == ',')
        {
            for (int i = 0; i < numBooks; ++i)
            {
                string isbn, title;
                if (!getline(ss, isbn, ',') || !getline(ss, title, ','))
                {
                    cout << "Error: Malformed book data in line - " << line << endl;
                    delete user;
                    continue;
                }
                user->A.borrowedBooks.insert({isbn, title});
            }
        }

        // Read history
        if (ss >> numHistory && ss.get() == ',')
        {
            for (int i = 0; i < numHistory; ++i)
            {
                string isbn, title, start, end;
                if (!getline(ss, isbn, ',') || !getline(ss, title, ',') ||
                    !getline(ss, start, ',') || !getline(ss, end, ','))
                {
                    cout << "Error: Malformed history data in line - " << line << endl;
                    delete user;
                    continue;
                }
                user->A.addHistory(isbn, title, start, end);
            }
        }

        users.push_back(user);
    }

    file.close();
    return users;
}

void Library::saveUserData(const vector<User *> &users)
{
    ofstream file("users.txt", ios::trunc);
    if (!file)
    {
        cerr << "Error: Could not open file for writing\n";
        return;
    }
    for (const auto *user : users)
    {
        file << user->getUserName() << "," << user->getPassword() << ","
             << user->getUserType() << "," << user->getUserID() << "," << user->A.fine << ",";
        // cout<<user;
        // Save borrowed books
        file << user->A.borrowedBooks.size() << ",";
        for (const auto &book : user->A.borrowedBooks)
        {
            file << book.first << "," << book.second << ",";
        }

        // Save history
        file << user->A.history.size() << ",";
        for (const auto &entry : user->A.history)
        {
            file << entry.first.first << "," << entry.first.second << ","
                 << entry.second.first << "," << entry.second.second << ",";
        }

        file << "\n";
    }
    file.close();
}
