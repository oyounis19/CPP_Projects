#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class flights
{
    private:
        string from;
        string to;
        string from_date;
        string to_date;
        short adults, kids, infants, selected_flight;
    public:
        flights();
        flights(string f, string t, string fd, string td, short A, short K, short I, short S);

        int adults_num();
        int kids_num();
        int infants_num();
        short select();

        ~flights();
};

#endif // USER_H
