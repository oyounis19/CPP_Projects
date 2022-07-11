#include <iostream>

using namespace std;

int main ()
{
    int num;
    string name[10000]={"0"};
    int age[10000]={0}, sal[10000]={0}, reading = 0;
    char gen[10000]={0};
    for(int i=0 ;i>-1;i++)
    {
        cout<<"Enter your choice:\n";
        cout<<"1) ADD new employee\n";
        cout<<"2) print all employees\n";
        cout<<"3) Delete by age\n";
        cout<<"4) Update by name\n";
        cin>>num;

        if(num == 1)
        {
            cout<<"Enter name: ";
            cin>>name[i];
            cout<<"Enter age: ";
            cin>>age[i];
            cout<<"Enter salary: ";
            cin>>sal[i];
            cout<<"Enter gender: ";
            cin>>gen[i];
            reading++;
        }
        else if(num == 2)
        {
            for(int j=0; j<25; j++)
                cout<<"*";
            cout<<endl;
            for(int j=0; j<reading; j++)
            {
                if(age[j] != -1)
                    cout<<name[j]<<' '<<age[j]<<' '<<sal[j]<<' '<<gen[j]<<endl;
                else
                    cout<<"employee not found\n";
            }
        }
        else if(num == 3)
        {int start, end;
            cout<<"Enter start and end age\n";
            cin>>start>>end;
            for(int j=0; j<reading; j++)
                if(age[j] >= start && age[j] <= end)
                    age[j] = -1;
            cout<<endl;
        }
        else if(num == 4)
        {
            string x;
            int s;
            cout<<"Enter the name and the salary ";
            cin>>x>>s;
            for(int j=0; j<reading; j++)
            {
                if(name[j] == x)
                {
                    sal[j] = s;
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
