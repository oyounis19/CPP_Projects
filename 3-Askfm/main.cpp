#include <bits/stdc++.h>
using namespace std;

string current_username;

//general purpose
void system();
int generate_id();
void log_menu();
void Q_menu();
//for users
int login_or_signup();
void Login();
void Signup();
void validate_username(string &x);
void List_Users();
//for question
void Ask_Q();
void answer_Q();
void inbox();
void answeredd(int x);
void edit_answer(int id, string x);
string find_ans(int Id);
void add_answer(int Id, string x);
void Feed();
void sent();
void delete_Q();

int main()
{
    system();
    return 0;
}

void system()
{
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

            Q_menu();
            logged_out = 0;
        }
        cout<<"\nEnter number in range 1 - 8: ";
        cin>>n;
        switch(n)
        {
            case 1:
                inbox();
                break;
            case 2:
                sent();
                break;
            case 3:
                answer_Q();
                break;
            case 4:
                delete_Q();
                break;
            case 5:
                Ask_Q();
                break;
            case 6:
                List_Users();
                break;
            case 7:
                Feed();
                break;
            case 8:
                logged_out = 1;
                break;
            default:
                cout<<"Invalid input...";
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
    int n;
    do
    {
        cout<<"Enter number in range 1 - 2: ";
        cin>>n;
        if(1 > n || n > 2)
            cout<<"Invalid input...\n";
    }while(1 > n || n > 2);

    return n;
}

void Login()
{
    string username, pass, users, passes, line;
    ifstream fin("users.txt", ios::in);
    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
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
                found = 1; break;}
        }
        if(!found){
            cout<<"Invalid username or password...[To sign up, type -1]\n";
            fin.clear();
            fin.seekg(0, ios::beg);
        }
    }while(!found);
    fin.close();
    current_username = username;
    cout<<"Welcome, "<<username<<"!!\n";
}

void Signup()
{
    int ID;
    string username, pass, anon;
    cout<<"Email: "; cin>>username;
    cout<<"Username: "; cin>>username;
    cout<<"Password: "; cin>>pass;


    cout<<"Allow anonymous questions? (yes or no)"; cin>>anon;

    while(anon != "yes" && anon != "no"){
        cout<<"Invalid input...\n";
        cout<<"Allow anonymous questions? (yes or no)";
        cin>>anon;
    }
    validate_username(username);
    ID = generate_id();

    ofstream fout("users.txt", ios::out | ios:: app);
    fout<<username<<' '<<pass<<' '<<anon<<' '<<ID<<endl;
    fout.close();
    current_username = username;
    cout<<"Welcome, "<<username<<"!! :)"<<endl;
}

void validate_username(string &username)
{
    bool found = 0;
    string users;
    ifstream fin("users.txt", ios::in);
    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
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

int generate_id()
{
    int ID;
    ifstream idin("ID.txt");
    if(idin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    idin>>ID;
    idin.close();

    ofstream idout("ID.txt");
    idout<<++ID;
    idout.close();

    return ID;
}

void Q_menu()
{
    cout<<"Menu:\n";
    cout<<"1: Received Questions\n";
    cout<<"2: Sent Questions\n";
    cout<<"3: Answer a Question\n";
    cout<<"4: Delete a Question\n";
    cout<<"5: Ask a Question\n";
    cout<<"6: List all users\n";
    cout<<"7: Feed\n";
    cout<<"8: Logout\n";
}

void List_Users()
{
    ifstream fin("users.txt");
    string line, username, empty;
    int id;
    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(fin, line))
    {
        istringstream in(line);
        in>>username>>empty>>empty>>id;
        cout<<"ID: "<<id<<"\t Username: "<<username<<"\n";
    }
    fin.close();
}

void Ask_Q()
{
    string username, line, user, empty, anon;
    bool found=0, AQ = 0;

    cout<<"To whom: ";
    cin>>username;

    ifstream fin("users.txt", ios::in);
    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(fin, line))//checking if user allows AQ.
    {
        istringstream in(line);
        in>>user;
        if(user == username)
        {
            found = 1;
            in>>empty>>anon;
            if(anon == "no")
            {
                cout<<"Note: Anonymous questions aren't allowed for this user\n";
                break;
            }
            else
            {
                char c;
                cout<<"For anonymous question type 'y' else type 'n': ";
                cin>>c;
                if(c =='y')
                    AQ = 1;
                break;
            }
        }
    }
    fin.close();
    if(found == 0){
        cout<<"Invalid username...\n";
        Ask_Q();
        return;
    }

    int n, ids, ID = generate_id();
    string Question;
    char Type;
    bool thats_it = 0, done = 0;
    found = 0;
    cout<<"For new question enter -1 , For thread question enter it's parent ID: ";
    cin>>n;

    if(n == -1)
    {
        ifstream qin("all_in_one.txt", ios::in);
        ofstream qout("all_in_one.txt", ios::out | ios::app);
        cout<<"Enter your Question: ";
        cin.ignore();
        getline(cin, Question);
        qout<<"Q "<<ID<<' '<<AQ<<' '<<current_username<<' '<<username<<' '<<0<<" | "<<Question<<endl;
        qin.close();
        qout.close();
    }
    else
    {
        ifstream qin("all_in_one.txt", ios::in);
        ofstream tout("temp.txt", ios::out | ios::app);
        while(getline(qin, line))
        {
            istringstream In(line);
            In>>Type>>ids;
            if(Type == 'Q' && ids == n)
                found = 1;
        }
        if(found == 0)
        {
            cout<<"Invalid id...\n";
            Ask_Q();
            return;
        }
        else
        {
            cout<<"Enter your Question: ";
            cin.ignore();
            getline(cin, Question);
        }
        qin.clear();
        qin.seekg(0, ios::beg);

        while(getline(qin, line))//Adding thread question
        {
            istringstream In(line);
            In>>Type>>ids;
            if(thats_it && Type == 'Q')
            {
                tout<<"T "<<ID<<' '<<n<<' '<<AQ<<' '<<current_username<<' '<<username<<' '<<0<<" | "<<Question<<"\n"<<line<<endl;
                thats_it = 0;
                done = 1;
                continue;
            }
            if(Type != 'Q' && !thats_it){
                tout<<line<<endl;
                continue;
            }
            if(ids == n)
            {
                thats_it = 1;
                tout<<line<<endl;
            }
            else
                tout<<line<<endl;
        }
        if(thats_it && !done)//if thread question must be added in last line
            tout<<"T "<<ID<<' '<<n<<' '<<AQ<<' '<<current_username<<' '<<username<<' '<<0<<" | "<<Question<<"\n"<<line;

        tout.close();
        qin.close();
        remove("all_in_one.txt");
        rename("temp.txt", "all_in_one.txt");
    }
}

void answer_Q()
{
    string line, username, to_whom, answer;
    int Id, ids, AQ, answered, Parent_ID;
    bool found = 0;
    char Type;


    cout<<"Enter Question id or -1 to cancel: ";
    cin>>Id;

    if(Id == -1)
        return;

    ifstream qin("all_in_one.txt", ios::in);
    if(qin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }

    while(getline(qin, line))//checks if ID found and if it is answered already or NOT.
    {
        istringstream In(line);
        In>>Type>>ids;
        if(Type == 'Q' && Id == ids)
        {
            found = 1;
            In>>AQ>>username>>to_whom>>answered;
            break;
        }
        if(Type == 'T' && Id == ids)
        {
            found = 1;
            In>>Parent_ID>>AQ>>username>>to_whom>>answered;
            break;
        }
    }
    qin.close();

    if (found == 0){
        cout<<"Invalid id...\n";
        answer_Q();
    }

    if(answered == 0)
    {
        cout<<"\nNote: Not answered.\n";
        cout<<"Enter answer: ";
        cin.ignore();
        getline(cin, answer);
        add_answer(Id, answer);
        answeredd(Id);
        cout<<"Done:)\n";
    }
    else
    {
        string answerred = find_ans(Id);
        cout<<"\tAnswer: "<<answerred<<"\n\n";
        cout<<"Note: Already answered, Answer will be updated:)\n";
        cout<<"Edit answer: ";
        cin.ignore();
        getline(cin, answer);
        edit_answer(Id, answer);
        cout<<"Done:)\n";
    }
}

void add_answer(int ID, string answer)
{
    ifstream ain("all_in_one.txt");
    ofstream temp("temp.txt");
    if(ain.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }

    int id, parent_id;
    string line;
    char Type;

    while(getline(ain, line))
    {
        istringstream In(line);
        In>>Type>>id;
        if(Type != 'A' && id == ID)
        {
            if(Type == 'T')
            {
                In>>parent_id;
                temp<<line<<"\n"<<"A "<<ID<<' '<<parent_id<<" | "<<answer<<endl;
            }
            else
                temp<<line<<"\n"<<"A "<<ID<<" | "<<answer<<endl;
            continue;
        }
        temp<<line<<endl;
    }
    ain.close();
    temp.close();
    remove("all_in_one.txt");
    rename("temp.txt", "all_in_one.txt");
}

void answeredd(int ID)
{
    ifstream ain("all_in_one.txt");
    ofstream temp("temp.txt");
    if(ain.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    string line, username, to_whom, question;
    int id, AQ, ans, parent_id;
    char Type, c;

    while(getline(ain, line))
    {
        istringstream In(line);
        In>>Type>>id;

        if(Type == 'Q' && id == ID)
        {
            In>>AQ>>username>>to_whom>>ans>>c;
            getline(In, question);
            temp<<"Q "<<id<<' '<<AQ<<' '<<username<<' '<<to_whom<<' '<<1<<" | "<<question<<endl;
        }
        else if(Type == 'T' && id == ID)
        {
            In>>parent_id>>AQ>>username>>to_whom>>ans>>c;
            getline(In, question);
            temp<<"T "<<id<<' '<<parent_id<<' '<<AQ<<' '<<username<<' '<<to_whom<<' '<<1<<" | "<<question<<endl;
        }
        else
            temp<<line<<endl;
    }
    ain.close();
    temp.close();
    remove("all_in_one.txt");
    rename("temp.txt", "all_in_one.txt");
}

string find_ans(int ID)
{
    ifstream ain("all_in_one.txt");
    char Type, c;
    string line, answer;
    int id;

    if(ain.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(ain, line))
    {
        istringstream In(line);
        In>>Type>>id;
        if(Type == 'A' && id == ID)
        {
            In>>c;
            getline(In, answer);
            ain.close();
            return answer;
        }
    }
    ain.close();
    return "Not found...";
}

void edit_answer(int ID, string answer)
{
    ifstream ain("all_in_one.txt");
    ofstream temp("temp.txt");
    string line;
    char Type;
    int id;

    if(ain.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(ain, line))
    {
        istringstream In(line);
        In>>Type>>id;
        if(Type == 'A' && id == ID)
        {
            temp<<"A "<<id<<" | "<<answer<<endl;
        }
        else
            temp<<line<<endl;
    }
    ain.close();
    temp.close();
    remove("all_in_one.txt");
    rename("temp.txt", "all_in_one.txt");
}

void Feed()
{
    ifstream fin("all_in_one.txt");
    string line, username, to_whom, question, answer;
    int id, parent_id, AQ, answered;
    char Type, c;

    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(fin, line))
    {
        istringstream In(line);
        In>>Type>>id;

        if(Type == 'Q')
        {
            In>>AQ>>username>>to_whom>>answered>>c;
            getline(In, question);

            if(answered == 1)
            {
                if(AQ == 1)
                    cout<<"\t--------------------\nQuestion id("<<id<<") to "<<to_whom<<":";
                else
                    cout<<"\t--------------------\nQuestion id("<<id<<") from "<<username<<" to "<<to_whom<<":";
                cout<<question<<endl;
            }
            continue;
        }
        if(Type == 'A')
        {
            In>>c;
            if(isdigit(c))
                In>>parent_id>>c;

            getline(In, answer);
            cout<<"\tAnswer:"<<answer<<endl;
            continue;
        }
        if(Type == 'T')
        {
            In>>parent_id>>AQ>>username>>to_whom>>answered>>c;
            getline(In, question);

            if(answered == 1)
            {
                if(AQ == 1)
                    cout<<"\tThread to "<<to_whom<<":";
                else
                    cout<<"\tThread from "<<username<<" to "<<to_whom<<":";
                cout<<question<<endl;
            }
        }
    }
    fin.close();
}

void inbox()
{
    ifstream fin("all_in_one.txt");
    string line, username, to_whom, question, answer;
    int id, parent_id, ID, AQ, answered;
    bool empty_inbox = 1;
    char Type, c;

    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(fin, line))
    {
        istringstream In(line);
        In>>Type>>id;

        if(Type == 'Q')
        {

            In>>AQ>>username>>to_whom>>answered>>c;
            getline(In, question);
            if(to_whom == current_username)
            {
                empty_inbox = 0;
                ID = id;
                if(AQ == 1)
                    cout<<"\t--------------------\nQuestion Id ("<<id<<") \n";
                else
                    cout<<"\t--------------------\nQuestions Id ("<<id<<") from "<<username<<endl;

                cout<<"Question:"<<question<<endl;

                if(answered == 0)
                    cout<<"\tNot answered!!\n";

                continue;
            }
        }
        if(Type == 'A')
        {
            In>>c;
            if(isdigit(c))
                In>>parent_id>>c;
            getline(In, answer);
            if(id == ID)
                cout<<"\tAnswer:"<<answer<<endl;
        }
        if(Type == 'T')
        {
            In>>parent_id>>AQ>>username>>to_whom>>answered>>c;
            getline(In, question);

            if(to_whom == current_username)
            {
                ID = id;
                if(AQ == 1)
                    cout<<"\tThread Id("<<id<<") :"<<question<<endl;
                else
                    cout<<"\tThread Id("<<id<<") "<<"from "<<username<<" :"<<question<<endl;

                if(answered == 0)
                    cout<<"\tNot answered!!\n";
            }
        }
    }
    if(empty_inbox)
        cout<<"\nInbox empty!!\n";

    fin.close();
}

void sent()
{
    ifstream fin("all_in_one.txt");
    string line, username, to_whom, question, answer;
    int id, parent_id, ID, AQ, answered;
    bool empty_inbox = 1;
    char Type, c;

    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(fin, line))
    {
        istringstream In(line);
        In>>Type>>id;

        if(Type == 'Q')
        {

            In>>AQ>>username>>to_whom>>answered>>c;
            getline(In, question);
            if(username == current_username)
            {empty_inbox = 0;
                ID = id;
                if(AQ == 1)
                    cout<<"\t--------------------\nQuestion Id ("<<id<<") !AQ to "<<to_whom<<"\n";
                else
                    cout<<"\t--------------------\nQuestions Id ("<<id<<") to "<<to_whom<<endl;

                cout<<"Question:"<<question<<endl;

                if(answered == 0)
                    cout<<"\tNot answered!!\n";

                continue;
            }
        }
        if(Type == 'A')
        {
            In>>c;
            if(isdigit(c))
                In>>parent_id>>c;
            getline(In, answer);
            if(id == ID)
                cout<<"\tAnswer:"<<answer<<endl;
        }
        if(Type == 'T')
        {
            In>>parent_id>>AQ>>username>>to_whom>>answered>>c;
            getline(In, question);

            if(username == current_username)
            {
                ID = id;
                if(AQ == 1)
                    cout<<"\tThread Id("<<id<<") !AQ to "<<to_whom<<" :"<<question<<endl;
                else
                    cout<<"\tThread Id("<<id<<") to "<<to_whom<<" :"<<question<<endl;

                if(answered == 0)
                    cout<<"\tNot answered!!\n";
            }
        }
    }
    if(empty_inbox)
        cout<<"\nYou didn't send any questions yet!!\n";

    fin.close();
}

void delete_Q()
{
    string line, username, to_whom, question, answer;
    int id, parent_id, ID, AQ;
    bool found = 0;
    char Type;

    cout<<"Enter Question id or -1 to cancel: ";
    cin>>ID;
    if(ID == -1) return;

    ifstream fin("all_in_one.txt");
    ofstream temp("temp.txt");

    if(fin.fail())
    {
        cout<<"Failed to open file\n";
        exit(0);
    }
    while(getline(fin, line))
    {
        istringstream In(line);
        In>>Type>>id;
        if(Type == 'Q')
            In>>AQ>>username;
        else if(Type == 'T')
            In>>parent_id>>AQ>>username;
        else if(Type == 'A')
            In>>parent_id;

        if(id == ID || parent_id == ID)
        {
            found = 1;
            parent_id = -1;
            if(username == current_username)//to make sure that the user can delete only his own questions.
                continue;
        }
            temp<<line<<endl;
    }
    if(!found){
        cout<<"Wrong Id...\n";
        delete_Q();
    }
    fin.close();
    temp.close();
    remove("all_in_one.txt");
    rename("temp.txt", "all_in_one.txt");
}

