#include <iostream>
#include <cstring>
using namespace std;

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
string act;

void check();

int main() {
    cout << "GRAMMAR:";
    cout << "\nE -> E + E\nE -> E / E";
    cout << "\nE -> E * E\nE -> a / b";
    cout << "\nEnter the input symbol:\t";
    cin >> ip_sym;
    
    cout << "\n\t Stack implementation table\n";
    cout << "\nStack\t\t Input symbol\t\t Action";
    cout << "\n______\t\t ____________\t\t ______\n";
    cout << "\n $\t\t" << ip_sym << "$\t\t\t--";
    
    act = "Shift ";
    act += ip_sym[ip_ptr];
    len = strlen(ip_sym);
    
    for (i = 0; i <= len - 1; i++) {
        stack[st_ptr] = ip_sym[ip_ptr];
        stack[st_ptr + 1] = '\0';
        ip_sym[ip_ptr] = ' ';
        ip_ptr++;
        
        cout << "\n $" << stack << "\t\t" << ip_sym << "$\t\t\t" << act;
        act = "shift ";
        act += ip_sym[ip_ptr];
        
        check();
        st_ptr++;
    }
    return 0;
}

void check() {
    int flag = 0;
    string temp2(1, stack[st_ptr]);
    
    if (temp2 == "a" || temp2 == "b") {
        stack[st_ptr] = 'E';
        cout << "\n $" << stack << "\t\t" << ip_sym << "$\t\t\tE->" << temp2;
        flag = 1;
    }
    
    if (temp2 == "+" || temp2 == "*" || temp2 == "/") {
        flag = 1;
    }
    
    string stack_str(stack);
    if (stack_str == "E+E" || stack_str == "E/E" || stack_str == "E*E") {
        stack[0] = 'E';
        stack[1] = '\0';
        st_ptr = 0;
        
        cout << "\n $" << stack << "\t\t" << ip_sym << "$\t\t\tE->" << stack_str;
        flag = 1;
    }
    
    if (stack_str == "E" && ip_ptr == len) {
        cout << "\n $" << stack << "\t\t" << ip_sym << "$\t\t\tACCEPT";
        return;
    }
    
    if (flag == 0) {
        cout << "\n" << stack << "\t\t\t" << ip_sym << "\t\t REJECT";
        return;
    }
}