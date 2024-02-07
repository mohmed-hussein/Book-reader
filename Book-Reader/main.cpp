#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
class HelperFunction{
public:
    static int getNumberInRange(int low , int high , int cnt = 3){
        if(cnt == 0) exit(500);
        cout<<"Enter number in Range ["<<low<<','<<high<<"] : ";
        int numbere ;cin>>numbere;
        if(numbere < low || numbere > high)
            return getNumberInRange(low , high , cnt - 1);
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

    Book(int numberPages, const string &bookTitle, const string &bookAuther, const vector<string> &pages , int curPage = 0)
            : numberPages(numberPages), curPage(curPage), bookTitle(bookTitle), bookAuther(bookAuther), pages(pages) {}

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
    string getCurPage(){
        return pages[curPage];
    }
    bool hasNext() const {
        return(curPage < numberPages-1);
    }
    bool hasPrevious() const{
        return (curPage > 0);
    }
     void getNext() {
        if(!this->hasNext()) return;
        curPage++;
    }
     void getPrevious(){
        if(!this->hasPrevious()) return ;
        curPage--;
    }
    string getCurPageNumber() const{
        ostringstream ret;
        ret<<'('<<(curPage + 1) <<'/' <<getNumberPages()<<')';
        return ret.str();
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
    void addBook(const Book & book){
        books.emplace_back(book);
    }
    void listBooks() const {
        int idx = 1;
        for(auto book : books){
            cout<<idx++ << ": ";
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
library * library::lib = nullptr;

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
        cout<<book.getCurPageNumber();
        cout<<' ' << ctime(&sessionDate)<<endl;
    }
};
class person{
private:
    string name , userName , passWord , email;
    int Id;
    vector<session> sessions;
public:
    person() : person("" , "" , ""){}
    person(const string &name, const string &userName, const string &passWord)
            : name(name), userName(userName), passWord(passWord) {}

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
    void readBook(Book & book){
        int choice;
        while(true){

            cout<<"Current Page : " << book.getCurPageNumber()<<endl;
            cout<<book.getCurPage()<<"\n\n";

            cout<<"Menu :" << endl;
            cout<<'\t' << "1: Next Page"<<endl;
            cout<<'\t' << "2: Previous Page"<<endl;
            cout<<'\t' << "3: Stop Reading"<<endl;

            choice = HelperFunction::getNumberInRange(1 , 3);

            if(choice == 1)
                book.getNext();
            else if(choice == 2)
                book.getPrevious();
            else if (choice == 3 ) break;
        }
    }

    void listSelectFromHistory(){
        if(sessions.empty()) return;
        cout<<"Your Sessions is : "<<endl;
        int idx = 1;
        for(auto it : sessions) {
            cout<<idx++ << ": ";
            it.printSessionInfo();
        }
        cout<<"Which session to open : "<<endl;
        int sessionIdx = HelperFunction::getNumberInRange(1 , idx-1);
        Book book = sessions[sessionIdx-1].getBook();
        readBook(book);
        sessions[sessionIdx-1].update(book);
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

    bool isEqule(const person & obj){
        return (this->getUserName() == obj.getUserName() && this->getPassWord() == obj.getPassWord());
    }

};



class BookReader{
private:
    person * currentUser;
    vector<person*>users;
    int TypeLogin;
public:
    BookReader() : TypeLogin(-1){}
    void signIn(){
        string name , username , passWord;
        cout<<"Enter Name : ";     cin>>name;
        cout<<"Enter userName : "; cin>>username;
        cout<<"Enter Pass Word " ; cin>>passWord;
        currentUser = new person(name , username , passWord);
        users.push_back(currentUser);
        TypeLogin = 0;
    }

    void logIn(){
        string username , passWord;
        cout<<"Enter userName : "; cin>>username;
        cout<<"Enter Pass Word " ; cin>>passWord;

        for(auto &it : users){
            if(it->isEqule(person("",username , passWord))){
                currentUser = it;
                cout<<"Welcome : "<<endl;
                currentUser->viewProfile();
                TypeLogin = 0;
                return;
            }
        }

        cout<<"Error : userName or Pass Word is Wrong"<<endl;
        logIn();
    }

    int  listOptions() const{
        cout<<"Menu :" << endl;
        if(TypeLogin == -1){
            cout<<"\t1: log in"<<endl;
            cout<<"\t2: sign in"<<endl;
            return 2;
        }else if(TypeLogin == 0){
            cout<<"\t1: View Profile"<<endl;
            cout<<"\t2: List & Select From My Reading History"<<endl;
            cout<<"\t3: List & Select From Available Books"<<endl;
            cout<<"\t4: LogOut"<<endl;
            return 4;
        }
    }
    void run(){
        while(true){
            int high = listOptions();
            int choice = HelperFunction::getNumberInRange(1 , high);
            if(TypeLogin == -1){
                if(choice == 1)
                    logIn();
                else signIn();
            }else if(TypeLogin == 0){

                if(choice == 1){
                    currentUser->viewProfile();
                }else if(choice == 2){
                    currentUser->listSelectFromHistory();
                }else if(choice == 3)
                    currentUser->listSelectFromLibrary();
                else logOut();
            }
        }
    }
    void logOut(){
        TypeLogin = -1;
    }
};
int main() {
    library * lib = library::getLibrary();
    Book Book1(4 , "cpp" , "mo" , {"A cpp" , "B cpp" , "C cpp" , "D cpp"});
    Book Book2(4 , "c#" , "mo" , {"A C#" , "B C#" , "C C#" , "D C#"});
    Book Book3(4 , "cxx" , "mo" , {"A cxx" , "B cxx" , "C cxx" , "D cxx"});
    lib->addBook(Book1);
    lib->addBook(Book2);
    lib->addBook(Book3);

    BookReader sys;
    sys.run();
    return 0;
}
