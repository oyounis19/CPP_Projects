#include <bits/stdc++.h>
using namespace std;

string current_username;
bool admin = 0;

void system();
void log_menu();
const string currentDateTime();
int login_or_signup();
void Login();
void Signup();
void validate_username(string &username);
int generate_id();
void user_menu();
void View_profile();
void R_history();
void A_books();
vector<string> lines_of_book(int n);
void session_stamp(int x, int b, int y, string z);
void open_session(int current_page, int n);
void Add_book();

int main()
{
    system();
    return 0;
}

const string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

void system() {
    bool logged_out = 1;
    while(1)
    {
        int n;
        if(logged_out)
        {
            log_menu();
            n = login_or_signup();

            if(n == 1)
                Login();
            else
                Signup();

            user_menu();
            logged_out = 0;
        }
        if(!admin)// user interface
        {
            cout<<"\nEnter number in range 1 - 4: ";
            cin>>n;
            switch(n)
            {
                case 1:
                    View_profile();
                    break;
                case 2:
                    R_history();
                    break;
                case 3:
                    A_books();
                    break;
                case 4:
                    logged_out = 1;
                    break;
                default:
                    cout<<"Invalid input...";
            }
        }
        else// Admin interface
        {
            cout<<"\nEnter number in range 1 - 3: ";
            cin>>n;
            switch(n)
            {
                case 1:
                    View_profile();
                    break;
                case 2:
                    Add_book();
                    break;
                case 3:
                    logged_out = 1;
                    break;
                default:
                    cout<<"Invalid input...";
            }
        }
    }
}

void log_menu()
{
    cout<<"Main menu:\n";
    cout<<"\t1: Login\n";
    cout<<"\t2: Sign up\n\n";
}

int login_or_signup()
{
    int n = 0;
    while(1 > n || n > 2)
    {
        cout<<"Enter number in range 1 - 2: ";
        cin>>n;
        if(1 > n || n > 2)
            cout<<"Invalid input...\n";
    }
    return n;
}

void Login()
{
    string username, pass, users, passes, line, adm;
    ifstream fin("users.txt", ios::in);
    bool found = 0;
    do
    {
        cout<<"Enter username: ";
        cin>>username;
        if(username == "-1")
        {
            Signup();
            return;
        }
        cout<<"Enter password: ";
        cin>>pass;
        while(getline(fin, line))
        {
            istringstream in(line);
            in>>users>>passes;
            if(username == users && pass == passes){
                found = 1;
                in>>adm;
                if(adm == "adm")
                    admin = 1;
                else
                    admin = 0;
                break;
            }
        }
        if(!found){
            cout<<"Invalid username or password...[To sign up, type -1]\n";
            fin.clear();
            fin.seekg(0, ios::beg);
        }
    }while(!found);
    fin.close();
    current_username = username;
    if(!admin)
        cout<<"Welcome, "<<username<<"!! | User View\n";
    else
        cout<<"Welcome, "<<username<<"!! | Admin View\n";
}

void Signup()
{
    string username, pass, email;

    cout<<"Email: ";    cin>>email;
    cout<<"Username: "; cin>>username;
    cout<<"Password: "; cin>>pass;

    validate_username(username);

    ofstream fout("users.txt", ios::out | ios:: app);
    fout<<username<<' '<<pass<<' '<<email<<endl;
    fout.close();

    current_username = username;
    admin = 0;
    cout<<"Welcome, "<<username<<"!! | User View\n";
}

void validate_username(string &username)
{
    bool found = 0;
    string users;
    ifstream fin("users.txt", ios::in);
    do// Validating unique username.
    {
        if(found == 1)
        {
            cout<<"This username already taken :(\nUsername: ";
            cin>>username;
        }
        found = 0;
        while(!fin.eof())
        {
            fin>>users;
            if(users == username)
            {
                found = 1;
                break;
            }
        }
    }while(found);
    fin.close();
}

void user_menu()
{
    if(!admin) {
    cout<<"Menu:\n";
    cout<<"1: View Profile\n";
    cout<<"2: Reading history\n";
    cout<<"3: Available Books\n";
    cout<<"4: Logout\n";
    }
    else {
        cout<<"Menu:\n";
        cout<<"1: View Profile\n";
        cout<<"2: Add Book\n";
        cout<<"3: Logout\n";
    }
}

void View_profile()
{

    if(admin){
        cout<<"ADMIN \n"; return;}

    string username, pass, email, line;
    ifstream fin("users.txt", ios::in);

    while(getline(fin, line))
    {
        istringstream In(line);
        In>>username;
        if(current_username == username) {
                In>>pass>>email;
            cout<<"User name: "<<username<<endl;
            cout<<"Email: "<<email<<endl;
            break;
        }
    }
    fin.close();
}

void R_history()
{
    ifstream fin("sessions.txt", ios::in);
    string line, username, session, words;
    vector<string> sessions;
    vector<int> book_numbers;
    int i=1, book_number, n, current_page = 1;

    while(getline(fin, line))
    {
        istringstream In(line);
        In>>book_number>>username;

        if(username == current_username) {
            getline(In, session);
            cout<<i<<":"<<session<<endl;
            sessions.push_back(session);
            book_numbers.push_back(book_number);
            i++;
        }
    }
    fin.close();

    cout<<"Which session to open?\n";
    do{
        cout<<"Enter number in range 1 - "<<sessions.size()<<": ";
        cin>>n;
        if(1 > n || n > (int)sessions.size())
            cout<<"Invalid input...\n";
    }while(1 > n || n > (int)sessions.size());

    istringstream In(sessions[n-1]);

    while(In>>words){
        if(words == "Page:"){
            In>>current_page;
            break;
        }
    }

    open_session(current_page, book_numbers[n-1]);
}

void A_books()
{
    ifstream fin("books.txt", ios::in);
    string line, ref, book_name;
    int no_of_books=0, n;

    cout<<"Our current book collection:\n";
    while(getline(fin, line))// counting number of books
    {
        istringstream In(line);
        In>>ref;
        if(ref == "book:"){
            getline(In, line);
            no_of_books++;
            cout<<"\t"<<no_of_books<<' '<<line<<endl;
        }
    }
    cout<<"Which book to read?\n";
    do{
        cout<<"Enter number in range 1 - "<<no_of_books<<": ";
        cin>>n;

        if(1>n || n>no_of_books)
            cout<<"Invalid input...\n";

    }while(1>n || n>no_of_books);

    fin.close();

    int book_num, current_page = 1;
    ifstream sin("sessions.txt");
    string username, words, x;
    bool found = 0;

    while(getline(sin, line))// to continue reading from last time if found
    {
        istringstream In(line);
        In>>book_num>>username;
        if(book_num == n && username == current_username)
        {
            while(In>>words){
                if(words == "Page:"){
                    In>>current_page;
                    found = 1;
                    break;
                }
            }
        }
    }
    if(found)
    {
        cout<<"Do you want to continue reading from last time? (y , n): ";
        cin>>x;
        if(x == "yes")
            open_session(current_page, n);
        else
            open_session(1, n);
    }
    else
        open_session(1, n);
}

vector<string> lines_of_book(int n)
{
    ifstream fin("books.txt", ios::in);
    vector<string> pages;
    bool thats_it = 0, once = 1;
    string line, ref, book_name;
    int num=0;
    int i=0;

    while(getline(fin, line))
    {
        istringstream In(line);
        In>>ref;
        if(ref == "book:")
            i++;
        if(thats_it)
        {
            if(i != n)
                break;
            num++;
            pages.push_back(line);
        }

        if(i == n && once){
            thats_it = 1;
            getline(In, book_name);
            once = 0;
        }
    }

    pages.insert(pages.begin(), to_string(num));// how many pages in the chosen book [1]
    pages.insert(pages.begin(), book_name);// returning book's name [0]
    fin.close();
    return pages;
}

void session_stamp(int current_page, int book_number, int no_of_pages, string book_name)
{
    ifstream fin("sessions.txt", ios::in);
    string line, name, word, time;
    ofstream temp("temp.txt");
    bool found = 0;
    int num;

    while(getline(fin, line))// deleting the old session if found and creating new one
    {
        istringstream In(line);
        In>>num>>name;
        if(num == book_number && name == current_username) {
            temp<<book_number<<' '<<current_username<<' '<<book_name<<" Page: "<<current_page<<"/"<<no_of_pages<<" - "<<currentDateTime()<<endl;
            found = 1;
        }
        else
            temp<<line<<endl;
    }
    if(!found)
        temp<<book_number<<' '<<current_username<<' '<<book_name<<" Page: "<<current_page<<"/"<<no_of_pages<<" - "<<currentDateTime()<<endl;

    temp.close();
    fin.close();
    remove("sessions.txt");
    rename("temp.txt", "sessions.txt");
}

void open_session(int current_page, int book_number)
{
    ifstream fin("books.txt", ios::in);
    string book_name;
    int no_of_pages, n;

    vector<string> pages = lines_of_book(book_number);

    book_name = pages[0];
    pages.erase(pages.begin());

    no_of_pages = stoi(pages[0]);
    pages.erase(pages.begin());

    while(1)
    {
        cout<<"Current Page: "<<current_page<<"/"<<no_of_pages<<endl;
        cout<<pages[current_page-1]<<endl;

        cout<<"Menu:\n";
        cout<<"\t1: Next Page\n";
        cout<<"\t2: Previous Page\n";
        cout<<"\t3: Stop reading\n";

        cout<<"\nEnter number in range 1 - 3: ";
        cin>>n;
        if(n == 1 && current_page < no_of_pages)
            current_page++;
        else if(n == 2 && current_page > 1)
            current_page--;
        else if(n == 3){
            session_stamp(current_page, book_number, no_of_pages, book_name);
            break;
        }
        else
            cout<<"Invalid input...\n";
    }
    fin.close();
}

void Add_book()
{
    string title, pages;
    int no_of_pages;
    vector<string> content;

    cout<<"Enter the book's Title: "; cin.ignore(); getline(cin, title);
    cout<<"Enter how many Pages: "; cin>>no_of_pages;

    cin.ignore(256,'\n');
    for(int i=1; i<=no_of_pages; i++)
    {
        cout<<"Enter page #"<<i<<": ";
        getline(cin, pages);
        content.push_back(pages);
    }

    ofstream fout("books.txt", ios::out | ios::app);
    fout<<"book: "<<title<<endl;
    while(no_of_pages--)
    {
        fout<<"\t"<<content.front()<<endl;
        content.erase(content.begin());
    }
    fout.close();
}

