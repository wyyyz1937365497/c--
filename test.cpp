#include <iostream>
using namespace std;
int main()
{
    string asd = "qwe";
    int i = 0;
    for (char x : asd)
    {
        cout << x << endl;
        cout << (int)x << endl;
        cout << i << endl;
        i++;
    }
}