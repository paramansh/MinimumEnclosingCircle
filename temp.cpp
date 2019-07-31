#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector <int> a(10000);
    for (int i = 0; i < 100000; i++)
    {
        int temp =a[i % 10000];
        if (i % 10000 == 0)
        {
            cout << i << endl;
        }
    }
}
