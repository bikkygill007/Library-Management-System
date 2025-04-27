#include "Class.hpp"



    User::User() : A() {}
    User::User(const std::string &usrname, const std::string &pswd, const int &id, const int &type)
        : userName(usrname), password(pswd), userID(id), usertype(type), A(){}
    int User::getUserType() const
    {
        return usertype;
    }
    int User::getUserID() const
    {
        return userID;
    }
    std::string User::getUserName() const
    {
        return userName;
    }
    std::string User::getPassword() const
    {
        return password;
    }
    void User::changeUserName(std::string newName, Library &L)
    {

        set<pair<std::string, std::string>> tmp;
        for (auto &book : L.books)
        {
            if (book.getBorrower() == userName)
            {
                book.changeBorrower(newName);
            }
        }
        userName = newName;
    }
    void User::changeUserID(int newID)
    {
        userID = newID;
    }
    void User::changePassword(std::string newPassword)
    {
        password = newPassword;
    }
    void User::changeUserType(int newType)
    {
        usertype = newType;
    }
    bool User::authenticate(const std::string &enteredPassword) const
    {
        return (password == enteredPassword);
    }



    Student::Student(const std::string &usrname, const std::string &pswd, const int &id)
        : User(usrname, pswd, id, 0){}

    Student::Student() : User() {}
    Student::~Student() {}
    int Student::getCurrentFine()
    {
        return A.fine;
    }
    void Student::borrowBook(const std::string &ISBN, Library &L)
    {
        A.fine = A.calculateFine(L.books);

        if (A.fine > 0)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " You have a pending fine of " << A.fine << " rupees.\n";
            std::cout << " Please clear your fine before borrowing new books. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        if (A.borrowedBooks.size() >= maxBooks)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " You have reached the maximum borrowing limit of " << maxBooks << " books.\n";
            std::cout << " Please return a book before borrowing another. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            
            std::cin.ignore();
            return;
        }

        Book *book = L.findBookByISBN(ISBN);
        if (book == nullptr)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No book with ISBN " << ISBN << " exists in the library. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        if (book->getAvailability() == 0)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book '" << book->getTitle() << "' is currently borrowed by another user. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        if (book->getAvailability() == 2)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book '" << book->getTitle() << "' is reserved. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        // Book is available, proceed with borrowing
        std::cout << "----------------------------------------\n";
        std::cout << " Borrowing Request Approved\n";
        std::cout << "----------------------------------------\n";
        std::cout << " Book: " << book->getTitle() << " (ISBN: " << book->getISBN() << ") is now issued to you.\n";

        A.borrowBookAccount(book->getISBN(), book->getTitle());
        book->changeAvailability(0);
        book->changeLatestDate(getCurrentDate());
        book->changeBorrower(userName);

        std::cout << " Book borrowed successfully!\n";
        std::cout << " Please return the book within the allowed period to avoid overdue fines. Press Enter to Continue.\n";
        std::cout << "----------------------------------------\n";
        std::cin.ignore();
    }

    
    void Student::returnBook(const std::string &ISBN, Library &L)
    {
        Book *book = L.findBookByISBN(ISBN);

        if (book == nullptr)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Return Request Failed\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No book found with ISBN: " << ISBN << ". Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        int overdueDays = daysBetweenDates(book->getLatestDate(), getCurrentDate());

        if (overdueDays > Student::maxDays)
        {
            int fineAmount = (overdueDays - Student::maxDays) * Student::fineRate;

            std::cout << "----------------------------------------\n";
            std::cout << " Overdue Book Return\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book '" << book->getTitle() << "' is overdue by " << (overdueDays - Student::maxDays) << " days.\n";
            std::cout << " A fine of " << fineAmount << " rupees must be paid before returning.\n";
            std::cout << " Would you like to pay the fine now? (Y/N): ";

            char choice;
            std::cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                this->A.fine -= fineAmount;
                std::cout << " Fine paid successfully for the book: " << book->getTitle() << "\n";
            }
            else
            {
                std::cout << " Fine not paid. The book cannot be returned until the fine is cleared.\n";
                std::cout << "----------------------------------------\n";
                std::cin.ignore();
                return;
            }
        }

        // Proceed with returning the book
        A.returnBookAccount(book->getISBN(), book->getTitle());
        A.addHistory(book->getISBN(), book->getTitle(), book->getLatestDate(), getCurrentDate());

        book->changeAvailability(1);
        book->changeBorrower("");
        book->changeLatestDate("");

        std::cout << "----------------------------------------\n";
        std::cout << " Book Returned Successfully\n";
        std::cout << "----------------------------------------\n";
        std::cout << " Book Title: " << book->getTitle() << "\n";
        std::cout << " ISBN      : " << ISBN << "\n";
        std::cout << " Press Enter to Continue.\n";
        std::cout << "----------------------------------------\n";
        std::cin.ignore();
    }



    Faculty::Faculty(const std::string &usrname, const std::string &pswd, const int &id)
        : User(usrname, pswd, id, 1)
    {
        // std::cout << "Faculty Account initialized for: " << usrname << endl;
    }
    Faculty::Faculty() : User() {}
    Faculty::~Faculty() {}
    
    void Faculty::borrowBook(const std::string &ISBN, Library &L)
    {
        // Check if faculty has exceeded the maximum borrowing period
        if (A.returnMaxDaysFaculty(L.books))
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " You have exceeded the maximum borrowing period of 60 days for a book.\n";
            std::cout << " Please return the overdue book before borrowing a new one. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        // Find the book in the library
        Book *book = L.findBookByISBN(ISBN);
        if (book == nullptr)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No book with ISBN " << ISBN << " exists in the library. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        // Check book availability status
        if (book->getAvailability() == 0)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book '" << book->getTitle() << "' (ISBN: " << ISBN << ") is currently borrowed. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }
        else if (book->getAvailability() == 2)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book '" << book->getTitle() << "' (ISBN: " << ISBN << ") is reserved. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        // Check if user has reached the borrowing limit
        if (A.borrowedBooks.size() >= maxBooks)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Borrowing Request Denied\n";
            std::cout << "----------------------------------------\n";
            std::cout << " You have reached the maximum limit of " << maxBooks << " books.\n";
            std::cout << " Please return a book before borrowing another. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        // Book is available, proceed with borrowing
        std::cout << "----------------------------------------\n";
        std::cout << " Borrowing Request Approved\n";
        std::cout << "----------------------------------------\n";
        std::cout << " Book Title : " << book->getTitle() << "\n";
        std::cout << " ISBN       : " << book->getISBN() << "\n";
        std::cout << "----------------------------------------\n";

        // Issue the book
        A.borrowBookAccount(book->getISBN(), book->getTitle());
        book->changeAvailability(0);
        book->changeLatestDate(getCurrentDate());
        book->changeBorrower(userName);

        std::cout << " The book has been successfully issued to you. Press Enter to Continue.\n";
        std::cout << "----------------------------------------\n";
        std::cin.ignore();
    }

    void Faculty::returnBook(const std::string &ISBN, Library &L)
    {
        // Find the book in the library
        Book *book = L.findBookByISBN(ISBN);
        if (book == nullptr)
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Return Request Failed\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No book found with ISBN: " << ISBN << "\n";
            std::cout << " Please check the ISBN and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }

        // Process the book return
        A.returnBookAccount(book->getISBN(), book->getTitle());
        A.addHistory(book->getISBN(), book->getTitle(), book->getLatestDate(), getCurrentDate());

        book->changeAvailability(1);
        book->changeBorrower("");
        book->changeLatestDate("");

        // Display confirmation message
        std::cout << "----------------------------------------\n";
        std::cout << " Book Returned Successfully.\n";
        std::cout << "----------------------------------------\n";
        std::cout << " Book Title : " << book->getTitle() << "\n";
        std::cout << " ISBN       : " << ISBN << "\n";
        std::cout << " Press Enter to Continue.\n";
        std::cout << "----------------------------------------\n";
        std::cin.ignore();
    }


    Librarian::Librarian(const std::string &usrname, const std::string &pswd, const int &id)
        : User(usrname, pswd, id, 2){}

    Librarian::Librarian() : User() {}
    Librarian::~Librarian() {}
    
    void Librarian::addNewUser(vector<User *> &users, const std::string &username, const int &newUserID)
    {
        auto it = find_if(users.begin(), users.end(),
                          [username](const User *u)
                          { return u->getUserName() == username; });

        if (it != users.end())
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Username Already Exists\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The chosen username is already in use. Please try a different one. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " User Adding Instructions\n";
            std::cout << "----------------------------------------\n";
            std::cout << " Please follow the instructions below to add the user details.\n";
            std::cout << "----------------------------------------\n";
            std::string password;
            int usertype;
            std::cout << " Enter the User Password                                             : ";
            getline(std::cin, password);
            std::cout << " Enter the User Type (0 for Student, 1 for Faculty, 2 for Librarian) : ";
            while (!(std::cin >> usertype))
            {
                std::cout << "----------------------------------------\n";
                std::cout << " Invalid Input \n";
                std::cout << "----------------------------------------\n";
                std::cout << " The user type entered is not an integer value. Please enter a valid integer (0, 1 or 2).\n";
                std::cout << "----------------------------------------\n";
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // int newUserID = users.empty() ? 1 : users.back()->getUserID() + 1; // Generate a new user ID
            User *newUser = nullptr;
            if (usertype == 0)
            {
                newUser = new Student(username, password, newUserID);
            }
            else if (usertype == 1)
            {
                newUser = new Faculty(username, password, newUserID);
            }
            else if (usertype == 2)
            {
                newUser = new Librarian(username, password, newUserID);
            }
            else
            {
                std::cout << "----------------------------------------\n";
                std::cout << " Invalid User Type\n";
                std::cout << "----------------------------------------\n";
                std::cout << " The user type entered is not recognized. Please enter a valid user type. Press Enter to Continue.\n";
                std::cout << "----------------------------------------\n";
                std::cin.ignore();
                return;
            }
            users.push_back(newUser);
            std::cout << "----------------------------------------\n";
            std::cout << " User Added Successfully\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The new user has been registered in the system. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
    }

    void Librarian::addNewBook(vector<Book> &books, const std::string &ISBN)
    {
        auto it = find_if(books.begin(), books.end(),
                          [ISBN](const Book &b)
                          { return b.getISBN() == ISBN; });

        if (it != books.end())
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Already Exists\n";
            std::cout << "----------------------------------------\n";
            std::cout << " A book with ISBN " << ISBN << " is already in the system.\n";
            std::cout << " Please check the details and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Adding Instructions\n";
            std::cout << "----------------------------------------\n";
            std::cout << " Please follow the instructions below to add the book details.\n";
            std::cout << "----------------------------------------\n";

            std::string title, author, publisher, year;
            std::cout << " Enter the Title       : ";
            getline(std::cin, title);

            std::cout << " Enter the Author      : ";
            getline(std::cin, author);

            std::cout << " Enter the Publisher   : ";
            getline(std::cin, publisher);

            std::cout << " Enter the Year        : ";
            getline(std::cin, year);

            Book newBook(title, author, publisher, ISBN, year, 1, "", "");
            books.push_back(newBook);
            std::cout << "----------------------------------------\n";
            std::cout << " Book Added Successfully\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book has been successfully added to the library system. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
    }
    void Librarian::removeUser(vector<User *> &users, const std::string &username)
    {
        auto it = find_if(users.begin(), users.end(),
                          [username](const User *u)
                          { return u->getUserName() == username; });

        if (it != users.end())
        {
            // logic to check if he has any borrowed books, if yes then the librarian cannot delete the user
            if ((*it)->A.borrowedBooks.size() > 0)
            {
                std::cout << "----------------------------------------\n";
                std::cout << " User Deletion Restricted\n";
                std::cout << "----------------------------------------\n";
                std::cout << " The user has borrowed books and cannot be deleted at this time.\n";
                std::cout << " Please ensure all borrowed books are returned before proceeding. Press Enter to Continue.\n";
                std::cout << "----------------------------------------\n";
                std::cin.ignore();
                return;
            }
            delete *it;
            users.erase(it);
            std::cout << "----------------------------------------\n";
            std::cout << " User Removed Successfully\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The user has been successfully deleted from the system.\n";
            std::cout << "----------------------------------------\n";
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " User Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No matching user was found in the system.\n";
            std::cout << " Please check the details and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
    }
    void Librarian::removeBook(vector<Book> &books, const std::string &ISBN)
    {
        auto it = find_if(books.begin(), books.end(),
                          [ISBN](const Book &b)
                          { return b.getISBN() == ISBN; });

        if (it != books.end())
        {
            // logic to check if the user has borrowed the book, if yes then the librarian cannot delete the book
            if (it->getAvailability() == 0)
            {
                std::cout << "----------------------------------------\n";
                std::cout << " Book Deletion Restricted\n";
                std::cout << "----------------------------------------\n";
                std::cout << " The book is currently borrowed by a user and cannot be deleted.\n";
                std::cout << " Please ensure the book is returned before proceeding. Press Enter to Continue\n";
                std::cout << "----------------------------------------\n";
                std::cin.ignore();
                return;
            }
            books.erase(it);
            std::cout << "----------------------------------------\n";
            std::cout << " Book Removed Successfully\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book has been successfully deleted from the library system. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No matching book was found in the system.\n";
            std::cout << " Please check the details and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
    }
    void Librarian::updateBook(vector<Book> &books, const std::string &ISBN)
    {

        auto it = find_if(books.begin(), books.end(),
                          [ISBN](const Book &b)
                          { return b.getISBN() == ISBN; });
        // a function which checks if the book is borrowed by someone and if it is then it should not be updated

        if (it != books.end())
        {
            if (it->getAvailability() == 0)
            {
                std::cout << "----------------------------------------\n";
                std::cout << " Book Updation Restricted\n";
                std::cout << "----------------------------------------\n";
                std::cout << " The book is currently borrowed by a user and cannot be updated.\n";
                std::cout << " Please ensure the book is returned before proceeding. Press Enter to Continue.\n";
                std::cout << "----------------------------------------\n";
                std::cin.ignore();
                return;
            }
            std::cout << "----------------------------------------\n";
            std::cout << " Book Update Instructions\n";
            std::cout << "----------------------------------------\n";
            std::cout << " Please follow the instructions below to update the book details.\n";
            std::cout << "----------------------------------------\n";

            std::string newTitle, newAuthor, newPublisher, newYear;
            int newStatus;

            std::cout << " Enter the new Title       : ";
            getline(std::cin, newTitle);

            std::cout << " Enter the new Author      : ";
            getline(std::cin, newAuthor);

            std::cout << " Enter the new Publisher   : ";
            getline(std::cin, newPublisher);

            std::cout << " Enter the new Year        : ";
            getline(std::cin, newYear);

            std::cout << " Enter the new Status      :\n";
            std::cout << "   0 - Not Available\n";
            std::cout << "   1 - Available\n";
            std::cout << "   2 - Reserved\n";
            std::cout << " Choice: ";

            while (!(std::cin >> newStatus))
            {
                std::cout << "----------------------------------------\n";
                std::cout << " Invalid Input\n";
                std::cout << "----------------------------------------\n";
                std::cout << " Please enter a valid integer for the book status.\n";
                std::cout << "   0 - Not Available\n";
                std::cout << "   1 - Available\n";
                std::cout << "   2 - Reserved\n";
                std::cout << "----------------------------------------\n";
                std::cout << " Choice: ";

                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            it->changeTitle(newTitle);
            it->changeAuthor(newAuthor);
            it->changePublisher(newPublisher);
            it->changeYear(newYear);
            it->changeAvailability(newStatus);
            std::cout << "----------------------------------------\n";
            std::cout << " Book Updates Successfully\n";
            std::cout << "----------------------------------------\n";
            std::cout << " The book has been successfully updated in the library system. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No matching book was found in the system.\n";
            std::cout << " Please check the details and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
            return;
        }
    }

    void Librarian::searchUser(vector<User *> &users, const std::string &username)
    {
        auto it = find_if(users.begin(), users.end(),
                          [username](const User *u)
                          { return u->getUserName() == username; });

        if (it != users.end())
        {
            std::cout << "----------------------------------------\n";
            std::cout << " User Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " Username  : " << (*it)->getUserName() << "\n";
            std::cout << " User ID   : " << (*it)->getUserID() << "\n";
            std::cout << " User Type : " << (*it)->getUserType() << "\n";
            std::cout << "----------------------------------------\n";

            // logic to see the currently borrowed books:
            (*it)->A.displayCurrentBooks();
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " User Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No matching user was found in the system.\n";
            std::cout << " Please check the details and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
    }
    void Librarian::searchBook(vector<Book> &books, const std::string &title)
    {
        auto it = find_if(books.begin(), books.end(),
                          [title](const Book &b)
                          { return b.getTitle() == title; });

        if (it != books.end())
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " Title            : " << it->getTitle() << "\n";
            std::cout << " Author           : " << it->getAuthor() << "\n";
            std::cout << " Publisher        : " << it->getPublisher() << "\n";
            std::cout << " Year             : " << it->getYear() << "\n";
            std::cout << " ISBN             : " << it->getISBN() << "\n";
            std::cout << " Availability     : " << ((it->getAvailability()==2)?"Reserved" : (it->getAvailability()==1)? "Available" : "Not Available") << "\n";
            if((it->getAvailability()==0))
            std::cout<<  " Current Borrower : " << ((it->getBorrower()))<< "\n";
            std::cout << "----------------------------------------\n";
        }
        else
        {
            std::cout << "----------------------------------------\n";
            std::cout << " Book Not Found\n";
            std::cout << "----------------------------------------\n";
            std::cout << " No matching book was found in the system.\n";
            std::cout << " Please check the details and try again. Press Enter to Continue.\n";
            std::cout << "----------------------------------------\n";
            std::cin.ignore();
        }
    }
    void Librarian::borrowBook(const std::string &ISBN, Library &L) { return; }
    void Librarian::returnBook(const std::string &ISBN, Library &L) { return; }
