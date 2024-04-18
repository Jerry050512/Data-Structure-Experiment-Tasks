#include <iostream>
#include "book.cpp"

void raise_price(BookList& booklist, double low, double high);

int main()
{
    BookList book_list;
    string filename;
    Book book;
    while(true)
    {
        int i=1, option;

        cout << "[" << i++ << "]" << " Read from csv" << endl;
        cout << "[" << i++ << "]" << " Show all books" << endl;
        cout << "[" << i++ << "]" << " Search a book" << endl;
        cout << "[" << i++ << "]" << " Add a book" << endl;
        cout << "[" << i++ << "]" << " Delete a book" << endl;
        cout << "[" << i++ << "]" << " Preview first 5 books" << endl;
        cout << "[" << i++ << "]" << " Raise Price" << endl;
        cout << "[" << i++ << "]" << " Reverse the list" << endl;
        cout << "[" << i++ << "]" << " Get the most expensive book" << endl;
        cout << "[" << i++ << "]" << " Add new book from csv with given row number" << endl;
        cout << "[" << i++ << "]" << " Remove mulitiple books" << endl;
        cout << "[" << i++ << "]" << " Drop duplicates" << endl;

        cout << "[0] Exit" << endl;

        cout << "Enter your option: ";
        cin >> option;

        switch (option)
        {
        case 0:
            cout << "Exiting..." << endl;
            return 0;
        case 1:
            cout << "Enter the file name: ";
            cin >> filename;
            // filename = "book_data.csv";
            book_list.readFromCSV(filename);
            break;
        case 2:
            book_list.preview(book_list.getLength());
            break;
        case 4:
            cout << "Enter the book name: ";
            cin >> book.name;
            cout << "Enter the author name: ";
            cin >> book.author;
            cout << "Enter the ISBN: ";
            cin >> book.isbn;
            cout << "Enter the price: ";
            cin >> book.price;
            book_list.addBook(book);
            break;
        case 5:
            cout << "Enter the index: ";
            cin >> i;
            book_list.remove(i);
            cout << "Removed book at index " << i << endl;
            break;
        case 6:
            book_list.preview(5);
            break;
        case 7:
            raise_price(book_list, 1.2, 1.1);
        case 8:
            book_list.reverse();
            book_list.preview(5);
        case 9:
            book_list.getMostExpensiveBooks();
        case 10:
            book_list.addFromCSVwithRowNum("new_book_data.csv");
        case 11:
            cout << "Enter the indexes: ";
            book_list.removeIndexesFromInput();
            break;
        case 12:
            book_list.dropDuplicates();
            break;
            
        default:
            break;
        }
    }
}

void raise_price(BookList& booklist, double low, double high)
{
    double avg_price = booklist.getAveragePrice();
    cout << "Average Price: " << avg_price << endl;
    cout << "\nBefore Price Raise: " << endl;
    booklist.preview(5);
    for(auto &book : booklist)
    {
        if(book.price < avg_price)
        {
            book.price *= low;
        }
        else
        {
            book.price *= high;
        }
    }
    cout << "\nAfter Price Raise: " << endl;
    booklist.preview(5);
}