#include "hotels.h"

hotels::hotels()
{
    //ctor
}

hotels::hotels(string fromdate, string todate, string contry, string cety, short A, short K, short selectedflight):
        from_date(fromdate), to_date(todate), country(contry), city(cety), adults(A), kids(K), selected_flight(selectedflight)
{
}

int hotels::adults_num()
{
    return adults;
}

int hotels::kids_num()
{
    return kids;
}

short hotels::select()
{
    return selected_flight;
}

hotels::~hotels()
{
    //dtor
}
