#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "seqlist.cpp"

using namespace std;

typedef struct
{
    string name;
    string author;
    string isbn;
    double price;
} Book;

class BookList : public SequentialList<Book>
{
public:
    BookList(int size = 100) : SequentialList<Book>(size){}
    ~BookList() {}

    void addBook(const Book &book)
    {
        append(book);
    }

    void readFromCSV(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Could not open the file: " << filename << endl;
            return;
        }

        string line, word;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream s(line);
            // TO-DO Check Book Validation
            Book book;
            getline(s, book.isbn, ',');
            getline(s, book.name, ',');
            getline(s, book.author, ',');
            s >> book.price;
            addBook(book);
        }
        file.close();
        cout << "Finish reading " << filename << endl;
    }

    void addFromCSVwithRowNum(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Could not open the file: " << filename << endl;
            return;
        }

        string line, word;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream s(line);
            // TO-DO Check Book Validation
            Book book;
            int index;
            s >> index;
            getline(s, line, ',');
            getline(s, book.isbn, ',');
            getline(s, book.name, ',');
            getline(s, book.author, ',');
            s >> book.price;
            if(insert(index, book) == false)
            {
                cout << "Could not insert book at " << index << endl;
            }
            
        }
        file.close();
        cout << "Finish reading " << filename << endl;
    }

    void removeIndexesFromInput()
    {
        int indexes[100];
        int count = 0;
        string line;
        getline(cin, line);
        getline(cin, line);
        stringstream s(line);
        while(s >> indexes[count])
        {
            count++;
        }
        sort(indexes, indexes + count, [](int a, int b){return a > b;});
        for (int i = 0; i < count; i++)
        {
            if(indexes[i] >= getLength() || indexes[i] < 0)
            {
                cout << "Invalid index: " << indexes[i] << endl;
                continue;
            }
            remove(indexes[i]);
        }
    }

    double getAveragePrice()
    {
        double sum = 0;
        for (auto i=begin(); i!=end(); i++)
        {
            Book book = *i;
            sum += book.price;
        }
        return sum / getLength();
    }

    BookList getMostExpensiveBooks()
    {
        double highest_price = 0;
        for (auto i=begin(); i!=end(); i++)
        {
            Book book = *i;
            if (book.price > highest_price)
            {
                highest_price = book.price;
            }
        }

        BookList result;
        for (auto i=begin(); i!=end(); i++)
        {
            Book book = *i;
            if (book.price == highest_price)
            {
                result.addBook(book);
            }
        }
        result.preview(result.getLength());
        return result;
    }

    void dropDuplicates()
    {
        // TO-DO Compare different books
        for (auto i=begin(); i!=end(); i++)
        {
            Book book = *i;
            for(auto j=end()-1; j!=i; j--)
            {
                Book book2 = *j;
                if (book.isbn == book2.isbn)
                {
                    cout << "Duplicate book found: " << book.isbn << ", " << book.name << endl;
                    remove(j-begin());
                }
            }
        }
    }

    // void apply(function<Book(const Book&, Args...)>& func, Args... args)
    // {
    //     auto cur = begin();
    //     for (int i = 1; i <= getLength(); i++)
    //     {
    //         Book book = *++cur;
    //         *cur = func(book);
    //     }
    // }

    void preview(int n)
    {
        if (n > getLength())
        {
            n = getLength();
            cout << "There are only " << getLength() << " books in the list." << endl;
        }
        auto cur = begin();
        for (int i = 1; i <= n; i++)
        {
            Book book = *cur++;
            cout << "Book " << i << ":" << endl;
            cout << "\tBook name: " << book.name << endl;
            cout << "\tAuthor: " << book.author << endl;
            cout << "\tISBN: " << book.isbn << endl;
            cout << "\tPrice: " << fixed << setprecision(2) << book.price << endl;
            cout << endl;
        }
    }
};

// int main() 
// {
//     BookList book_list;
//     book_list.readFromCSV("book_data.csv");
//     book_list.preview(5);
//     return 0;
// }