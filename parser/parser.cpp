#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Tokens.h"

int main()
{
	std::string consoleInput;

	std::cout << "Enter the expression: ";
	getline(std::cin, consoleInput);

	Lexer lex(consoleInput);	

	return 0;
}
