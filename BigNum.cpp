#include <BigNum.hpp>

#include <cassert>
#include <cstring>
#include <cmath>

using namespace BigNumSpace;

BigNum BigNumSpace::bignum_create(std::string str){
	BigNum to_return;
	
	if(str[0] == '-'){
		to_return.is_negative = true;
		str = str.substr(1);
	}
	else{
		to_return.is_negative = false;
	}

	for(int i = 0; i < to_return.SIZE; i++){
		to_return.integer[i] = 0;
		to_return.fractional[i] = 0;
	}

	int fount_poind = str.find(".");
	int len = str.length();

	int j = 9;
	if(found_point == std::string::npos){
		to_return.precision = 0;
		for(int i = 0; i < len; i++){
			to_return.integer[j] *= 10;
			to_return.integer[j] += std::stoll(str[i]);
			if(i%9 == 8){
				j--;
			}
		}
	}

	else{
		std::string str_integer = str.substr(0, found_point);
		std::string str_fractional = str.substr(found_point+1);
		
		len = str_integer.length();
		for(int i = 0; i < len; i++){
			to_return.integer[j] *= 10;
			to_return.integer[j] += stoll(str_integer[i]);
			if(i%9 == 8){
				j--;
			}
		}

		j = 9;
		len = str_fractional.length();
		to_return.precision = len;
		for(int i = 0; i < len; i++){
			to_return.fractional[j] *= 10;
			to_return.fractional[j] += stoll(str_fractional[i]);
			if(i%9 == 8){
				j--;
			}
		}
	}
}


BigNum BigNumSpace::operator+(const BigNum& that, const BigNum& other){
	int need_plus = 0;
	BigNum answer;
// Числа одного знака (простое сложение)
	if (that.is_negative == other.is_negative){
		for (int i = 0; i < answer.SIZE; i++){
			answer.fractional[i] = that.fractional[i] + other.fractional[i];
			if(answer.fractional[i] > answer.BASE){
				answer.fractional[i]-=answer.BASE;
				if(i+1!=answer.SIZE){
					answer.fractional[i+1]++;
				}
				else{
					need_plus = 1;
				}
			}
		}
		answer.integer[0] += need_plus;
		for (int i = 0; i < answer.SIZE; i++){
			answer.integer[i] = that.integer[i] + other.integer[i];
			if(answer.integer[i] > answer.BASE){
				answer.integer[i]-=answer.BASE;
				if(i+1!=answer.SIZE){
					answer.integer[i+1]++;
				}
			}
		}
		answer.is_negative = that.is_negative;
	}
// Числа разных знаков (одно вычитаем из другого)
	else{
		bool that_more = false;
		bool flag_changes = false;
		// Сравнение целой части
		for (int i = that.SIZE-1; i >= 0; i--){
			if (that.integer[i] > other.integer[i]){
				that_more = true;
				flag_changes = true;
				break;
			}
			else if(that.integer[i] < other.integer[i]){
				that_more = false;
				flag_changes = true;
				break;
			}
		}
		// Если целая часть равна, сравнение дробной части
		if (flag_changes == false){
			for (int i = that.SIZE-1; i >= 0; i--){
				if (that.fractional[i] > other.fractional[i]){
					that_more = true;
					flag_changes = true;
					break;
				}
			else if(that.fractional[i] < other.fractional[i]){
					that_more = false;
					flag_changes = true;
					break;
				}
			}	
		}

		// Если обе части равны, возврат нулевого числа
		if (flag_changes == false){
			for(int i = 0; i < answer.SIZE; i++){
				answer.integer[i] = 0;
				answer.fractional[i] = 0;
			}
			answer.is_negative = false;
			return answer;
		}


		if (that.is_negative == true && that_more == true){
			answer.is_negative = true;
			int need_minus = 0;
			for (int i = 0; i < answer.SIZE; i++){
				answer.fractional[i] = that.fractional[i] - other.fractional[i];
				if (answer.fractional[i] < 0){
					answer.fractional[i]+=answer.BASE;
					if (i+1 != answer.SIZE){
						answer.fractional[i+1]--;
					}
					else{
						need_minus = 1;
					}
				}
			}
			answer.integer[0] -= need_minus;
			for (int i = 0; i < answer.SIZE; i++){
				answer.integer[i] = that.integer[i] - other.integer[i];
				if (answer.integer[i] < 0){
					answer.integer[i]+=answer.BASE;
					if (i+1 != answer.SIZE){
						answer.integer[i+1]--;
					}
				}
			}
		}
		else if(that.is_negative == false && that_more == true){}
		else if(that.is_negative == true && that_more == false){}
		else if(that.is_negative == false && that_more == false){}
	}
}

