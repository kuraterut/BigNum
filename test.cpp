#include <iostream>
#include "BigNum-version-2.hpp"


int main(){
	BigNum a = "1.57";
	BigNum b = "12345654.553";
	b-=a;
	std::cout << b.integer[0] << std::endl;
	std::cout << b.fractional[0] << std::endl;
	return 0;
}
