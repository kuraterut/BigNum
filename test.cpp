#include <iostream>
#include "BigNum.hpp"


int main(){
	BigNum a = "-1.572352";
	// std::cout << "lol" << std::endl;
	BigNum b = "12345654.553362";
	a*=b;
	std::cout << a.is_negative << std::endl;
	std::cout << a.integer[0] << std::endl;
	std::cout << a.fractional[1] << std::endl;
	return 0;
}
