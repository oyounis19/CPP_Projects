#include <bits/stdc++.h>
using namespace std;

void cout2d(char a[][10], int n);

void all(char a[][10], int n);

char win(char a[][10], int n);

int main()
{
    ofstream fout("history.txt", ios::out | ios::app);
	ifstream fin("history.txt", ios::in);

    int n, i, j;
    string p1, p2, x;
    cout<<"Enter grid n*n: n = ";
    cin>>n;
    cout<<"Enter 1st Player's Name [Plays with X]: ";
    cin>>p1;
    cout<<"Enter 2nd Player's Name [Plays with O]: ";
    cin>>p2;
    char a[n][10];
    all(a, n);
    for(int l=0; l>-1; l++)
    {
        if(l %2 == 0)
        {
            cout<<p1<<"'s turn. Enter empty location (r , c): ";
            cin>>i>>j; i--; j--;
            if(a[i][j] != '.')
            {
                cout<<"Invalid input. Try again\n";
                l--;
                continue;
            }
            a[i][j] = 'X';
            cout2d(a, n);
        }
        else
        {
            cout<<p2<<"'s turn. Enter empty location (r , c): ";
            cin>>i>>j; i--; j--;
            if(a[i][j] != '.')
            {
                cout<<"Invalid input. Try again\n";
                l--;
                continue;
            }
            a[i][j] = 'O';
            cout2d(a, n);
        }

        if(win(a, n) == 'x')
        {
            cout<<p1<<" Won!!!! :)\n";
            fout<<p1<<endl; fout.close();
            cout<<"\t\t\t\t\t\t\t\t\tHistory:\n";
            while(getline(fin, x))
                cout<<"\t\t\t\t\t\t\t\t\t"<<x<<endl;
            fin.close();
            break;
        }
        else if(win(a, n) == 'o')
        {
            cout<<p2<<" Won!!!! :)";
            fout<<p2<<endl; fout.close();
            cout<<"\t\t\t\t\t\t\t\t\tHistory:\n";
            while(getline(fin, x))
                cout<<"\t\t\t\t\t\t\t\t\t"<<x<<endl;
            fin.close();
            break;
        }
        else if(win(a, n) == 't')
        {
            cout<<"It's a Tie!! :(";
            fout<<"Tie"<<endl; fout.close();
            cout<<"\t\t\t\t\t\t\t\t\tHistory:\n";
            while(getline(fin, x))
                cout<<"\t\t\t\t\t\t\t\t\t"<<x<<endl;
            fin.close();
            break;
        }
    }
    return 0;
}

void cout2d(char a[][10], int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout<<a[i][j]<<"\t";
        cout<<endl<<endl;
    }

}

void all(char a[][10], int n)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            a[i][j] = '.';
}

char win(char a[][10], int n)
{
    int xh, yh, xv, yv, mdx=0, mdy=0, sdx=0, sdy=0, t=0;
    for(int i=0; i<n; i++)
    {
        xh=0; yh=0; xv=0; yv=0;
        for(int j=0; j<n; j++)
        {
            if(a[i][j] == 'X')
                xh++;
            else if(a[i][j] == 'O')
                yh++;
            if(a[j][i] == 'X')
                xv++;
            else if(a[j][i] == 'O')
                yv++;
            if(i == j && a[i][j] == 'X')
                mdx++;
            else if(i == j && a[i][j] == 'O')
                mdy++;
            if(i + j == n-1 && a[i][j] == 'X')
                sdx++;
            else if(i + j == n-1 && a[i][j] == 'O')
                sdy++;
            if(a[i][j] != '.')
                t++;
        }
        if(xh == n)
            return 'x';
        if(yh == n)
            return 'o';

        if(xv == n)
            return 'x';
        if(yv == n)
            return 'o';
    }
    if(mdx == n)
        return 'x';
    if(mdy == n)
        return 'o';

    if(sdx == n)
        return 'x';
    if(sdy == n)
        return 'o';

    if(t == n*n)
        return't';

    return 'n';
}

