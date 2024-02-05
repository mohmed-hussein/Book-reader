#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
class HelperFunction{
public:
    static int getNumberInRange(int low , int high){
        cout<<"Enter number in Range ["<<low<<','<<high<<"] : ";
        int numbere ;cin>>numbere;
        if(numbere < low || numbere > high)
            return getNumberInRange(low , high);
        return numbere;
    }
};
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
    bool hasPrevious() const{
        return (getCurPageNumber() > 0);
    }
    const string &getNext() {
        if(!this->hasNext()) return pages[curPage - 1];
        return pages[curPage++];
    }
    const string & getPrevious(){
        if(!this->hasPrevious()) return pages[curPage + 1];
        return pages[--curPage];
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
        cout<< getBookTitle() <<endl;
    }
};

class library{
private:
    vector<Book> books;
    library(){};
     static library * lib;
public:
    static library * getLibrary(){
         if(lib == nullptr){
             lib = new library;
         }
        return lib;
    }
    void addBook(){
        Book newBook;
        newBook.readNewBook();
        books.emplace_back(newBook);
    }
    void listBooks() const {
        int idx = 1;
        for(auto book : books){
            cout<<idx << ": ";
            book.printInfo();
        }
    }
    int getNumberOfBooks(){
        return books.size();
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
    session(){}
    session(const Book & _book , int ID) :
        book(_book) , userID(ID) , sessionDate(time(nullptr)){}
    void update(const Book & _book){
        book = _book;
        sessionDate = time(nullptr);
    }

     Book getBook() const {
        return book;
    }

    void printSessionInfo() const {
        cout<<book.getBookTitle()<<' ';
        cout<<'('<<book.getCurPageNumber() << '/' << book.getNumberPages() <<')';
        cout<<' ' << ctime(&sessionDate)<<endl;
    }
};
class person{
private:
    string name , userName , passWord , email;
    int Id;
    bool isAdmin;
public:
    person() : person("" , "" , "" , "" , 0 ){}
    person(const string &name, const string &userName, const string &passWord, const string &email, bool isAdmin)
            : name(name), userName(userName), passWord(passWord), email(email), isAdmin(isAdmin) {}

public:
    void viewProfile() const{
        cout<<"Name : " << this->name<<endl;
        cout<<"UserName : " << this->userName<<endl;
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

    void setId(int id) {
        Id = id;
    }

    bool isAdmin1() const {
        return isAdmin;
    }

};

class user : public person{
private:
    vector<session> sessions;
public:
    user() : person(){};
    user(const string &name, const string &userName, const string &passWord, const string &email, bool isAdmin)
            : person(name, userName, passWord, email, isAdmin) {}
    void readBook(Book & book){
        int choice = 1;
        while(true){
            cout<<"Current Page : " << book.getCurPageNumber() <<'/' << book.getNumberPages()<<endl;
            if(choice == 1)
                cout<<book.getNext()<<endl;
            else if(choice == 2)
                cout<<book.getPrevious()<<endl;
            else break;

            choice = HelperFunction::getNumberInRange(1 , 3);
            cout<<"Menu :" << endl;
            cout<<'\t' << "1: Next Page"<<endl;
            cout<<'\t' << "2: Previous Page"<<endl;
            cout<<'\t' << "3: Stop Reading"<<endl;
        }
    }

    void listSelectFromHistory(){
        cout<<"Your Seessions is : ";
        for(auto it : sessions)
                it.printSessionInfo();
        cout<<"Which session to open : ";
        int sessionIdx = HelperFunction::getNumberInRange(1 , sessions.size());
        Book book = sessions[sessionIdx].getBook();
        readBook(book);
        sessions[sessionIdx].update(book);
    }

    void listSelectFromLibrary(){
        cout<<"Our Current Books Collection : "<<endl;
        library * lib = library::getLibrary();
        lib->listBooks();
        int bookIdx = HelperFunction::getNumberInRange(1 , lib->getNumberOfBooks());
        Book _book = lib->selectBook(bookIdx);
        readBook(_book);
        sessions.emplace_back(session(_book , this->getId()));
    }
};

class admin : public person{
public:
    admin(const string &name, const string &userName, const string &passWord, const string &email, bool isAdmin = 1)
            : person(name, userName, passWord, email, isAdmin) {}

    void AddBook(){
        library * lib = library::getLibrary();
        lib->addBook();
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
