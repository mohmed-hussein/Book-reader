#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Book{
private:
    int numberPages , curPage;
    string bookTitle ,bookAuther;
    vector<string>pages;
public:
    Book() :numberPages(0) , curPage(0) ,
            bookAuther("") , bookTitle(""){}

    int getNumberPages() const {
        return numberPages;
    }

    const string &getBookTitle() const {
        return bookTitle;
    }

    const string &getBookAuther() const {
        return bookAuther;
    }

    void setPages(const vector<string> &pages) {
        Book::pages = pages;
    }

    bool hasNext() const {
        return(curPage < numberPages);
    }
    const string &getNext() {
        if(!this->hasNext()) return "";
        return pages[curPage++];
    }
    int getCurPageNumber() const{
        return curPage+1;
    }
    void readNewBook(){
        cout<<"Enter Book's Title : ";
        cin>>this->bookTitle;

        cout<<"Enter Auther Name : ";
        cin>>this->bookAuther;

        cout<<"Enter Number of Pages : ";
        cin>>this->numberPages;

        for(int i = 0 ; i < numberPages ; i++){
            cout<<"Enter content of page number : " << i + 1 << endl;
            string page;cin>>page;
            pages.emplace_back(page);
        }
    }
    void printInfo() const {
        cout<<"Book Name : " << getBookTitle() <<endl;
        cout<<"Number of Pages : " << getNumberPages() << endl;
    }
};

class library{
private:
    vector<Book> books;
public:
    void addBook(const Book & newBook){
        books.emplace_back(newBook);
    }
    void listBooks() const {
        for(auto book : books) book.printInfo();
    }
    Book selectBook(int idx) const {
        return books[idx - 1];
    }
};

class session{
private:
    Book book;
    time_t sessionDate;
    int userID;
public:
    session(const Book &book, time_t Date, int userId) :
        book(book), sessionDate(Date), userID(userId) {}

    void printSessionInfo() const {
        cout<<"Book Name : " << book.getBookTitle()<<endl;
        cout<<"Current Page " << book.getCurPageNumber()<<endl;
        cout<<sessionDate<<endl;
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
