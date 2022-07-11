#ifndef HOTELS_H
#define HOTELS_H
#include <string>
using namespace std;

class hotels
{
    private:
        string from_date, to_date, country, city;
        short adults, kids, selected_flight;
    public:
        hotels();
        hotels(string fromdate, string todate, string contry, string cety, short A, short K, short selectedflight);

        int adults_num();
        int kids_num();
        short select();

        ~hotels();
};

#endif // HOTELS_H
