#include <iostream>
#include "BigNum.hpp"


int main(){
	BigNum a = "0.32145"_bn;
	BigNum b = "1";
	a*=b;

	std::cout << a << std::endl;
	return 0;
}
