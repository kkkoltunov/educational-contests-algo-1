#include <iostream>

using namespace std;

void function(int n)
{
    int number;
    cin >> number;

    if (n != 0)
    {
        n--;
        function(n);
    }

    cout << number << " ";
}

int main()
{
    int n;

    cin >> n;
    function(n - 1);
}
