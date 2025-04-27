# Library Management System

## Overview of the System

This application has been developed as part of the **CS253** course assignments offered in the **2024-25-II Semester** under the guidance of Prof. Indranil Saha.

## Basic Structure of the Application

**Database management** is handled using **C++ file handling**, and all interactions with the application are conducted via the **terminal**.<br>
The system maintains two primary databases: **users.txt** and **books.txt**.

### `users.txt`

This file stores information for three types of users: **Students, Faculty, and Librarians**. All users are recorded in a single database and distinguished by their `usertype`. Each entry consists of a `Username`, `Password`, `Usertype` (Student, Faculty, Librarian), `User ID`, `Outstanding Fine Amount`, `Current Number of Borrowed Books`, followed by the `ISBN` and `Title` of the borrowed books. It also includes the `Number of Previously Borrowed Books` along with their `ISBN`, `Title`, `Borrow Date`, and `Return Date`.

### `books.txt`

This file stores details about books, including `Title`, `Author`, `Publisher`, `ISBN`, `Year of Publication`, `Status` (Available or Borrowed), `Current Borrower Username` (if borrowed), and `Last Borrowed Date`.

The entire application is implemented in **C++**, utilizing **Object-Oriented Programming (OOP)** principles.
The code is structured as following :<br>

- `Class.hpp` : This header file contains the declarations of all the classes and their concerned functions:
  - `Book` class:
    - Attributes : title, author, publisher, ISBN, year, isAvailable, borrower, latest_borrowed_date.
    - Functions : to display and change each of the Attributes.
  - `Account` class:
    - Each User has an account associated with him/her.
    - Attributes : A of currently borrowed books, stored as a set of pairs,a list of previously borrowed books, alongwith the concerned dates (stored as a vector of pair of two pairs), and fine associated with the user.
    - Functions : Functions to add the details any book which is being borrowed or returned, to dispay the currently borrowed or previously borrowed books,to calculate, display and pay the fine, it also includes a utility function to check if a faculty has any book for over 60 days.
  - `Library` class:
    - Attributes : a list of the books and users in the system, which is read and saved between every two times the system is run.
    - Functions : Contains functions to load and save both the data of books and that of the users.
  - `User` class:
    - Base class of the three derived classes : Student, Librarian and Faculty.
    - Attributes : userName (being used as an ID, but also has an ID associated with the user), password, usertype, userID
    - Functions : constructor and destructor, two virtual functions namely to borrow and return books which makes the class abstract, also functions to change and view each of the attributes.
  - `Student` class:
    - Attributes : associated values of maximum borrow days, fine rate and maximum number of books that can be borrowed at one time.
    - Functions : constructor and destructor, a function to get the fine and redefinitions of the virtual functions of the base class.
  - `Faculty` class:
    - Attributes : associated values of maximum borrow days and maximum number of books that can be borrowed at one time.
    - Functions : constructor and destructor, and redefinitions of the virtual functions of the base class.
  - `Librarian` class:
    - Attributes : no special attributes.
    - Functions  : constructor and destrcutor functions, functions to add, remove, search users and book, and also a functions to update a book. Includes a redundant definition of virtual functions of the base class which are not used by any object of this class.
- `books.cpp` : This file contains all the implementations of `Book` class.
- `Account.cpp` : This file contains all the implementations of `Account` class.
- `Library.cpp` : This file contains all the implementations of `Library` class.
- `Users.cpp` : This file contains all the implementations of the `User` class as well as all of its derived classes namely the `Student`, `Librarian` and `Faculty` classes.
- `Utils.cpp` : This file contains two helper/utility functions which help with the calculation of the days between two dates and the current date, which is being used extensively in the system.


This structured approach ensures efficient tracking of users and books within the **Library Management System**.

## Features and Functionalities

- **Students and Faculty** can search for a book, borrow a book, return a book, and update personal details such as username and password. Students can also pay fines.
- **Librarians** can search for a book/user, add a book/user, delete a book/user, update book details, and update only the user ID of users.

## Assumptions and some other points
The following has been assumed during the development of the code:
- The **Status** of the book has been represented by the integer variable isAvailable which assumes values **0** for **borrowed**, **1** for **available** and **2** for **reserved**.
- The **userType** has been represented by an integer variable of the same name, which assumes value **0** for a **student**, **1** for a **faculty** and **2** for a **librarian**.
- All the **Users** have a **unique ID**, but are also provided with unique **Usernames**, so **Usernames** have been used as **IDs** to search the user throughout the system.
- All the **Books** have a **unique ISBN** which acts as an **ID** of the book since it is assumed that each book has only **ONE** copy in the system.
- The **ID** of the users is calculated always as:
    ```ID of the last user in the vector of users + 1```
  This allows the **Uniqueness** of the **ID** although disrupts the continuity of the **IDs**.
- The files saving the data are updated after the user logs out successfully, they are not updated while the program is running or if the program is terinated say by pressing the key combination:
  ```CTRL + C ```
- It is assumed that the **Students** can themselves handle their fines, be it viewing them or paying them and there exists an option for the student to pay the fine.
- The fines are always associated with a book and the student has to specify the **ISBN** of the book for which the fine is being paid. Also the student is not allowed to pay the fine in installments, it is always the complete fine for a particular book.
- The student is only allowed to return a book, **if their is no fine incurred by the book or the student agrees to pay the fine**, otherwise the student cannot return the book.
- A book cannot be **Updated** or **Deleted** by the Librarian if it is currently borrowed by someone. Similarly if a **User** has borrowed any book he cannot be **Deleted** by the Librarian unless he **Returns** the book.
- **Reserved** Books do not have any particular user associated with it, only an user logging in as a **Librarian** can change its status to available so that a user can borrow it. Similarly only **Librarian** has the right to make a book **Reserved**.

## Portability
The system has been made in a Windows operating system. So there might be complications, causing disruption in functinalities in other operating systems. Although, there has been maximum effort to include cross platform libraries in the headers, and there are no hard-coded paths.

## Usage
  - First make sure that all the code and data files are in the same folder, since the code has been written assuming the same if the paths are being considered.<br>
  - Compile the code using `g++ compiler`:

    `g++ main.cpp -o main`

  - Then run the code by using :

    `.\main`

## Made By:
  - NAME   : BIKRAMJEET SINGH
  - AUTHOR : 230298
