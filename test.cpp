#include <iostream>
#include "BigNum-version-2.hpp"


int main(){
	BigNum a = "12345678910";
	BigNum b = "12345678910";
	b-=a;
	std::cout << b.integer[0] << std::endl;
	return 0;
}
