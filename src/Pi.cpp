#include <iostream>
#include "BigNum.hpp"



BigNum calcPi(long long precision_pi){
	std::vector<BigNum> pow_sixteen;
	BigNum one = "1.0";
	BigNum sixteen = "0.0625";
	BigNum eight = "8.0";
	BigNum four = "4.0";
	BigNum five = "5.0";
	BigNum six = "6.0";
	BigNum two = "2.0";
	BigNum ans = "0.0";

	BigNum sum1, sum2, sum3, sum4;
	pow_sixteen.push_back(one);
	for (long long i = 1; i < precision_pi; i++){
		pow_sixteen.push_back(pow_sixteen[i-1]*sixteen);
	}

	for (long long i = 0; i < precision_pi; i++){
		sum1 = four/((eight*BigNum(i)) + one);
		sum2 = two/((eight*BigNum(i)) + four);
		sum3 = one/((eight*BigNum(i)) + five);
		sum4 = one/((eight*BigNum(i)) + six);
		ans+= pow_sixteen[i]*(sum1-sum2-sum3-sum4);
	}
	return ans;
}

int main(){
	long long precision_pi;
	std::cin >>	precision_pi;
	ans = 
	std::cout << calcPi(precision_pi) << std::endl;
}
