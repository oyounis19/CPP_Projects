#include <iostream>
#include <stdlib.h>
#define MAX_PATIENTS 1000
using namespace std;

struct patient
{
    string name;
    int spec;
    int status;
}n[MAX_PATIENTS];

int freq[21];

void system();
void coutmenu();
void add(int &pn);
void pp(int pn);
void gp(int &pn);

int main()
{
    system();
    return 0;
}

void system()
{
    int n, pn = -1;

    for(int l=0; l>-1; l++)
    {
        coutmenu();
        cin>>n;
        if(n == 1)
        {
            pn++;
            add(pn);
        }
        else if(n == 2)
            pp(pn);
        else if(n == 3)
            gp(pn);
        else if(n == 4)
            exit(0);
    }
}
void coutmenu()
{
    cout<<"Enter your choice:\n";
    cout<<"1) Add new patient\n";
    cout<<"2) Print all patients\n";
    cout<<"3) Get next patient\n";
    cout<<"4) Exit\n";
}
void add(int &pn)
{
    int spec, stat;
    string name;
    cout<<"Enter specialization, name, status: ";
    cin>>spec>>name>>stat;
    if(freq[spec] == 5){
        cout<<"sorry we can't add more patients to specialization\n\n";
        pn--;
        return;
    }
        n[pn].spec = spec;
        n[pn].status = stat;
        n[pn].name = name;

    freq[n[pn].spec]++;
    if(n[pn].status == 1)
    {
        for(int i=pn-1; i>=0; i--)
            n[i+1] = n[i];

        n[0].spec = spec;
        n[0].name = name;
        n[0].status = stat;
    }
    cout<<endl;
}

void pp(int pn)
{
    cout<<"\t\t\t\t*************************************************\n";
    if(pn == -1)
    {
        cout<<"No patients at the moment\n\n";
        return;
    }
    for(int i=0; i<21; i++)
    {
        if(freq[i] != 0)
        {
            cout<<"There are "<<freq[i]<<" patients in specialization "<<i<<endl;
            for(int j=0; j<=pn; j++)
            {
                if(n[j].spec == i)
                {
                    cout<<n[j].name;
                    if(n[j].status == 0)
                        cout<<" regular\n";
                    else
                        cout<<" urgent\n";
                }
            }
        }
    }
    cout<<"\n\n";
}

void gp(int &pn)
{
    if(pn == -1)
    {
        cout<<"No patients at the moment, Dr\n\n";
        return;
    }
    int x;
    cout<<"Enter specialization: ";
    cin>>x;
    for(int i=0; i<=pn; i++)
    {
        if(n[i].spec == x)
        {
            cout<<n[i].name<<" please go with the Dr\n\n";
            freq[n[i].spec]--;
            for(int j=i; j<=pn; j++)
                n[j] = n[j+1];

            pn--;
            return;
        }
    }
    cout<<"No patients at the moment. Have a rest, Dr\n\n";
}
