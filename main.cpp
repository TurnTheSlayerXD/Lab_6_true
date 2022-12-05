#include <iostream>
#include "Stack.h"
#include "Functions.h"
#include<string>
using namespace std;

int main() {
    string str;
    getline(cin, str);
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str = "[" + str + "]";
    string res = fuu(str);
    for (int i = 0; i < res.length(); i++) {
        if (res[i] == '+' || res[i] == '-' || res[i] == '*' || res[i] == '/' || res[i] == '^') {
            cout << " " << res[i] << " ";
        }
        else {
            cout << res[i];
        }
    }
    return 0;
}