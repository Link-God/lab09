#include <string>
#include <fstream>
#include <iostream>

//Prints text to standard output stream
void print(const std::string& text, std::ostream& out = std::cout);

//Prints text to specified file
void print(const std::string& text, std::ofstream& out);
