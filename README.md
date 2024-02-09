# Online Reader System

This is a simple console-based Online Reader System written in C++. The system allows users to log in, sign up, and perform various actions based on their roles (Admin or User). Users can view their profile, read books, and manage their reading history. Admins, on the other hand, can also add books to the system.

## Table of Contents
- [Features](#features)
- [How to Use](#how-to-use)
- [Project Structure](#project-structure)
- [Code Overview](#code-overview)
- [Dependencies](#dependencies)
- [Build and Run](#build-and-run)

## Features

- User authentication (login and signup).
- Different views for Admin and User roles.
- Users can view their profile, read books, and manage reading history.
- Admins can add new books to the system.


## Project Structure

The project is organized into several classes, each handling specific functionalities:

- `Book`: Represents a book with ISBN, title, author, and pages.
- `BookReadingSession`: Manages the reading session for a specific book.
- `User`: Represents a user with a username, password, name, email, and role (Admin or User).
- `UsersManager`: Manages user-related operations such as login, signup, and user data.
- `BooksManager`: Manages book-related operations such as adding, updating, and deleting books.
- `UserView`: Handles the user interface for regular users.
- `AdminView`: Handles the user interface for administrators.
- `OnlineReaderSystem`: Orchestrates the entire system.

## Code Overview

- The code is written in C++ and follows object-oriented principles.
- Classes are used to encapsulate data and functionality, promoting modularity.
- The system employs a simple console interface for user interaction.
- User authentication is implemented with login and signup functionality.
- Reading sessions are managed for individual users, allowing them to keep track of their reading history.
- Admins have the ability to add new books to the system.

## Dependencies

The project has no external dependencies and is written in standard C++.

