#pragma once
#include<iostream>
#include "Stack.h"
#include <string>
using namespace std;
int find_plusORminus(string str, int l, int r) {
    Stack BKT;
    int x = -1;
    for (int i = l; i <= r; i++) {
        if (str[i] == '(') {
            BKT.push_back(str[i]);
        }
        else if (str[i] == ')') {
            BKT.pop_back();
        }
        else if (str[i] == '+' || str[i] == '-') {
            if (BKT.is_empty() == false) {
                continue;
            }
            else {
                x = i;
            }
        }
    }
    return x;
}
int find_multiplyORdivide(string str, int l, int r) {
    Stack BKT;
    int x = -1;

    for (int i = l; i <= r; i++) {
        if (str[i] == '(') {
            BKT.push_back(str[i]);
        }
        else if (str[i] == ')') {
            BKT.pop_back();
        }
        else if (str[i] == '*' || str[i] == '/') {
            if (BKT.is_empty() == false) {
                continue;
            }
            else {
                x = i;
            }
        }
    }
    return x;
}
int find_involution(string str, int l, int r) {
    Stack BKT;
    int x = -1;
    for (int i = l; i <= r; i++) {
        if (str[i] == '(') {
            BKT.push_back(str[i]);
        }
        else if (str[i] == ')') {
            BKT.pop_back();
        }
        else if (str[i] == '^') {
            if (BKT.is_empty() == false) {
                continue;
            }
            else {
                x = i;
            }
        }
    }
    return x;
}

bool check_brackets(string str, int l, int r) {
    Stack A;
    for (int i = l + 1; i <= r - 1; i++) {
        if (str[i] == '(') {
            A.push_back('(');
        }
        if (str[i] == ')' && A.is_empty() == false) {
            A.pop_back();
        }
    }
    if (A.is_empty() == true) {
        return false;
    }
    else {
        return true;
    }
}

int find_X(string str, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (str[i] == 'x') {
            return i;
        }
    }
    return -1;
}
bool check_if_letter(char x) {
    for (int i = 0; i <= 25; i++) {
        if (x == 'a' + i) {
            return true;
        }
    }
    return false;
}
string find_function(string str, int l, int r) {
    int i = l;
    bool exists = false;
    for (i; i <= r; i++) {
        if (check_if_letter(str[i]) == true) {
            exists = true;
            break;
        }
    }
    if (exists == false) {
        return "!";
    }
    if (str.substr(i, 3) == "sin") {
        return "cos";
    }
    if (str.substr(i, 3) == "cos") {
        return "-sin";
    }
    if (str.substr(i, 3) == "log") {
        return "1/";
    }
    if (str.substr(i, 2) == "tg") {
        return "1/cos^2";
    }
    if (str.substr(i, 3) == "ctg") {
        return "-1/cos^2";
    }
    if (str.substr(i, 3) == "aco") {
        return "-1/sqrt";
    }
    if (str.substr(i, 3) == "asi") {
        return "1/sqrt";
    }
    else {
        return "!";
    }
}

bool check_if_num(char x) {
    if (x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9') {
        return true;
    }
    return false;
}
string construct_num(string str, int l, int r) {
    int size = 0;
    for (int i = l; i <= r; i++) {
        if (check_if_num(str[i])) {
            size++;
        }
        else {
            break;
        }
    }
    if (size == 0) {
        return "!";
    }
    return str.substr(l, size);
}
string construct_left_num(string str, int r) {
    int size = 0;
    for (int i = r; i >= 0; i--) {
        if (check_if_num(str[i])) {
            size++;
        }
        else {
            break;
        }
    }
    if (size == 0) {
        return "!";
    }
    return str.substr(r - size, size);
}
string create_subexpr(string expr, int l, int r) {
    string str_prev = "";
    if (l > 0) {
        str_prev = expr.substr(0, l);
    }
    string str_post = "";
    if (r < expr.length() - 1) {
        str_post = expr.substr(r + 1, expr.length() - r - 1);
    }
    string l_br = "";
    string r_br = "";
    int pos;
    l = l + 1;
    r = r - 1;
    if (expr[l] == '(' && expr[r] == ')') {
        if (check_brackets(expr, l, r) == false) {
            l_br = "(";
            r_br = ")";
            l = l + 1;
            r = r - 1;
        }
    }
    bool exists = false;
    for (int i = l; i <= r; i++) {
        if (expr[i] == 'x') {
            exists = true;
        }
    }
    if (exists == false) {
        return str_prev + "0" + str_post;
    }

    if ((pos = find_plusORminus(expr, l, r)) != -1) {
        string str1 = l_br + "[" + expr.substr(l, pos - l) + "]";
        string str2 = "[" + expr.substr(pos + 1, r - pos) + "]" + r_br;
        string action;
        if (expr[pos] == '+') {
            action = "+";
        }
        if (expr[pos] == '-') {
            action = "-";
        }
        return str_prev + str1 + action + str2 + str_post;
    }
    else if ((pos = find_multiplyORdivide(expr, l, r)) != -1) {
        if (expr[pos] == '*') {
            string str1 = l_br + "([" + expr.substr(l, pos - l) + "]";
            string str2 = "*" + expr.substr(pos + 1, r - pos) + "+";
            string str3 = "[" + expr.substr(pos + 1, r - pos) + "]";
            string str4 = "*" + expr.substr(l, pos - l) + ")" + r_br;
            return str_prev + str1 + str2 + str3 + str4 + str_post;
        }
        else {
            string str1 = l_br + "([" + expr.substr(l, pos - l) + "]";
            string str2 = "*" + expr.substr(pos + 1, r - pos) + "-";
            string str3 = "[" + expr.substr(pos + 1, r - pos) + "]";
            string str4 = "*" + expr.substr(l, pos - l) + ")";
            string str5 = "/" + expr.substr(pos + 1, r - pos) + "^2" + r_br;
            return str_prev + str1 + str2 + str3 + str4 + str5 + str_post;
        }
    }
    else if ((pos = find_involution(expr, l, r)) != -1) {
        string num;
        if ((num = construct_num(expr, pos + 1, r)) != "!") {
            int pow_int = stoi(num);
            pow_int--;
            string power = to_string(pow_int);
            if (expr[pos - 1] == 'x') {
                return str_prev + l_br + num + 'x' + '^' + power + r_br + str_post;
            }
            if (expr[pos - 1] == ')') {
                return str_prev + l_br + num + expr.substr(l, pos - l) + "^" + power + "*" + "[" + expr.substr(l, pos - l) + "]" + r_br + str_post;
            }
        }
        else {
            string str1 = expr.substr(l, r);
            string str2 = "[log(" + expr.substr(l, pos - l) + ")*(" + expr.substr(pos + 1, r - pos) + ")]";
            return str_prev + l_br + str1 + "*" + str2 + r_br + str_post;
        }
    }
    else if (check_if_letter(expr[l]) == true && expr[l] != 'x') {
        string function = find_function(expr, l, r);
        int it;
        for (it = l + 2; it <= r; it++) {
            if (expr[it] == '(') {
                break;
            }
        }
        if (function == "1/sqrt") {
            return str_prev + l_br + "(" + function + "(1-" + expr.substr(it, r - it + 1) + "^2)" + "*" + "[" + expr.substr(it, r - it + 1) + "]" + r_br + ")" + str_post;
        }
        if (function == "-1/sqrt") {
            return str_prev + l_br + "(" + function + "(1-" + expr.substr(it, r - it + 1) + "^2)" + "*" + "[" + expr.substr(it, r - it + 1) + "]" + r_br + ")" + str_post;
        }
        return str_prev + l_br + "(" + function + expr.substr(it, r - it + 1) + "*" + "[" + expr.substr(it, r - it + 1) + "]" + r_br + ")" + str_post;
    }
    else if ((pos = find_X(expr, l, r)) != -1) {
        return str_prev + "1" + str_post;
    }
    else {
        return str_prev + "0" + str_post;
    }
}
string fuu(string expr) {
    int l = -1;
    int r = -1;
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '[') {
            l = i;
        }
        if (expr[i] == ']') {
            r = i;
            break;
        }
    }
    if (l == -1 || r == -1) {
        return expr;
    }
    else {
        return fuu(create_subexpr(expr, l, r));
    }
}