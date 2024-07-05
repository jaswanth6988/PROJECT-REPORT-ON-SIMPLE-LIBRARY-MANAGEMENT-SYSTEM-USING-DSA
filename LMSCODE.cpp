#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int id, const string& title, const string& author)
        : id(id), title(title), author(author), isIssued(false) {}
};

void quickSort(vector<Book>& books, int low, int high);
int partition(vector<Book>& books, int low, int high);

void addBook(vector<Book>& books, int id, const string& title, const string& author) {
    // Check if book with given id already exists
    for (const Book& book : books) {
        if (book.id == id) {
            cout << "A book with ID " << id << " already exists. Please reverify and try again.\n"<<endl;
            return;
        }
    }

    // If not found, add the new book
    books.push_back(Book(id, title, author));
    cout << "Book added successfully.\n"<<endl;
}

void searchBookById(const vector<Book>& books, int id) {
    for (const Book& book : books) {
        if (book.id == id) {
            cout << "Book found\nID: " << book.id
                 << "\nTitle: " << book.title
                 << "\nAuthor: " << book.author
                 << "\nStatus: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << '\n'<<endl;
            return;
        }
    }
    cout << "Book not found.\n"<<endl;
}

void searchBookByTitle(const vector<Book>& books, const string& title) {
    for (const Book& book : books) {
        if (book.title == title) {
            cout << "Book found\nID: " << book.id
                 << "\nTitle: " << book.title
                 << "\nAuthor: " << book.author
                 << "\nStatus: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << '\n'<<endl;
            return;
        }
    }
    cout << "Book not found.\n"<<endl;
}

void issueBook(vector<Book>& books, queue<Book>& issueQueue, int id, const string& student) {
    for (Book& book : books) {
        if (book.id == id) {
            if (!book.isIssued) {
                book.isIssued = true;
                book.issuedTo = student;
                issueQueue.push(book);
                cout << "Book issued successfully to " << student << ".\n";
            } else {
                cout << "Book is already issued to " << book.issuedTo << ".\n"<<endl;
            }
            return;
        }
    }
    cout << "Book not found.\n"<<endl;
}

void returnBook(vector<Book>& books, queue<Book>& issueQueue) {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (Book& book : books) {
        if (book.id == id) {
            if (book.isIssued) {
                book.isIssued = false;
                book.issuedTo = "";
                queue<Book> tempQueue;
                while (!issueQueue.empty()) {
                    Book tempBook = issueQueue.front();
                    issueQueue.pop();
                    if (tempBook.id != id) {
                        tempQueue.push(tempBook);
                    }
                }
                swap(issueQueue, tempQueue);
                cout << "Book returned successfully.\n"<<endl;
            } else {
                cout << "Book was not issued.\n"<<endl;
            }
            return;
        }
    }
    cout << "Book not found.\n"<<endl;
}

void listAllBooks(vector<Book>& books) {
    quickSort(books, 0, books.size() - 1);

    for (const Book& book : books) {
        cout << "ID: " << book.id
             << "\nTitle: " << book.title
             << "\nAuthor: " << book.author
             << "\nStatus: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << '\n'<<endl;
    }
}

void deleteBook(vector<Book>& books, int id) {
    vector<Book>::iterator it = remove_if(books.begin(), books.end(), [id](const Book& book) {
        return book.id == id;
    });

    if (it != books.end()) {
        books.erase(it, books.end());
        cout << "Book deleted successfully.\n"<<endl;
    } else {
        cout << "Book not found.\n"<<endl;
    }
}

void quickSort(vector<Book>& books, int low, int high) {
    if (low < high) {
        int pi = partition(books, low, high);
        quickSort(books, low, pi - 1);
        quickSort(books, pi + 1, high);
    }
}

int partition(vector<Book>& books, int low, int high) {
    int pivot = books[high].id;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (books[j].id < pivot) {
            i++;
            swap(books[i], books[j]);
        }
    }
    swap(books[i + 1], books[high]);
    return (i + 1);
}

int main() {
    vector<Book> books;
    queue<Book> issueQueue;
    int choice, id;
    string title, author, student;
    cout << "**********  Welcome To Library  **********\n"<< endl;
    while (true) {
        cout << "Library Management System\n";
        cout << "1. Add New Book\n2. Search Book by ID\n3. Search Book by Title\n4. Issue Book\n5. Return Book\n6. List All Books\n7. Delete Book\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                addBook(books, id, title, author);
                break;
            case 2:
                cout << "Enter Book ID: ";
                cin >> id;
                searchBookById(books, id);
                break;
            case 3:
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                searchBookByTitle(books, title);
                break;
            case 4:
                cout << "Enter Book ID to issue: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, student);
                issueBook(books, issueQueue, id, student);
                break;
            case 5:
                returnBook(books, issueQueue);
                break;
            case 6:
                listAllBooks(books);
                break;
            case 7:
                cout << "Enter Book ID to delete: ";
                cin >> id;
                deleteBook(books, id);
                break;
            case 8:
                cout << "**********  Thanks for using the library management system  **********\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n"<<endl;
        }
    }
 return 0;
}
