#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    int i = 0, state = 0;

    cout << "Enter a string: ";
    cin >> str;

    while (i < str.length())
    {
        switch (state)
        {
        case 0:
            if (str[i] == 'b')
                state = 1;
            else
                state = 4;
            break;
        case 1:
            if (str[i] == 'a')
                state = 2;
            else
                state = 4;
            break;
        case 2:
            if (str[i] == 'a')
                state = 3;
            else
                state = 4;
            break;
        case 3:
            if (str[i] == 'b')
                state = 3;
            else
                state = 4;
            break;
        case 4:
            break; // Invalid state
        }
        i++;
    }

    if (state == 3)
        cout << "The string is accepted" << endl;
    else
        cout << "The string is invalid" << endl;

    return 0;
}