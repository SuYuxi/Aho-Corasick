//example
#include "AhoCorasick.cpp"
#include <iostream>
#include <string>
int main() {
	Aho_Corasick::AhoCorasick ac;
	ac.build({"hers", "his", "she"});
	ac.addPattern("he");
	ac.buildFailureLink();
	std::string test = "ushers";
	std::cout << "Test string is: " << test << std::endl;
	ac.query(test);
	ac.query("aaaaabababaaaba");
}
