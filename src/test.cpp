#include <iostream>
#include "BigNum.hpp"


int main(){
	BigNum a = "4572.7234"_bn;
	BigNum b = "161124512.51";
	BigNum c = b*a;

	std::cout << c << std::endl;
	return 0;
}
