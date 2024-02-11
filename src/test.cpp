#include <iostream>
#include "BigNum.hpp"
#include <ctime>

int main(){
	clock_t start = clock();
	BigNum a = Pi(100);
	clock_t end = clock();
	std::cout << a << std::endl;
	double seconds = (double) (end - start) / CLOCKS_PER_SEC;
	std::cout << seconds << std::endl;

}

