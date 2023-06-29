#include <string>
#include <iostream>

#define CAPACITY 50

typedef struct stack{
    int size_;
    char data_[CAPACITY];
} Stack;

void initialize(Stack* stk){
    stk->size_ = 0;
}

bool isEmpty(Stack* stk){
    return stk->size_ == 0;
}

bool isFull(Stack* stk){
    return stk->size_ == CAPACITY;
}

void push(Stack* stk, char c){
    if (!isFull(stk)){
        stk->data_[stk->size_] = c;
        stk->size_++;
    } else {
        std::cout << "The stack overflow" << std::endl;
    }
}

char pop(Stack* stk){
    char ch;
    if (!isEmpty(stk)){
        stk->size_--;
        ch = stk->data_[stk->size_];
    } else {
        std::cout << "The stack is empty" << std::endl;
        ch = ' ';
    }
    return ch;
}

char top(Stack* stk){
    return stk->data_[stk->size_];
}

bool bracketCheck(const std::string& s){
    Stack stk;
    initialize(&stk);
    char ch;
    bool valid = true;

    for (int i=0; i<s.length() ; i++){
        ch = s[i];
        if (ch == '{' || ch == '[' || ch == '('){
            push(&stk, ch);
        } else if (ch == '}'){
            if (pop(&stk) != '{'){
                valid = false;
            }
        } else if (ch == ']'){
            if (pop(&stk) != '['){
                valid = false;
            }
        } else if (ch == ')'){
            if (pop(&stk) != '('){
                valid = false;
            }
        }
    }

    if (!isEmpty(&stk)){
        valid = false;
    }

    return valid;
}



