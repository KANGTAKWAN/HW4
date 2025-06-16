#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; 

public:
    
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); 
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { 
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    void searchByTitle(const string& title) {
        for (Book& book : books) {
            if (title == book.title) {
                cout << "책제목" << title << "을(를) 찾았습니다." << endl;
                return;
            }
        }
        cout << title << "을(를) 찾지 못했습니다." << endl;
    }
    void searchByAuthor(const string& author) {
        for (Book& book: books) {
            if (author == book.author) {
                cout << "책제목" << book.title << "을(를) 찾았습니다." << endl;
                return;
            }
        }
        cout << author << "을(를) 찾지 못했습니다." << endl;
    }

    Book* findBookByTitle(const string& title) {
        for (Book& book: books) {
            if (title == book.title) {
                return &book;
            }
        }
        return nullptr;
    }
    Book* findBookByAuthor(const string& author) {
        for (Book& book: books) {
            if (author == book.author) {
                return &book;
            }
        }
        return nullptr;
    }
};
class BorrowManager {
private:
    unordered_map<string, int> stock;
public:
    void initializeStock(const Book* book, int quantity = 3) {
        if (nullptr == book) {
            return;
        }
        stock[book->title] = quantity;
        cout << "책이 추가되었습니다: " << book->title << "by" << book->author << endl;
    }
    void borrowBook(const string& title) {
        if (stock.end() != stock.find(title)) {
            if (0 < stock[title]) {
                --stock[title];
                cout << title << "을(를) 대여했습니다." << endl;
            }
            else {
                cout << "재고가 부족하여 " << title << "을(를) 대여하지 못했습니다." << endl;
            }
        }
        else {
            cout << title << "이라는 책을 찾지 못했습니다." << endl;
        }
    }
    void returnBook(const string& title) {
        if (stock.end() != stock.find(title)) {
            if (3 > stock[title]) {
                ++stock[title];
                cout << title << "을(를) 반납했습니다." << endl;
            }
            else {
                cout << title << "을(를) 반납하지 못했습니다." << endl;
            }
        }
        else {
            cout << title << "이라는 책을 찾지 못했습니다." << endl;
        }
    }
    void displayStock() {
        for (pair<const string, int> e : stock) {
            cout << "책 제목: " << e.first << "책 재고: " << e.second << endl;
        }
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    bookManager.addBook("홍길동전", "허균");
    bookManager.addBook("반지의제왕", "톨킨");

    borrowManager.initializeStock(bookManager.findBookByTitle("홍길동전"));
    borrowManager.initializeStock(bookManager.findBookByTitle("반지의제왕"));

    while (true) {
        system("cls");

        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl;
        cout << "2. 모든 책 출력" << endl;
        cout << "3. 제목으로 책 검색" << endl; 
        cout << "4. 저자로 책 검색" << endl;
        cout << "5. 책 대여" << endl;
        cout << "6. 책 반납" << endl;
        cout << "7. 책 재고 출력" << endl;
        cout << "8. 종료" << endl;
        cout << "선택: ";

        int choice; 
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "책 제목: ";
            getline(cin, title); 
            cout << "책 저자: ";
            getline(cin, author); 
            bookManager.addBook(title, author); 
        }
        else if (choice == 2) {
            bookManager.displayAllBooks();
        }
        else if (choice == 3) {
            string title;
            cout << "검색할 책 제목:";
            getline(cin, title);
            bookManager.searchByTitle(title);
        }
        else if (choice == 4) {
            string author;
            cout << "검색할 작가 이름:";
            getline(cin, author);
            bookManager.searchByAuthor(author);
        }
        else if (choice == 5) {
            cout << "대여할 책 제목 또는 작가 이름: ";
            string query;
            getline(cin, query);

            Book* book = bookManager.findBookByTitle(query);
            if (book) {
                borrowManager.borrowBook(book->title);
            }
            else {
                book = bookManager.findBookByAuthor(query);
                if (book) {
                    borrowManager.borrowBook(book->title);
                }
                else {
                    cout << "관련된 책 정보가 존재하지 않습니다." << endl; 
                }
            }
        }
        else if (choice == 6) {
            cout << "반납할 책 제목 또는 작가 이름:";
            string query;
            getline(cin, query);

            Book* book = bookManager.findBookByTitle(query);
            if (book) {
                borrowManager.returnBook(book->title);
            }
            else {
                book = bookManager.findBookByAuthor(query);
                if (book) {
                    borrowManager.returnBook(book->title);
                }
                else {
                    cout << "관련된 책 정보가 없습니다." << endl;
                }
            }
        }
        else if (choice == 7) {
            borrowManager.displayStock();
        }
        else if (choice == 8) {
            cout << "프로그램을 종료합니다." << endl;
            break; 
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }

        system("pause");
    }

    return 0;
}
