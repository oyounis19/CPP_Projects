#include <bits/stdc++.h>
#include <windows.h>//For sleep();
#include "User.h"//flights Class
#include "hotels.h"//hotels Class
using namespace std;

vector<string> fake_flights = { "300 Airline: Turkish Airlines || Cost: 300$, Departure Date: 10-01-2022, Arrival Date: 10-02-2022",
                                "320 Airline: Turkish Airlines || Cost: 320$, Departure Date: 12-01-2022, Arrival Date: 10-02-2022",
                                "200 Airline: AirCanada Airlines || Cost: 200$, Departure Date: 25-01-2022, Arrival Date: 10-02-2022",
                                "250 Airline: AirCanada Airlines || Cost: 250$, Departure Date: 29-01-2022, Arrival Date: 10-02-2022"};

vector<string> fake_hotels = {  "200 Hotel: Hilton || Room Type: Interior View(6), Price Per night: 200$, From Date: 29-01-2022 to 10-02-2022",
                                "300 Hotel: Hilton || Room Type: City View(3), Price Per night: 300$, From Date: 30-01-2022 to 10-02-2022",
                                "500 Hotel: Hilton || Room Type: Deluxe View(8), Price Per night: 500$, From Date: 29-01-2022 to 10-02-2022",
                                "320 Hotel: Marriott || Room Type: City View(7), Price Per night: 320$, From Date: 29-01-2022 to 10-02-2022",
                                "220 Hotel: Marriott || Room Type: Interior View(4), Price Per night: 220$, From Date: 29-01-2022 to 10-02-2022",
                                "600 Hotel: Marriott || Room Type: Private View(5), Price Per night: 600$, From Date: 29-01-2022 to 10-02-2022"};

vector<flights> FL;
vector<hotels> HL;

string current_username;
bool admin = 0, paid = 0;
int i, ih;//i, ih =0

//User Log
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
//Sys
void new_itinerary();
void add_menu();
void Add_flight();
void Invalid_input();
void Add_Hotel();
void Done();
void List();

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
                    new_itinerary();
                    break;
                case 3:
                    List();
                    break;
                case 4:
                    logged_out = 1;
                    FL.clear();
                    HL.clear();
                    break;
                default:
                    cout<<"Invalid input...";
            }
        }
        else// Admin interface
        {
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
    cout<<"2: Make Itinerary\n";
    cout<<"3: List my Itinerary\n";
    cout<<"4: Logout\n";
    }
    else
    {
    }
}

void View_profile()
{

    if(admin){
        cout<<"ADMIN \n";
        return;
    }

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

void new_itinerary()
{
    int x;
    bool added = 0;
    do
    {
        add_menu();
        cin>>x;
        switch(x)
        {
            case 1:
                Add_flight();
                added = 1;
                break;
            case 2:
                Add_Hotel();
                added = 1;
                break;
            case 3:
                if(!added)
                    cout<<"No reservations were made.\n";
                else
                    Done();
                return;
            case 4:
                i = 0;
                ih = 0;
                FL.clear();
                HL.clear();
                return;
            default:
                Invalid_input();
        }
    }while(x != 4 || x != 3);
}

void add_menu()
{
    cout<<"Menu:\n";
    cout<<"\t1: Add Flight\n";
    cout<<"\t2: Add Hotel\n";
    cout<<"\t3: Done\n";
    cout<<"\t4: Cancel\n";
    cout<<"\nEnter number in range 1 - 4: ";
}

void Add_flight()
{
    string from, to, from_date, to_date, line;
    short adults, kids, infants, cost;

    cout<<"From: "; cin>>from;
    cout<<"To: "; cin>>to;
    cout<<"From date (DD-MM-YY): "; cin>>from_date;
    cout<<"To date (DD-MM-YY): "; cin>>to_date;
    cout<<"Number of (Adults, children, infants): "; cin>>adults>>kids>>infants;

    for(auto l : fake_flights){
        istringstream pp(l);
        pp>>cost;
        getline(pp, line);
        cout<<line<<endl;
        Sleep(200);
    }

    short n;
    cout<<"(-1 to cancel) Enter number in range 1 - "<<fake_flights.size()<<": ";
    cin>>n;

    if(n == -1)
        return;

    if(n > (int)fake_flights.size() || n < 1)
    {
        Invalid_input();
        return;
    }

    if(i == 10)
    {
        cout<<"You have reached the limit of flights";
        return;
    }

//    tempF.set_from_to(from, to);
//    tempF.set_from_to_date(from_date, to_date);
//    tempF.set_family(adults, kids, infants);
//    tempF.select(n-1);
//    FL.push_back(tempF);
    FL.push_back(flights(from, to, from_date, to_date, adults, kids, infants, n-1));
    i++;
}

void Invalid_input()
{
    cout<<"Invalid Input";Sleep(500);
    cout<<".";Sleep(500);
    cout<<".";Sleep(500);
    cout<<".\n";
}

void Add_Hotel()
{
    string from_date, to_date, country, city, line;
    int adults, kids, cost;

    cout<<"From date (DD-MM-YY): "; cin>>from_date;
    cout<<"To date (DD-MM-YY): "; cin>>to_date;
    cout<<"Country: ";cin>>country;
    cout<<"City: ";cin>>city;
    cout<<"Number of Adults, children: "; cin>>adults>>kids;

    for(auto l : fake_hotels){
        istringstream pp(l);
        pp>>cost;
        getline(pp, line);
        cout<<line<<endl;
        Sleep(300);
    }

    short n;
    cout<<"(-1 to cancel) Enter number in range 1 - "<<fake_hotels.size()<<": ";
    cin>>n;

    if(n == -1)
        return;

    if(n > (int)fake_hotels.size() || n < 1)
    {
        Invalid_input();
        return;
    }

    if(ih == 10)
    {
        cout<<"You have reached the limit of Hotels";
        return;
    }

    HL.push_back(hotels(from_date, to_date, country, city, adults, kids, n-1));
    ih++;
}

void Done()
{
    int n;
    cout<<"Select a Payment method:\n";
    cout<<"\t1: [Debit Card] Owner: "<<current_username<<", Card number: 1228-0114-0397\n";
    cout<<"\t2: [Credit Card] Owner: "<<current_username<<", Card number: 2581-2119-3907\n";
    cout<<"Enter number in range 1 - 2: ";
    cin>>n;

    cout<<"Money Withdraw successfully\nReservation Confirmed\nItinerary Reserved\n";

    paid = 1;
}

void List()
{
    if(!paid)
    {
        cout<<"No Itineraries Yet!\n";
        return;
    }
    unsigned flights_no = FL.size();
    unsigned hotels_no = HL.size();
    int total_flight_cost=0, total_hotel_cost=0, fcost;
    string line;
    cout<<"**********************************************************************\n";
    cout<<"Itinerary of "<<flights_no + hotels_no<<" sub-reservation(s)\n";
    if(flights_no != 0)
    {
        cout<<"Airline reservation(s):\n";
        for(int l = 0; l<(int)flights_no; l++)
        {
            istringstream pp(fake_flights[FL[l].select()]);
            pp>>fcost;
            total_flight_cost += fcost;
            getline(pp, line);
            cout<<"\t"<<line<<endl;
            cout<<"\tAdults: "<<FL[l].adults_num()<<", children: "<<FL[l].kids_num()<<", Infants: "<<FL[l].infants_num()<<endl;
            cout<<"\t\t\t\t\t\t---------\n";
        }
        cout<<"Total Cost: "<<total_flight_cost<<"$\n\n";
        cout<<"\t\t\t\t\t----------------------------\n";
    }
    if(hotels_no != 0)
    {
        cout<<"Hotel reservation(s):\n";
        for(int l = 0; l<(int)hotels_no; l++)
        {
            istringstream pp(fake_hotels[HL[l].select()]);
            pp>>fcost;
            total_hotel_cost += fcost;
            getline(pp, line);
            cout<<"\t"<<line<<endl;
            cout<<"\tAdults: "<<HL[l].adults_num()<<", children: "<<HL[l].kids_num()<<endl;
            cout<<"\t\t\t\t\t\t---------\n";
        }
        cout<<"\t\t\t\t\t----------------------------\n";
        cout<<"Total Cost: "<<total_hotel_cost<<"$\n\n";
    }
    cout<<"Total Itinerary Cost: "<<total_flight_cost + total_hotel_cost<<"$"<<endl;
    cout<<"**********************************************************************\n";
}

