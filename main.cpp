#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "ArgumentManager.h"
#include "evaluate.h"

// :D

int main() {

    // postfix takes statement and uses stack to return double value

    // prefix takes statement and uses stack to return double value

    // infix takes statement, uses Shunting-Yard algorithm to convert
    // to postfix, and calls postfix function to return double value

    std::ofstream ofs("output.txt");
    std::ifstream ifs("input.txt"); 

    int determinant = 0;
    std::string input_string;
    
    while (std::getline(ifs, input_string)) {

        // 1=prefix, 2=postfix, 3=infix
        bool prefix_find = input_string.find("prefix") != std::string::npos;
        bool postfix_find = input_string.find("postfix") != std::string::npos;
        bool infix_find = input_string.find("infix") != std::string::npos;

        if (determinant == 1) {

            double output = prefix_statement(input_string);
            ofs << std::fixed << std::setprecision(2) << output << std::endl;
            determinant = 0;

        }
        
        if (determinant == 2) {

            double output = postfix_statement(input_string);
            ofs << std::fixed << std::setprecision(2) << output << std::endl;
            determinant = 0;

        }
        
        if (determinant == 3) {
            
            double output = infix_statement(input_string);
            ofs << std::fixed << std::setprecision(2) << output << std::endl;
            determinant = 0;

        }


        if (prefix_find) {

            determinant = 1;

        }

        if (postfix_find) {

            determinant = 2;

        }

        if (infix_find) {

            determinant = 3;

        }

    }

    ifs.close();
    ofs.close();

    return 0;

};