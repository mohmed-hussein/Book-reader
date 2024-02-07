#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <stdexcept>

using namespace std;

class HelperFunction {
public:
    static int getNumberInRange(int low, int high, int cnt = 3) {
        if (cnt == 0)
            exit(500);
        cout << "Enter number in Range [" << low << ',' << high << "] : ";
        int numbere;
        cin >> numbere;
        if (numbere < low || numbere > high)
            return getNumberInRange(low, high, cnt - 1);
        return numbere;
    }
};

class Book {
private:
    int numberPages, curPage;
    string bookTitle, bookAuthor;
    vector<string> pages;

public:
    Book() : numberPages(0), curPage(0), bookAuthor(""), bookTitle("") {}
    Book(int numberPages, const string &bookTitle, const string &bookAuthor, const vector<string> &pages, int curPage = 0)
            : numberPages(numberPages), curPage(curPage), bookTitle(bookTitle), bookAuthor(bookAuthor), pages(pages) {}

    int getNumberPages() const {
        return numberPages;
    }

    const string &getBookTitle() const {
        return bookTitle;
    }

    const string &getBookAuthor() const {
        return bookAuthor;
    }

    void setPages(const vector<string> &pages) {
        this->pages = pages;
    }

    string getCurPage() const {
        return pages[curPage];
    }

    bool hasNext() const {
        return curPage < numberPages - 1;
    }

    bool hasPrevious() const {
        return curPage > 0;
    }

    void getNext() {
        if (!hasNext())
            return;
        curPage++;
    }

    void getPrevious() {
        if (!hasPrevious())
            return;
        curPage--;
    }

    string getCurPageNumber() const {
        ostringstream ret;
        ret << '(' << (curPage + 1) << '/' << getNumberPages() << ')';
        return ret.str();
    }

    void readNewBook() {
        cout << "Enter Book's Title : ";
        cin >> bookTitle;

        cout << "Enter Author Name : ";
        cin >> bookAuthor;

        cout << "Enter Number of Pages : ";
        cin >> numberPages;

        for (int i = 0; i < numberPages; i++) {
            cout << "Enter content of page number : " << i + 1 << endl;
            string page;
            cin >> page;
            pages.emplace_back(page);
        }
    }

    void printInfo() const {
        cout << getBookTitle() << endl;
    }
};

class Library {
private:
    vector<Book> books;

    Library() {}
    static Library *lib;

public:
    static Library *getLibrary() {
        if (lib == nullptr) {
            lib = new Library;
        }
        return lib;
    }

    void addBook() {
        Book newBook;
        newBook.readNewBook();
        books.emplace_back(newBook);
    }

    void addBook(const Book &book) {
        books.emplace_back(book);
    }

    void listBooks() const {
        int idx = 1;
        for (const auto &book : books) {
            cout << idx++ << ": ";
            book.printInfo();
        }
    }

    int getNumberOfBooks() const {
        return books.size();
    }

    Book selectBook(int idx) const {
        return books[idx - 1];
    }
};

Library *Library::lib = nullptr;

class Session {
private:
    Book book;
    time_t sessionDate;
    int userID;

public:
    Session() {}
    Session(const Book &_book, int ID)
            : book(_book), userID(ID), sessionDate(time(nullptr)) {}

    void update(const Book &_book) {
        book = _book;
        sessionDate = time(nullptr);
    }

    Book getBook() const {
        return book;
    }

    void printSessionInfo() const {
        cout << book.getBookTitle() << ' ';
        cout << book.getCurPageNumber();
        cout << ' ' << ctime(&sessionDate) << endl;
    }
};

class Person {
private:
    string name, userName, passWord;
    int Id;
    vector<Session> sessions;

public:
    Person() : Person("", "", "") {}
    Person(const string &name, const string &userName, const string &passWord)
            : name(name), userName(userName), passWord(passWord) {}

    void viewProfile() const {
        cout << "Name : " << name << endl;
        cout << "UserName : " << userName << endl;
    }

    const string &getUserName() const {
        return userName;
    }

    const string &getPassWord() const {
        return passWord;
    }

    int getId() const {
        return Id;
    }

    void readBook(Book &book);

    void listSelectFromHistory();

    void listSelectFromLibrary();

    bool isEqual(const Person &obj) const {
        return (getUserName() == obj.getUserName() && getPassWord() == obj.getPassWord());
    }
};

class BookReader {
private:
    Person *currentUser;
    vector<Person*> users;

public:
    BookReader() : currentUser(nullptr) {}

    void signIn();

    void logIn();

    int listOptions() const;

    void run();

    void logOut();
};



void Person::readBook(Book &book) {
    int choice;
    while (true) {
        cout << "Current Page : " << book.getCurPageNumber() << endl;
        cout << book.getCurPage() << "\n\n";

        cout << "Menu :" << endl;
        cout << '\t' << "1: Next Page" << endl;
        cout << '\t' << "2: Previous Page" << endl;
        cout << '\t' << "3: Stop Reading" << endl;

        choice = HelperFunction::getNumberInRange(1, 3);

        if (choice == 1)
            book.getNext();
        else if (choice == 2)
            book.getPrevious();
        else if (choice == 3)
            break;
    }
}

void Person::listSelectFromHistory() {
    if (sessions.empty())
        return;

    cout << "Your Sessions are: " << endl;
    int idx = 1;
    for (const auto &session : sessions) {
        cout << idx++ << ": ";
        session.printSessionInfo();
    }

    cout << "Which session to open: " << endl;
    int sessionIdx = HelperFunction::getNumberInRange(1, idx - 1);
    Book book = sessions[sessionIdx - 1].getBook();
    readBook(book);
    sessions[sessionIdx - 1].update(book);
}

void Person::listSelectFromLibrary() {
    cout << "Our Current Books Collection: " << endl;
    Library *lib = Library::getLibrary();
    lib->listBooks();
    int bookIdx = HelperFunction::getNumberInRange(1, lib->getNumberOfBooks());
    Book _book = lib->selectBook(bookIdx);
    readBook(_book);
    sessions.emplace_back(Session(_book, getId()));
}

void BookReader::signIn() {
    string name, username, passWord;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter UserName: ";
    cin >> username;
    cout << "Enter PassWord: ";
    cin >> passWord;
    currentUser = new Person(name, username, passWord);
    users.push_back(currentUser);
}

void BookReader::logIn() {
    string username, passWord;
    cout << "Enter UserName: ";
    cin >> username;
    cout << "Enter PassWord: ";
    cin >> passWord;

    for (auto &user : users) {
        if (user->isEqual(Person("", username, passWord))) {
            currentUser = user;
            cout << "Welcome: " << endl;
            currentUser->viewProfile();
            return;
        }
    }

    cout << "Error: UserName or PassWord is Wrong" << endl;
    logIn();
}

int BookReader::listOptions() const {
    cout << "Menu :" << endl;
    if (currentUser == nullptr) {
        cout << "\t1: Log In" << endl;
        cout << "\t2: Sign In" << endl;
        return 2;
    } else {
        cout << "\t1: View Profile" << endl;
        cout << "\t2: List & Select From My Reading History" << endl;
        cout << "\t3: List & Select From Available Books" << endl;
        cout << "\t4: Log Out" << endl;
        return 4;
    }
}

void BookReader::run() {
    while (true) {
        int high = listOptions();
        int choice = HelperFunction::getNumberInRange(1, high);

        if (currentUser == nullptr) {
            if (choice == 1)
                logIn();
            else if (choice == 2)
                signIn();
        } else {
            if (choice == 1) {
                currentUser->viewProfile();
            } else if (choice == 2) {
                currentUser->listSelectFromHistory();
            } else if (choice == 3) {
                currentUser->listSelectFromLibrary();
            } else {
                logOut();
            }
        }
    }
}

void BookReader::logOut() {
    currentUser = nullptr;
}

int main() {
    Library *lib = Library::getLibrary();
    Book book1(4, "cpp", "mo", {"A cpp", "B cpp", "C cpp", "D cpp"});
    Book book2(4, "c#", "mo", {"A C#", "B C#", "C C#", "D C#"});
    Book book3(4, "cxx", "mo", {"A cxx", "B cxx", "C cxx", "D cxx"});
    lib->addBook(book1);
    lib->addBook(book2);
    lib->addBook(book3);

    BookReader sys;
    sys.run();

    return 0;
}
