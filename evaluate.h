#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifndef EVALUATION_H
#define EVALUATION_H

class Stacknode {

    public:

        double data;
        char cdata;

        Stacknode *next;
    
};

class Stack {

    public:

        Stacknode *top = nullptr;
        int size = 0;

        void push(double _data); // inserts new node at top of stack with selected double
        void cpush(char _data); // inserts new node at top of stack with selected char (infix)

        double isTop(); // finds top of stack and returns its double
        char cisTop(); // finds top of stack and returns its char (infix)

        bool isEmpty(); // returns true if size of stack == 0, else false
        void print(); // follows linked list from top to bottom, printing every node
        void pop(); // de-links top of linked list from stack, and makes next node the top
        int stackSize(); // returns size of stack

};

void Stack::push(double _data) {

  if (top == nullptr) {

    Stacknode *temp = new Stacknode();
    temp->data = _data;
    temp->next = nullptr;
    top = temp;

    ++size;

    return;

  }

  Stacknode *new_top = new Stacknode();
  new_top->data = _data;
  new_top->next = top;
  top = new_top;

  ++size;

  return;

};

void Stack::cpush(char _data) {

  if (top == nullptr) {

    Stacknode *temp = new Stacknode();
    temp->cdata = _data;
    temp->next = nullptr;
    top = temp;

    ++size;

    return;

  }

  Stacknode *new_top = new Stacknode();
  new_top->cdata = _data;
  new_top->next = top;
  top = new_top;

  ++size;

  return;

};


double Stack::isTop() {

  if (top == nullptr) {

    return 0;

  } else {

    return top->data;

  }

};

char Stack::cisTop() {

  if (top == nullptr) {

    return 'x';

  } else {

    return top->cdata;

  }

};


bool Stack::isEmpty() {

  if (size < 1) {

    return true;

  } else {

    return false;

  }

};

void Stack::print() {

  if (top == nullptr) {

    return;

  }

  Stacknode *temp = top;

  while (temp->next != nullptr) {

    std::cout << temp->data << " "; 
    temp = temp->next;

  }

  std::cout << temp->data << std::endl; 

  return;

};

void Stack::pop() {

  Stacknode *temp = top;

  top = top->next;

  free(temp);

  return;

};

int Stack::stackSize() { 
    
    return size; 
    
};


// precedence takes operator symbol and returns its precedence, used in infix function
// postfix returns final product of statement in postfix notation
// prefix returns final product of statement in prefix notation
// infix converts taken infix statement to prefix using Shunting-Yard algorithm, and returns final product of statement

int precedence(char user_operator) {

  if ((user_operator == '+') || (user_operator == '-')) {

    return 2;

  } else if ((user_operator == '*') || (user_operator == '/')) {

    return 3;

  } else if (user_operator == '^') {

    return 4;

  } else {

    return 1;

  }

};

double postfix_statement(std::string input) {

  Stack postfix;

  std::string input_segment;
  std::stringstream blarg(input);

  while (blarg >> input_segment) {

    if (input_segment.length() > 1) {

      double input_pusher = std::stod(input_segment);
      postfix.push(input_pusher);

    } else {

      char stack_additive = input_segment[0];

      if (isdigit(stack_additive)) {

        int stack_int_additive = stack_additive - '0';
        postfix.push(stack_int_additive);

      } else {

        double number_2 = postfix.isTop();
        postfix.pop();

        double number_1 = postfix.isTop();
        postfix.pop();

        double push_number;

        switch (stack_additive) {

            case '+':

                push_number = number_1 + number_2;
                postfix.push(push_number);

                break;

            case '-':

                push_number = number_1 - number_2;
                postfix.push(push_number);

                break;

            case '*':

                push_number = number_1 * number_2;
                postfix.push(push_number);

                break;

            case '/':

                push_number = number_1 / number_2;
                postfix.push(push_number);

                break;

            case '^':

                push_number = pow(number_1, number_2);
                postfix.push(push_number);

                break;

        }

      }

    }

  }

  return postfix.isTop();

};

double prefix_statement(std::string _input) {

  Stack prefix;

  std::string input = _input;
  reverse(input.begin(), input.end());

  std::string input_segment;
  std::stringstream s(input);

  while (s >> input_segment) {

    if (input_segment.length() > 1) {

      reverse(input_segment.begin(), input_segment.end());

      double input_pusher = std::stod(input_segment);
      prefix.push(input_pusher);

    } else {

      char stack_additive = input_segment[0];

      if (isdigit(stack_additive)) {

        int stack_int_additive = stack_additive - '0';
        prefix.push(stack_int_additive);

      } else {

        double number_1 = prefix.isTop();
        prefix.pop();

        double number_2 = prefix.isTop();
        prefix.pop();

        double push_number;

        switch (stack_additive) {

            case '+':

                push_number = number_1 + number_2;
                prefix.push(push_number);

                break;

            case '-':

                push_number = number_1 - number_2;
                prefix.push(push_number);

                break;

            case '*':

                push_number = number_1 * number_2;
                prefix.push(push_number);

                break;

            case '/':

                push_number = number_1 / number_2;
                prefix.push(push_number);

                break;

            case '^':

                push_number = pow(number_1, number_2);
                prefix.push(push_number);

                break;

        }

      }

    }

  }

  return prefix.isTop();

};

double infix_statement(std::string input) {

  Stack infix;

  std::string input_segment;
  std::stringstream s(input);
  std::string infix_string = "";

  while (s >> input_segment) {

    if ((input_segment.length() > 1) || (isdigit(input_segment[0]))) { // input_segment is a number

      infix_string += input_segment;
      infix_string += " ";
      continue;

    } else { // input_segment is an operator or parentheses

      char stack_additive = input_segment[0];
      
      if (stack_additive == ')') {

        while (infix.cisTop() != '(') {

          infix_string += infix.cisTop();
          infix_string += " ";
          infix.pop();
        }

        infix.pop();

      } else if (stack_additive == '(') {

        infix.cpush(stack_additive);

      } else {

        while ( (!(infix.isEmpty()))  &&  (precedence(stack_additive) <= precedence(infix.cisTop())) ) {

          infix_string += infix.cisTop();
          infix_string += " ";
          infix.pop();
          
        }

        infix.cpush(stack_additive);
        
      }

    }

  }

  while ( (infix.cisTop() != 'x') && (!infix.isEmpty()) ) {

    infix_string += infix.cisTop();
    infix_string += " ";
    infix.pop();
    
  }


  return postfix_statement(infix_string);
  
};

#endif
