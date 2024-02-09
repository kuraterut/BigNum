#include <iostream>
#include "BigNum.hpp"


int main(){
	BigNum a = "4.32145"_bn;
	BigNum b = "461.2533";
	a*=b;

	std::cout << a << std::endl;
	return 0;
}
