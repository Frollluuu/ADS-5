// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char op) {
    if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0; // для скобок
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack;
    std::string pst = "";
    
    for (char &c : inf) {
        if (c == ' ') {
            continue; // пропускаем пробелы
        }

        if (isdigit(c)) {
            pst += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (stack.get() != '(') {
                pst += " ";
                pst += stack.pop();
            }
            stack.pop();
        } else {
            pst += " ";
            while (!stack.isEmpty() && priority(stack.get()) >= priority(c)) {
                pst += stack.pop();
            }
            stack.push(c);
        }
    }
    
    while (!stack.isEmpty()) {
        pst += " ";
        pst += stack.pop();
    }
    
    return pst;
}

int eval(std::string post) {
    TStack<int, 100> stack;
    std::istringstream ss(post);
    std::string token;
    
    while (ss >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            int b = stack.pop();
            int a = stack.pop();
            if (token == "+") {
                stack.push(a + b);
            } else if (token == "-") {
                stack.push(a - b);
            } else if (token == "*") {
                stack.push(a * b);
            } else if (token == "/") {
                stack.push(a / b);
            }
        }
    }
    
    return stack.get();
}
