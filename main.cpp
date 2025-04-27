#include "Class.hpp"
#include "Account.cpp"
#include "Users.cpp"
#include "Books.cpp"
#include "Library.cpp"

int main()
{

    Library L;
    L.users = L.loadUserData("users.txt");
    L.books = L.loadBookData("books.txt");

    int id = L.users.back()->getUserID() + 1;

    while (1)
    {
    registered:
        cout << "----------------------------------------\n";
        cout << " User Type Selection\n";
        cout << "----------------------------------------\n";
        cout << " Enter the corresponding number for the user type:\n";
        cout << "   0 - Student\n";
        cout << "   1 - Faculty\n";
        cout << "   2 - Librarian\n";
        cout << "   Any other number - Exit\n";
        cout << "----------------------------------------\n";
        cout << " Choice: ";

        int verification;
        if (!(cin >> verification))
        {
            cout << "----------------------------------------\n";
            cout << " Invalid Input\n";
            cout << "----------------------------------------\n";
            cout << " Please enter a valid integer for the user type.\n";
            cout << "   0 - Student\n";
            cout << "   1 - Faculty\n";
            cout << "   2 - Librarian\n";
            cout << "   Any other number - Exit\n";
            cout << "----------------------------------------\n";
            cout << " Choice: ";

            // Clear the error state and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Restart the loop
        }
        string username;
        if (verification != 0 && verification != 1 && verification != 2)
        {
            cout << "----------------------------------------\n";
            cout << " Goodbye Sohneo!!\n";
            cout << "----------------------------------------\n";
            cout << " Thank you for using the Library Management System.\n";
            cout << " Have a great day ahead!\n";
            cout << "----------------------------------------\n";

            break;
            // return 0;
        }

        else if (verification == 0)
        {

            cout << "----------------------------------------\n";
            cout << " Registration Check\n";
            cout << "----------------------------------------\n";
            cout << " Are you already registered?\n";
            cout << " Type 'YES' if you are registered, or 'NO' to proceed with new registration.\n";
            cout << "----------------------------------------\n";
            cout << " Response: ";

            string answer;
            while (true)
            {

                cin >> answer;
                transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                if (answer == "YES" || answer == "NO")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "----------------------------------------\n";
                    cout << " Invalid Input\n";
                    cout << "----------------------------------------\n";
                    cout << " Please enter a valid response.\n";
                    cout << " Type 'YES' if you are registered, or 'NO' to proceed with new registration.\n";
                    cout << "----------------------------------------\n";
                    cout << " Response: ";

                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (answer == "YES")
            {
            login_0:

                cout << "----------------------------------------\n";
                cout << " Enter Username\n";
                cout << "----------------------------------------\n";
                cout << " Username: ";

                cin >> username;

                auto it = find_if(L.users.begin(), L.users.end(),
                                  [username](const User *u)
                                  { return u->getUserName() == username; });

                if (it != L.users.end())
                {
                    cout << "----------------------------------------\n";
                    cout << " Enter Password\n";
                    cout << "----------------------------------------\n";
                    cout << " Password: ";
                    string password;
                    cin >> password;

                    if ((*it)->authenticate(password))
                    {
                        cout << "----------------------------------------\n";
                        cout << " Login Successful\n";
                        cout << "----------------------------------------\n";
                        cout << " Welcome, " << (*it)->getUserName() << "!\n";
                        cout << " You have successfully logged into the system.\n";
                        cout << "----------------------------------------\n";

                        // User *loggedInUser = new Student((*it)->getUserName(), (*it)->getPassword(), (*it)->getUserID());
                        // loggedInUser->A = (*it)->A;
                        User *loggedInUser = *it;
                        // cout<<loggedInUser<<"\n";
                        loggedInUser->A.fine = loggedInUser->A.calculateFine(L.books);
                        cout << "========================================\n";
                        cout << "           User Menu Options            \n";
                        cout << "========================================\n";
                        cout << "  1. Search for a Book\n";
                        cout << "  2. Borrow a Book\n";
                        cout << "  3. Return a Book\n";
                        cout << "  4. Pay Fine\n";
                        cout << "  5. View Your Details\n";
                        cout << "  6. Change Your Details\n";
                        cout << "  7. Logout\n";
                        cout << "========================================\n";
                        cout << " Please enter your choice: ";

                        int choice = -1;
                        while (!(choice == 7))
                        {
                            // still can add the functionality to change personal attributes like username, password;
                            if (!(cin >> choice))
                            {
                                cout << "----------------------------------------\n";
                                cout << " Invalid Input\n";
                                cout << "----------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Please enter a valid input only from the following choices: \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";

                                continue;
                            }
                            if (choice == 1)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Search for a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the title of the book you want to search for: ";

                                string title;
                                cin.ignore();
                                getline(cin, title);
                                Librarian::searchBook(L.books, title);
                                cout << " What do you want to do next?\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 2)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Borrow a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the book you want to borrow: ";

                                string isbn;
                                cin >> isbn;
                                loggedInUser->borrowBook(isbn, L);
                                cout << " What do you want to do next?\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 3)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Return a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the book you want to return: ";

                                string isbn;
                                cin >> isbn;
                                loggedInUser->returnBook(isbn, L);
                                cout << " What do you want to do next?\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 4)
                            {
                                // L.payFine(username);
                                if ((loggedInUser->A.fine) == 0)
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " No Pending Fine\n";
                                    cout << "----------------------------------------\n";
                                    cout << " You do not have any outstanding fines at this time.\n";
                                    cout << "----------------------------------------\n";
                                }
                                else
                                {
                                    string isbn;
                                    cout << "----------------------------------------\n";
                                    cout << " Pay a Fine\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Enter the ISBN of the book for which you want to pay the fine: ";
                                    cin >> isbn;
                                    auto it_1 = find_if(L.books.begin(), L.books.end(),
                                                        [isbn](const Book &b)
                                                        { return b.getISBN() == isbn; });
                                    if (it_1 != L.books.end())
                                    {
                                        auto it = find_if(loggedInUser->A.borrowedBooks.begin(), loggedInUser->A.borrowedBooks.end(),
                                                          [isbn](const pair<string, string> &p)
                                                          { return p.first == isbn; });
                                        if (it != loggedInUser->A.borrowedBooks.end())
                                        {
                                            int overdueDays = daysBetweenDates(it_1->getLatestDate(), getCurrentDate());
                                            int amt = (overdueDays > 15 ? overdueDays - 15 : 0) * 10;
                                            if (amt == 0)
                                            {
                                                cout << "----------------------------------------\n";
                                                cout << " No Pending Fine fo this book\n";
                                                cout << "----------------------------------------\n";
                                                cout << " You do not have any outstanding fines for this book at this time.\n";
                                                cout << "----------------------------------------\n";
                                            }
                                            else
                                            {
                                                cout << "----------------------------------------\n";
                                                cout << " Pending Fine\n";
                                                cout << "----------------------------------------\n";
                                                cout << " You have a fine of " << amt << " rupees associated with this book.\n";
                                                cout << " Do you want to pay the fine now? (payment in installments NOT ALLOWED) (YES/NO): ";

                                                string choice;
                                                cin >> choice;
                                                transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
                                                if (choice == "YES")
                                                {
                                                
                                                    
                                                    loggedInUser->A.payFine(amt);
                                                    it_1->changeLatestDate(getCurrentDate());
                                                    cout << "----------------------------------------\n";
                                                    cout << " Fine Payment Successful\n";
                                                    cout << "----------------------------------------\n";
                                                    cout << " The fine has been paid successfully.\n";
                                                    cout << " The book's latest borrowed date has been updated to the current date.\n";
                                                    cout << "----------------------------------------\n";
                                                }
                                                else
                                                {
                                                    cout << "----------------------------------------\n";
                                                    cout << " Fine Payment Declined\n";
                                                    cout << "----------------------------------------\n";
                                                    cout << " The fine has not been paid.\n";
                                                    cout << " You must clear the fine to proceed with related actions.\n";
                                                    cout << "----------------------------------------\n";
                                                }
                                            }
                                        }
                                        else
                                        {
                                            cout << "----------------------------------------\n";
                                            cout << " Fine Payment Not Allowed\n";
                                            cout << "----------------------------------------\n";
                                            cout << " The specified book does not exist in your borrowed books.\n";
                                            cout << " You can only pay fines for books you have borrowed.\n";
                                            cout << "----------------------------------------\n";
                                        }
                                    }
                                    else
                                    {
                                        cout << "----------------------------------------\n";
                                        cout << " Fine Payment Not Allowed\n";
                                        cout << "----------------------------------------\n";
                                        cout << " The specified book does not exist in the library system.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                    // loggedInUser->A.payFine(amount);
                                }
                                cout << " What do you want to do next?\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 5)
                            {
                                cout << "========================================\n";
                                cout << "           User Details                 \n";
                                cout << "========================================\n";
                                cout << " Username  : " << loggedInUser->getUserName() << "\n";
                                cout << " User ID   : " << loggedInUser->getUserID() << "\n";
                                cout << " Fine Due  : " << loggedInUser->A.getFine() << " rupees\n";
                                cout << "========================================\n";

                                // cout << "Currently Borrowed Books: \n";
                                loggedInUser->A.displayCurrentBooks();
                                // cout << "Borrowed Books History: \n";
                                loggedInUser->A.displayHistory();
                                cout << " What do you want to do next?\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 6)
                            {
                                cout << "========================================\n";
                                cout << "         Update User Details            \n";
                                cout << "========================================\n";
                                cout << " What would you like to change?\n";
                                cout << "   1. Username\n";
                                cout << "   2. Password\n";
                                cout << "========================================\n";
                                cout << " Enter your choice: ";

                                int choice;
                                cin >> choice;
                                if (choice == 1)
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " Enter Username\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Username: ";
                                    string newUsername;
                                    cin >> newUsername;
                                    auto it = find_if(L.users.begin(), L.users.end(),
                                                      [newUsername](const User *u)
                                                      { return u->getUserName() == newUsername; });
                                    if (it != L.users.end())
                                    {
                                        cout << "----------------------------------------\n";
                                        cout << " Matching Username Found\n";
                                        cout << "----------------------------------------\n";
                                        cout << " A matching username was found in the system.\n";
                                        cout << " Please re-enter a new username and try again.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                    else
                                    {
                                        loggedInUser->changeUserName(newUsername, L);
                                        cout << "----------------------------------------\n";
                                        cout << " Username Updated Successful\n";
                                        cout << "----------------------------------------\n";
                                        cout << " Your Username has been Successfully Updated in the System.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                    cout << " What do you want to do next?\n";
                                    cout << "========================================\n";
                                    cout << "           User Menu Options            \n";
                                    cout << "========================================\n";
                                    cout << "  1. Search for a Book\n";
                                    cout << "  2. Borrow a Book\n";
                                    cout << "  3. Return a Book\n";
                                    cout << "  4. Pay Fine\n";
                                    cout << "  5. View Your Details\n";
                                    cout << "  6. Change Your Details\n";
                                    cout << "  7. Logout\n";
                                    cout << "========================================\n";
                                    cout << " Please enter your choice: ";
                                }
                                else
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " Enter Password\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Password: ";
                                    string newPassword;
                                    cin >> newPassword;
                                    loggedInUser->changePassword(newPassword);
                                    cout << "----------------------------------------\n";
                                    cout << " Password Updated Successful\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Your Password has been Successfully Updated in the System.\n";
                                    cout << "----------------------------------------\n";

                                    cout << " What do you want to do next?\n";
                                    cout << "========================================\n";
                                    cout << "           User Menu Options            \n";
                                    cout << "========================================\n";
                                    cout << "  1. Search for a Book\n";
                                    cout << "  2. Borrow a Book\n";
                                    cout << "  3. Return a Book\n";
                                    cout << "  4. Pay Fine\n";
                                    cout << "  5. View Your Details\n";
                                    cout << "  6. Change Your Details\n";
                                    cout << "  7. Logout\n";
                                    cout << "========================================\n";
                                    cout << " Please enter your choice: ";
                                }
                            }
                            else if (choice == 7)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Logout Successful\n";
                                cout << "----------------------------------------\n";
                                cout << " GoodBye, " << (*it)->getUserName() << "!\n";
                                cout << " You have successfully logged out of the system.\n";
                                cout << "----------------------------------------\n";
                            }
                            else
                            {
                                cout << "----------------------------------------\n";
                                cout << " Invalid Input\n";
                                cout << "----------------------------------------\n";
                                cout << " Please enter a valid integer for choosing the correct User Function\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. Pay Fine\n";
                                cout << "  5. View Your Details\n";
                                cout << "  6. Change Your Details\n";
                                cout << "  7. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                        }
                    }
                    else
                    {
                        cout << "----------------------------------------\n";
                        cout << " Invalid Password\n";
                        cout << "----------------------------------------\n";
                        cout << " The password does not match with your saved password, Please Try Again!!\n";
                        cout << "----------------------------------------\n";
                    }
                }
                else
                {
                    cout << "----------------------------------------\n";
                    cout << " Username Not Found\n";
                    cout << "----------------------------------------\n";
                    cout << " No matching username was found in the system.\n";
                    cout << " Please check the details and try again.\n";
                    cout << "----------------------------------------\n";
                }
            }
            else
            {
                cout << "=========================================\n";
                cout << " Would you like to register? \n";
                cout << " Type YES to register or NO to go back to the login page\n";
                cout << "=========================================\n";
                string answer;
                while (true)
                {

                    cin >> answer;
                    transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                    if (answer == "YES" || answer == "NO")
                    {
                        // Valid input, exit the loop
                        break;
                    }
                    else
                    {
                        cout << "----------------------------------------\n";
                        cout << " Invalid Input\n";
                        cout << "----------------------------------------\n";
                        cout << " Please type YES or NO ONLY!!\n";
                        cout << "----------------------------------------\n";
                        // Clear the input buffer to prevent infinite loop
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                if (answer == "YES")
                {
                    cout << "----------------------------------------\n";
                    cout << " Enter Username\n";
                    cout << "----------------------------------------\n";
                    cout << " Username: ";
                    string usernme;
                    while (true)
                    {
                        cin >> username;
                        auto it = find_if(L.users.begin(), L.users.end(),
                                          [username](const User *u)
                                          { return u->getUserName() == username; });
                        if (it != L.users.end())
                        {
                            cout << "----------------------------------------\n";
                            cout << " Matching Username Found\n";
                            cout << "----------------------------------------\n";
                            cout << " A matching username was found in the system.\n";
                            cout << " Please re-enter a new username and try again.\n";
                            cout << "----------------------------------------\n";
                            continue;
                        }
                        else
                        {
                            cout << "----------------------------------------\n";
                            cout << " Enter Password\n";
                            cout << "----------------------------------------\n";
                            cout << " Password: ";
                            string password;
                            cin >> password;
                            User *newUser = new Student(username, password, id);
                            L.users.push_back(newUser);
                            id++;
                            cout << "----------------------------------------\n";
                            cout << " User Added Successfully\n";
                            cout << "----------------------------------------\n";
                            cout << " The new user has been registered in the system.\n";
                            cout << "----------------------------------------\n";
                            cout << " Please Login Again to use the Library Management System \n";
                            cout << "----------------------------------------\n";
                            goto login_0;
                        }
                    }
                }
                else
                {
                    goto registered;
                }
            }
        }
        else if (verification == 1)
        {

            cout << "----------------------------------------\n";
            cout << " Registration Check\n";
            cout << "----------------------------------------\n";
            cout << " Are you already registered?\n";
            cout << " Type 'YES' if you are registered, or 'NO' to proceed with new registration.\n";
            cout << "----------------------------------------\n";
            cout << " Response: ";
            string answer;
            while (true)
            {

                cin >> answer;
                transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                if (answer == "YES" || answer == "NO")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "----------------------------------------\n";
                    cout << " Invalid Input\n";
                    cout << "----------------------------------------\n";
                    cout << " Please enter a valid response.\n";
                    cout << " Type 'YES' if you are registered, or 'NO' to proceed with new registration.\n";
                    cout << "----------------------------------------\n";
                    cout << " Response: ";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (answer == "YES")
            {
            login_1:

                cout << "----------------------------------------\n";
                cout << " Enter Username\n";
                cout << "----------------------------------------\n";
                cout << " Username: ";

                cin >> username;

                auto it = find_if(L.users.begin(), L.users.end(),
                                  [username](const User *u)
                                  { return u->getUserName() == username; });

                if (it != L.users.end())
                {
                    cout << "----------------------------------------\n";
                    cout << " Enter Password\n";
                    cout << "----------------------------------------\n";
                    cout << " Password: ";
                    string password;
                    cin >> password;

                    if ((*it)->authenticate(password))
                    {
                        cout << "----------------------------------------\n";
                        cout << " Login Successful\n";
                        cout << "----------------------------------------\n";
                        cout << " Welcome, " << (*it)->getUserName() << "!\n";
                        cout << " You have successfully logged into the system.\n";
                        cout << "----------------------------------------\n";

                        User *loggedInUser = *it;
                        cout << "========================================\n";
                        cout << "           User Menu Options            \n";
                        cout << "========================================\n";
                        cout << "  1. Search for a Book\n";
                        cout << "  2. Borrow a Book\n";
                        cout << "  3. Return a Book\n";
                        cout << "  4. View your details\n";
                        cout << "  5. Change Your Details\n";
                        cout << "  6. Logout\n";
                        cout << "========================================\n";
                        cout << " Please enter your choice: ";
                        int choice = -1;
                        while (!(choice == 6))
                        {
                            // still can add the functionality to change personal attributes like username, password;
                            if (!(cin >> choice))
                            {
                                cout << "----------------------------------------\n";
                                cout << " Invalid Input\n";
                                cout << "----------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Please enter a valid input only from the following choices: \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                                continue;
                            }
                            if (choice == 1)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Search for a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the title of the book you want to search for: ";
                                string title;
                                cin.ignore();
                                getline(cin, title);
                                Librarian::searchBook(L.books, title);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 2)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Borrow a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the book you want to borrow: ";
                                string isbn;
                                cin >> isbn;
                                loggedInUser->borrowBook(isbn, L);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 3)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Return a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the book you want to return: ";
                                string isbn;
                                cin >> isbn;
                                loggedInUser->returnBook(isbn, L);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 4)
                            {
                                cout << "========================================\n";
                                cout << "           User Details                 \n";
                                cout << "========================================\n";
                                cout << " Username  : " << loggedInUser->getUserName() << "\n";
                                cout << " User ID   : " << loggedInUser->getUserID() << "\n";
                                cout << " Fine Due  : " << loggedInUser->A.getFine() << " rupees\n";
                                cout << "========================================\n";
                                // cout << "Currently Borrowed Books: \n";
                                loggedInUser->A.displayCurrentBooks();
                                // cout << "Borrowed Books History: \n";
                                loggedInUser->A.displayHistory();
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 5)
                            {
                                cout << "========================================\n";
                                cout << "         Update User Details            \n";
                                cout << "========================================\n";
                                cout << " What would you like to change?\n";
                                cout << "   1. Username\n";
                                cout << "   2. Password\n";
                                cout << "========================================\n";
                                cout << " Enter your choice: ";
                                int choice;
                                cin >> choice;
                                if (choice == 1)
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " Enter Username\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Username: ";
                                    string newUsername;
                                    cin >> newUsername;
                                    auto it = find_if(L.users.begin(), L.users.end(),
                                                      [newUsername](const User *u)
                                                      { return u->getUserName() == newUsername; });
                                    if (it != L.users.end())
                                    {
                                        cout << "----------------------------------------\n";
                                        cout << " Matching Username Found\n";
                                        cout << "----------------------------------------\n";
                                        cout << " A matching username was found in the system.\n";
                                        cout << " Please re-enter a new username and try again.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                    else
                                    {
                                        loggedInUser->changeUserName(newUsername, L);
                                        cout << "----------------------------------------\n";
                                        cout << " Username Updated Successful\n";
                                        cout << "----------------------------------------\n";
                                        cout << " Your Username has been Successfully Updated in the System.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                }
                                else
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " Enter Password\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Password: ";
                                    string newPassword;
                                    cin >> newPassword;
                                    loggedInUser->changePassword(newPassword);
                                    cout << "----------------------------------------\n";
                                    cout << " Password Updated Successful\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Your Password has been Successfully Updated in the System.\n";
                                    cout << "----------------------------------------\n";
                                }
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 6)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Logout Successful\n";
                                cout << "----------------------------------------\n";
                                cout << " GoodBye, " << (*it)->getUserName() << "!\n";
                                cout << " You have successfully logged out of the system.\n";
                                cout << "----------------------------------------\n";
                            }
                            else
                            {
                                cout << "----------------------------------------\n";
                                cout << " Invalid Input\n";
                                cout << "----------------------------------------\n";
                                cout << " Please enter a valid integer for choosing the correct User Function\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << "  1. Search for a Book\n";
                                cout << "  2. Borrow a Book\n";
                                cout << "  3. Return a Book\n";
                                cout << "  4. View your details\n";
                                cout << "  5. Change Your Details\n";
                                cout << "  6. Logout\n";
                                cout << "========================================\n";
                                cout << " Please enter your choice: ";
                            }
                        }
                    }
                    else
                    {
                        cout << "----------------------------------------\n";
                        cout << " Invalid Password\n";
                        cout << "----------------------------------------\n";
                        cout << " The password does not match with your saved password, Please Try Again!!\n";
                        cout << "----------------------------------------\n";
                    }
                }
                else
                {
                    cout << "----------------------------------------\n";
                    cout << " Username Not Found\n";
                    cout << "----------------------------------------\n";
                    cout << " No matching username was found in the system.\n";
                    cout << " Please check the details and try again.\n";
                    cout << "----------------------------------------\n";
                }
            }
            else
            {
                cout << "=========================================\n";
                cout << " Would you like to register? \n";
                cout << " Type YES to register or NO to go back to the login page\n";
                cout << "=========================================\n";
                string answer;
                while (true)
                {

                    cin >> answer;
                    transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                    if (answer == "YES" || answer == "NO")
                    {
                        // Valid input, exit the loop
                        break;
                    }
                    else
                    {
                        cout << "----------------------------------------\n";
                        cout << " Invalid Input\n";
                        cout << "----------------------------------------\n";
                        cout << " Please type YES or NO ONLY!!\n";
                        cout << "----------------------------------------\n";
                        // Clear the input buffer to prevent infinite loop
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                if (answer == "YES")
                {
                    cout << "----------------------------------------\n";
                    cout << " Enter Username\n";
                    cout << "----------------------------------------\n";
                    cout << " Username: ";
                    string usernme;
                    while (true)
                    {
                        cin >> username;
                        auto it = find_if(L.users.begin(), L.users.end(),
                                          [username](const User *u)
                                          { return u->getUserName() == username; });
                        if (it != L.users.end())
                        {
                            cout << "----------------------------------------\n";
                            cout << " Matching Username Found\n";
                            cout << "----------------------------------------\n";
                            cout << " A matching username was found in the system.\n";
                            cout << " Please re-enter a new username and try again.\n";
                            cout << "----------------------------------------\n";
                            continue;
                        }
                        else
                        {
                            cout << "----------------------------------------\n";
                            cout << " Enter Password\n";
                            cout << "----------------------------------------\n";
                            cout << " Password: ";
                            string password;
                            cin >> password;
                            User *newUser = new Faculty(username, password, id);
                            L.users.push_back(newUser);
                            id++;
                            cout << "----------------------------------------\n";
                            cout << " User Added Successfully\n";
                            cout << "----------------------------------------\n";
                            cout << " The new user has been registered in the system.\n";
                            cout << "----------------------------------------\n";
                            cout << " Please Login Again to use the Library Management System \n";
                            cout << "----------------------------------------\n";
                            goto login_1;
                        }
                    }
                }
                else
                {
                    goto registered;
                }
            }
        }
        else
        {

            cout << "----------------------------------------\n";
            cout << " Registration Check\n";
            cout << "----------------------------------------\n";
            cout << " Are you already registered?\n";
            cout << " Type 'YES' if you are registered, or 'NO' to proceed with new registration.\n";
            cout << "----------------------------------------\n";
            cout << " Response: ";
            string answer;
            while (true)
            {

                cin >> answer;
                transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                if (answer == "YES" || answer == "NO")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "----------------------------------------\n";
                    cout << " Invalid Input\n";
                    cout << "----------------------------------------\n";
                    cout << " Please enter a valid response.\n";
                    cout << " Type 'YES' if you are registered, or 'NO' to proceed with new registration.\n";
                    cout << "----------------------------------------\n";
                    cout << " Response: ";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (answer == "YES")
            {
            login_2:

                cout << "----------------------------------------\n";
                cout << " Enter Username\n";
                cout << "----------------------------------------\n";
                cout << " Username: ";

                cin >> username;

                auto it = find_if(L.users.begin(), L.users.end(),
                                  [username](const User *u)
                                  { return u->getUserName() == username; });

                if (it != L.users.end())
                {
                    cout << "----------------------------------------\n";
                    cout << " Enter Password\n";
                    cout << "----------------------------------------\n";
                    cout << " Password: ";
                    string password;
                    cin >> password;

                    if ((*it)->authenticate(password))
                    {
                        cout << "----------------------------------------\n";
                        cout << " Login Successful\n";
                        cout << "----------------------------------------\n";
                        cout << " Welcome, " << (*it)->getUserName() << "!\n";
                        cout << " You have successfully logged into the system.\n";
                        cout << "----------------------------------------\n";

                        User *loggedInUser = *it;
                        cout << "========================================\n";
                        cout << "           User Menu Options            \n";
                        cout << "========================================\n";
                        cout << " 1. Search for a book\n";
                        cout << " 2. Search for a user\n";
                        cout << " 3. Update a Book\n";
                        cout << " 4. Add a Book\n";
                        cout << " 5. Add a User\n";
                        cout << " 6. Remove a User\n";
                        cout << " 7. Remove a Book\n";
                        cout << " 8. Change your details\n";
                        cout << " 9. Logout\n";
                        cout << " Please enter your choice: ";
                        int choice = -1;
                        while (!(choice == 9))
                        {
                            // still can add the functionality to change personal attributes like username, password;
                            if (!(cin >> choice))
                            {
                                cout << "----------------------------------------\n";
                                cout << " Invalid Input\n";
                                cout << "----------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << " Please enter a valid input only from the following choices: \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                                continue;
                            }
                            if (choice == 1)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Search for a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the title of the book you want to search for: ";
                                string title;
                                cin.ignore();
                                getline(cin, title);
                                Librarian::searchBook(L.books, title);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 2)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Search for a User\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the Username of the user you want to search for: ";
                                string username;
                                cin >> username;
                                Librarian::searchUser(L.users, username);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 3)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Update a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the book you want to update: ";
                                string isbn;
                                cin >> isbn;
                                cin.ignore();

                                Librarian::updateBook(L.books, isbn);

                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 4)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Add a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the book you want to add: ";
                                string isbn;
                                cin >> isbn;
                                cin.ignore();

                                Librarian::addNewBook(L.books, isbn);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 5)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Add a User\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the Username of the user you want to add: ";
                                string usernme;
                                cin >> username;
                                cin.ignore();

                                Librarian::addNewUser(L.users, username, id);
                                id++;
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }

                            else if (choice == 6)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Remove a User\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the Username of the user you want to remove: ";
                                string username;
                                cin >> username;
                                cin.ignore();
                                Librarian::removeUser(L.users, username);
                                id = L.users.back()->getUserID() + 1;
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 7)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Remove a Book\n";
                                cout << "----------------------------------------\n";
                                cout << " Enter the ISBN of the bookd you want to remove: ";
                                string isbn;
                                cin >> isbn;
                                cin.ignore();
                                Librarian::removeBook(L.books, isbn);
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 8)
                            {
                                cout << "========================================\n";
                                cout << "         Update User Details            \n";
                                cout << "========================================\n";
                                cout << " What would you like to change?\n";
                                cout << "   1. Username\n";
                                cout << "   2. Password\n";
                                cout << "========================================\n";
                                cout << " Enter your choice: ";
                                int choice;
                                cin >> choice;
                                if (choice == 1)
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " Enter Username\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Username: ";
                                    string newUsername;
                                    cin >> newUsername;
                                    auto it = find_if(L.users.begin(), L.users.end(),
                                                      [newUsername](const User *u)
                                                      { return u->getUserName() == newUsername; });
                                    if (it != L.users.end())
                                    {
                                        cout << "----------------------------------------\n";
                                        cout << " Matching Username Found\n";
                                        cout << "----------------------------------------\n";
                                        cout << " A matching username was found in the system.\n";
                                        cout << " Please re-enter a new username and try again.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                    else
                                    {
                                        loggedInUser->changeUserName(newUsername, L);
                                        cout << "----------------------------------------\n";
                                        cout << " Username Updated Successful\n";
                                        cout << "----------------------------------------\n";
                                        cout << " Your Username has been Successfully Updated in the System.\n";
                                        cout << "----------------------------------------\n";
                                    }
                                }
                                else
                                {
                                    cout << "----------------------------------------\n";
                                    cout << " Enter Password\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Password: ";
                                    string newPassword;
                                    cin >> newPassword;
                                    loggedInUser->changePassword(newPassword);
                                    cout << "----------------------------------------\n";
                                    cout << " Password Updated Successful\n";
                                    cout << "----------------------------------------\n";
                                    cout << " Your Password has been Successfully Updated in the System.\n";
                                    cout << "----------------------------------------\n";
                                }
                                cout << "What do you want to do next? \n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                            else if (choice == 9)
                            {
                                cout << "----------------------------------------\n";
                                cout << " Logout Successful\n";
                                cout << "----------------------------------------\n";
                                cout << " GoodBye, " << (*it)->getUserName() << "!\n";
                                cout << " You have successfully logged out of the system.\n";
                                cout << "----------------------------------------\n";
                            }
                            else
                            {
                                cout << "----------------------------------------\n";
                                cout << " Invalid Input\n";
                                cout << "----------------------------------------\n";
                                cout << " Please enter a valid integer for choosing the correct User Function\n";
                                cout << "========================================\n";
                                cout << "           User Menu Options            \n";
                                cout << "========================================\n";
                                cout << " 1. Search for a book\n";
                                cout << " 2. Search for a user\n";
                                cout << " 3. Update a Book\n";
                                cout << " 4. Add a Book\n";
                                cout << " 5. Add a User\n";
                                cout << " 6. Remove a User\n";
                                cout << " 7. Remove a Book\n";
                                cout << " 8. Change your details\n";
                                cout << " 9. Logout\n";
                                cout << " Please enter your choice: ";
                            }
                        }
                    }
                    else
                    {
                        cout << "----------------------------------------\n";
                        cout << " Invalid Password\n";
                        cout << "----------------------------------------\n";
                        cout << " The password does not match with your saved password, Please Try Again!!\n";
                        cout << "----------------------------------------\n";
                    }
                }
                else
                {
                    cout << "----------------------------------------\n";
                    cout << " Username Not Found\n";
                    cout << "----------------------------------------\n";
                    cout << " No matching username was found in the system.\n";
                    cout << " Please check the details and try again.\n";
                    cout << "----------------------------------------\n";
                }
            }
            else
            {
                cout << "=========================================\n";
                cout << " Would you like to register? \n";
                cout << " Type YES to register or NO to go back to the login page\n";
                cout << "=========================================\n";

                string answer;
                while (true)
                {

                    cin >> answer;
                    transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                    if (answer == "YES" || answer == "NO")
                    {
                        // Valid input, exit the loop
                        break;
                    }
                    else
                    {
                        cout << "----------------------------------------\n";
                        cout << " Invalid Input\n";
                        cout << "----------------------------------------\n";
                        cout << " Please type YES or NO ONLY!!\n";
                        cout << "----------------------------------------\n";
                        // Clear the input buffer to prevent infinite loop
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                if (answer == "YES")
                {
                    cout << "----------------------------------------\n";
                    cout << " Enter Username\n";
                    cout << "----------------------------------------\n";
                    cout << " Username: ";
                    string usernme;
                    while (true)
                    {
                        cin >> username;
                        auto it = find_if(L.users.begin(), L.users.end(),
                                          [username](const User *u)
                                          { return u->getUserName() == username; });
                        if (it != L.users.end())
                        {
                            cout << "----------------------------------------\n";
                            cout << " Matching Username Found\n";
                            cout << "----------------------------------------\n";
                            cout << " A matching username was found in the system.\n";
                            cout << " Please re-enter a new username and try again.\n";
                            cout << "----------------------------------------\n";
                            continue;
                        }
                        else
                        {
                            cout << "----------------------------------------\n";
                            cout << " Enter Password\n";
                            cout << "----------------------------------------\n";
                            cout << " Password: ";
                            string password;
                            cin >> password;
                            User *newUser = new Librarian(username, password, id);
                            L.users.push_back(newUser);
                            id++;
                            cout << "----------------------------------------\n";
                            cout << " User Added Successfully\n";
                            cout << "----------------------------------------\n";
                            cout << " The new user has been registered in the system.\n";
                            cout << "----------------------------------------\n";
                            cout << " Please Login Again to use the Library Management System \n";
                            cout << "----------------------------------------\n";
                            goto login_2;
                        }
                    }
                }
                else
                {
                    goto registered;
                }
            }
        }
    }
    L.saveBookData(L.books);
    L.saveUserData(L.users);
    return 0;
}
