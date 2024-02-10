#include <iostream>
#include "BigNum.hpp"



BigNum calcPi(long long precision_pi){
	std::vector<BigNum> pow_sixteen;
	BigNum one = "1.0";
	BigNum sixteen = "0.0625";
	BigNum ans = "0";
	BigNum powI1, powI2, powI3, powI4, chisl, znam;
	
	pow_sixteen.push_back(one);
	for (long long i = 1; i < precision_pi; i++){
		pow_sixteen.push_back(pow_sixteen[i-1]*sixteen);
	}
	for (long long i = 0; i < precision_pi; i++){
		powI1 = BigNum(i);
		powI2 = powI1*BigNum(i);
		powI3 = powI2*BigNum(i);
		powI4 = powI3*BigNum(i);
		chisl = "120"_bn*powI2 + "151"_bn*powI1 + "47"_bn;
		znam = "512"_bn*powI4 + "1024"_bn*powI3 + "712"_bn*powI2 + "194"_bn*powI1 + "15"_bn;
		ans+= pow_sixteen[i]*(chisl/znam);
	}
	return ans;
}

int main(){
	long long precision_pi;
	std::cin >>	precision_pi;
	BigNum ans = calcPi(precision_pi);
	ans.fractional.erase(ans.fractional.cbegin(), ans.fractional.cbegin() + ans.fractional.size()-34);
	std::cout << ans << std::endl;
}

