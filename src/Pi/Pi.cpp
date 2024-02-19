#include <iostream>
#include "../../include/BigNum.hpp"
#include <ctime>

int main(void){
	long long precision;
	std::cin>>precision;
	clock_t start = clock();
    BigNum my_Pi = Pi(precision);
    clock_t finish = clock();
    std::cout << "Pi calculating Time: "<< (double)(finish-start)/CLOCKS_PER_SEC<< " sec" << std::endl;
    std::cout << my_Pi << std::endl;
	return 0;
}