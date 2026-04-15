#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int bookId;
    string title;
    string author;
    bool isIssued;
    Book() {
        isIssued = false;
    }

    void input() {
        cout << "Enter Book ID: ";
        cin >> bookId;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        isIssued = false;
    }

    void display() {
        cout << "Book ID: " << bookId << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Status: " << (isIssued ? "Issued" : "Available") << endl;
        cout << "--------------------------\n";
    }

    void issueBook() {
        isIssued = true;
    }

    void returnBook() {
        isIssued = false;
    }
};

class User {
public:
    int userId;
    string name;
    Book* issuedBook;

    User() {
        issuedBook = NULL;
    }

    void input() {
        cout << "Enter User ID: ";
        cin >> userId;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        issuedBook = NULL;
    }

    void display() {
        cout << "User ID: " << userId << endl;
        cout << "Name: " << name << endl;
        if (issuedBook != NULL)
            cout << "Issued Book ID: " << issuedBook->bookId << endl;
        else
            cout << "No book issued\n";
        cout << "--------------------------\n";
    }

    void borrowBook(Book* b) {
        if (issuedBook != NULL) {
            cout << "User already has a book!\n";
            return;
        }
        if (b->isIssued) {
            cout << "Book already issued!\n";
            return;
        }

        issuedBook = b;
        b->issueBook();
        cout << "Book issued successfully!\n";
    }

    void returnBook() {
        if (issuedBook == NULL) {
            cout << "No book to return!\n";
            return;
        }

        issuedBook->returnBook();
        issuedBook = NULL;
        cout << "Book returned successfully!\n";
    }
};

int main() {
    Book* books[100];
    User* users[100];

    int bookCount = 0, userCount = 0;
    int choice;

    do {
        cout << "\n===== Book Issuing System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add User\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Books\n";
        cout << "6. Display Users\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            books[bookCount] = new Book();
            books[bookCount]->input();
            bookCount++;
            break;

        case 2:
            users[userCount] = new User();
            users[userCount]->input();
            userCount++;
            break;

        case 3: {
            int uid, bid;
            cout << "Enter User ID: ";
            cin >> uid;
            cout << "Enter Book ID: ";
            cin >> bid;

            User* u = NULL;
            Book* b = NULL;

            for (int i = 0; i < userCount; i++)
                if (users[i]->userId == uid)
                    u = users[i];

            for (int i = 0; i < bookCount; i++)
                if (books[i]->bookId == bid)
                    b = books[i];

            if (u && b)
                u->borrowBook(b);
            else
                cout << "User or Book not found!\n";

            break;
        }

        case 4: {
            int uid;
            cout << "Enter User ID: ";
            cin >> uid;

            for (int i = 0; i < userCount; i++) {
                if (users[i]->userId == uid) {
                    users[i]->returnBook();
                    break;
                }
            }
            break;
        }

        case 5:
            for (int i = 0; i < bookCount; i++)
                books[i]->display();
            break;

        case 6:
            for (int i = 0; i < userCount; i++)
                users[i]->display();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    // Free memory
    for (int i = 0; i < bookCount; i++)
        delete books[i];

    for (int i = 0; i < userCount; i++)
        delete users[i];

    return 0;
}