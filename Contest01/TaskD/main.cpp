#include <iostream>
#include <string>

using namespace std;

bool compare(string s1, string s2)
{
    if (s1.length() != s2.length())
    {
        return false;
    }

    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] != s2[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    string str1, str2;

    cin >> str1;
    cin >> str2;

    bool flag = compare(str1, str2);

    if (!flag)
    {
        cout << "no";
    }
    else
    {
        cout << "yes";
    }
}

