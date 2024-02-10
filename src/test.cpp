#include <iostream>
#include "BigNum.hpp"


int main(){
	BigNum a = "4.0"_bn;
	BigNum b = "4.0";
	BigNum c = a/b;

	std::cout << c << std::endl;
	return 0;
}
