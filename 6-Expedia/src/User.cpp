#include "User.h"

flights::flights()
{
    //ctor
}
flights::flights(string f, string t, string fd, string td, short A, short K, short I, short S):
        from(f), to(t), from_date(f), to_date(t), adults(A), kids(K), infants(I), selected_flight(S)
        {
        }
//Getters

int flights::adults_num()
{
    return adults;
}

int flights::kids_num()
{
    return kids;
}

int flights::infants_num()
{
    return infants;
}

short flights::select()
{
    return selected_flight;
}
flights::~flights()
{
    //dtor
}
