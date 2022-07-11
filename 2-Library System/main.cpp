#include <iostream>
#include <algorithm>
#include <stdlib.h>
#define MAX_BOOKS 1000
#define MAX_USERS 1000
#define MAX_BORROWED_BOOKS 1000
using namespace std;

struct book
{
    string name;
    int id;
    int quantity;
    int borrowed;
    book()
    {
        borrowed = 0;
    }
}n[MAX_BOOKS];

struct user
{
    string name;
    int phone;
    int borrowed_book_id[MAX_BORROWED_BOOKS] = {-1};
    int no_borrowed;
    user()
    {
        no_borrowed = 0;
    }
}u[MAX_USERS];

int no_of_books,
    no_of_users,
    no_of_borrowed_books;

bool compare_id(book x, book y)
{
    return (y.id > x.id);
}
bool compare_name(book x, book y)
{
    return (y.name > x.name);
}

void system();
void menu();
void add_book();
void print_lib_id();
void print_lib_name();
void search_books();
void add_user();
void print_users();
void borrow_book();
void users_borrowed();
void return_book();

int main()
{
    system();
    return 0;
}

void system()
{
    menu();
    int n;
    while(true)
    {
        cout<<"\n\nEnter your choice [1 - 10]: ";
        cin>>n;
        if(1 > n || n > 10){
            cout<<"Invalid option try again\n";
            continue;
        }
        switch (n)
        {
            case 1:
                no_of_books++;
                add_book();
                break;
            case 2:
                search_books();
                break;
            case 3:
                users_borrowed();
                break;
            case 4:
                print_lib_id();
                break;
            case 5:
                print_lib_name();
                break;
            case 6:
                no_of_users++;
                add_user();
                break;
            case 7:
                no_of_borrowed_books++;
                borrow_book();
                break;
            case 8:
                return_book();
                break;
            case 9:
                print_users();
                break;
            case 10:
                exit(0);
                break;
        }
    }
}
void menu()
{
    cout<<"Library Menu:-\n";
    cout<<"1) Add book\n";
    cout<<"2) Search books by prefix\n";
    cout<<"3) Print who borrowed book by name\n";
    cout<<"4) Print library by books id\n";
    cout<<"5) Print library by books name\n";
    cout<<"6) Add user\n";
    cout<<"7) User borrows a book\n";
    cout<<"8) User returns a book\n";
    cout<<"9) Print users\n";
    cout<<"10) Exit";
}

void add_book()
{
    cout<<"Enter book info [id & name & quantity]: ";
    cin>>n[no_of_books - 1].id >> n[no_of_books - 1].name >> n[no_of_books - 1].quantity;
}

void print_lib_id()
{
    sort(n, n + no_of_books, compare_id);
    for(int i=0; i<no_of_books; i++)
        cout<<"id = "<<n[i].id<<", name = "<<n[i].name<<", total quantity "<<n[i].quantity<<", "<<n[i].borrowed<<" copies are borrowed"<<endl;
}

void print_lib_name()
{
    sort(n, n + no_of_books, compare_name);
    for(int i=0; i<no_of_books; i++)
        cout<<"id = "<<n[i].id<<", name = "<<n[i].name<<", total quantity "<<n[i].quantity<<", total borrowed "<<n[i].borrowed<<endl;
}

void search_books()
{
    bool found = false;
    string x;
    cout<<"Enter the book's name or prefix: ";
    cin>>x;
    for(int i=0; i<no_of_books; i++)
    {
        unsigned c=0;
        for(unsigned j=0; j<x.size(); j++)
            if(n[i].name[j] == x[j])
                c++;
        if(c == x.size()){
            cout << n[i].name << endl;
            found = true;
        }
    }
    if (found == false)
        cout << "No books found :(\n";
}

void add_user()
{
    cout << "Enter user name & mobile number: ";
    cin >> u[no_of_users - 1].name >> u[no_of_users - 1].phone;
}

void print_users()
{
    for(int i=0; i<no_of_users; i++)
    {
        if(u[i].no_borrowed != 0)
        {
            cout<<"#"<<i+1<<" "<<u[i].name<<", Phone no. "<<0<<u[i].phone<<", Number of borrowed books is "<<u[i].no_borrowed<<", Borrowed books Ids: ";
            for(int j=0; j<=u[i].no_borrowed; j++)
                if(u[i].borrowed_book_id[j] > 0)
                    cout<<u[i].borrowed_book_id[j]<<' ';
            cout<<endl;
        }
        else
            cout<<"#"<<i+1<<" "<<u[i].name<<", Phone no. "<<0<<u[i].phone<<", No borrowed books.\n";
    }
}

void borrow_book()
{
    string usser, boook;
    int id;
    bool found = false;
    cout<<"Enter user name & book name: ";
    cin>>usser>>boook;
    for(int i=0; i<no_of_books; i++)
    {
        if(n[i].name == boook)
        {
            if(n[i].quantity == n[i].borrowed)
            {
                cout<<"All copies of this book ("<<n[i].name<<") are borrowed :(\n";
                return;
            }
            id = n[i].id;
            found = true;
            n[i].borrowed++;
            break;
        }
    }
    if(found == false)
    {
        cout<<"Invalid user name Or book name.\n";
        return;
    }
    for(int i=0; i<no_of_users; i++)
    {
        if(u[i].name == usser)
        {
            for(int j=0; j<u[i].no_borrowed; j++)
            {
                if(u[i].borrowed_book_id[j] == id)
                {
                    cout<<u[i].name<<" already has "<<n[i].name<<endl;
                    return;
                }
            }
            u[i].no_borrowed++;
            u[i].borrowed_book_id[u[i].no_borrowed - 1] = id;
        }
    }

}

void users_borrowed()
{
    string boook;
    int id;
    bool found = false, borrowed = false;

    cout<<"Enter book name: ";
    cin>>boook;

    for(int i=0; i<no_of_books; i++)
        if(n[i].name == boook)
        {
            id = n[i].id;
            found = true;
            break;
        }

    if(found == false)
    {
        cout<<"Invalid book name.\n";
        return;
    }

    for(int i=0; i<no_of_users; i++)
    {
        for(int j=0; j<u[i].no_borrowed; j++)
        {
            if(u[i].borrowed_book_id[j] == id)
            {
                borrowed = true;
                cout<<u[i].name<<endl;
            }
        }
    }

    if(borrowed == false)
    {
        cout<<"No one borrowed "<<boook<<endl;
        return;
    }
}

void return_book()
{
    string usser, boook;
    int id;
    bool found = false, borrowed = false;
    cout<<"Enter user name & book name: ";
    cin>>usser>>boook;
    for(int i=0; i<no_of_books; i++)
        if(n[i].name == boook)
        {
            id = n[i].id;
            found = true;
            n[i].borrowed--;
            break;
        }

    if(found == false)
    {
        cout<<"Invalid user name Or book name.\n";
        return;
    }

    for(int i=0; i<no_of_users; i++)
    {
        if(u[i].name == usser)
        {
            for(int j=0; j<u[i].no_borrowed; j++)
            {
                if(u[i].borrowed_book_id[j] == id)
                {
                    u[i].borrowed_book_id[j] = -1;
                    borrowed = true;
                }
            }
            if(borrowed == false)
            {
                cout<<u[i].name<<" hasn't borrowed any book\n";
                return;
            }
            u[i].no_borrowed--;
            break;
        }
    }
}
