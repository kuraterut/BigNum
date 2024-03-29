#include "BigNum.hpp"




BigNum BigNum::bignum_create(const char* strch){
	BigNum help;
	std::string str = strch;
	if(str[0] == '-'){
		help.is_negative = true;
		str = str.substr(1);
	}
	else{
		help.is_negative = false;
	}

	long long found_point = str.find(".");
	long long len = str.length();

	if (found_point == std::string::npos){
		for (long long i = len; i>0; i-=3){
			if (i < 3){help.integer.push_back(std::stoll(str.substr(0, i)));}
			else{help.integer.push_back(std::stoll(str.substr(i-3, 3)));}
		}
	}
	else{
		
		std::string str_integer = str.substr(0, found_point);
		std::string str_fractional = str.substr(found_point+1);
		long long len_int = str_integer.length();
		long long len_fract = str_fractional.length();

		for (long long i = len_int; i>=0; i-=3){
			if (i < 3){help.integer.push_back(std::stoll(str_integer.substr(0, i)));}
			else{help.integer.push_back(std::stoll(str_integer.substr(i-3, 3)));}
		}
		if(len_fract%3 != 0){
			help.fractional.push_back(std::stoll(str_fractional.substr(len_fract - len_fract%3, len_fract%3)) * pow(10, 3-len_fract%3));
			len_fract-=len_fract%3;
		}
		for (long long i = len_fract; i>=0; i-=3){
			if (i < 3){
				help.fractional.push_back(std::stoll(str_fractional.substr(0, i)) * pow(10, 3-i));
			}
			else{help.fractional.push_back(std::stoll(str_fractional.substr(i-3, 3)));}
		}		
	}

	return help;
}

BigNum& BigNum::set_precision(long long num){
	long long precision = num/3+1;
	long long cur_precision = fractional.size();
	if (precision > cur_precision){
		for (long long i = 0; i < precision-cur_precision; i++){
			(*this).fractional.emplace((*this).fractional.cbegin(), 0);
		}
	}
	else{
		for (long long i = 0; i < cur_precision-precision; i++){
			fractional.erase(fractional.cbegin());
		}
	}
	return *this;
}

BigNum& BigNum::delete_zeros(){
	long long size_int = integer.size();
	long long size_fract = fractional.size();
	auto iter_int = integer.cbegin();
	auto iter_fract = fractional.cbegin();
	
	for (long long i = size_int-1; i >= 0; i--){
		if(integer[i] == 0 && i != 0){
			integer.erase(iter_int+i);
			iter_int = integer.cbegin();
		}
		else{
			break;
		}
	}
	for (long long i = 0; i < size_fract; i++){
		if(fractional[0] == 0 && i != size_fract - 1){
			fractional.erase(iter_fract);
			iter_fract = fractional.cbegin();
		}
		else{
			break;
		}
	}
	if ((fractional.size() == 0 || (fractional.size() == 1 && fractional[0] == 0)) && integer.size() == 1 && integer[0] == 0){
		is_negative = false; 
	}

	return *this;
}



BigNum::BigNum(const std::string strcon){
	std::string str = strcon;
	if(str[0] == '-'){
		is_negative = true;
		str = str.substr(1);
	}
	else{
		is_negative = false;
	}

	long long found_point = str.find(".");
	long long len = str.length();

	if (found_point == std::string::npos){
		
		for (long long i = len; i>0; i-=3){
			if (i < 3){integer.push_back(std::stoll(str.substr(0, i)));}
			else{integer.push_back(std::stoll(str.substr(i-3, 3)));}
		}
	}
	else{
		
		std::string str_integer = str.substr(0, found_point);
		std::string str_fractional = str.substr(found_point+1);
		long long len_int = str_integer.length();
		long long len_fract = str_fractional.length();

		for (long long i = len_int; i>0; i-=3){
			if (i < 3){integer.push_back(std::stoll(str_integer.substr(0, i)));}
			else{integer.push_back(std::stoll(str_integer.substr(i-3, 3)));}
		}

		if(len_fract%3 != 0){
			fractional.push_back(std::stoll(str_fractional.substr(len_fract - len_fract%3, len_fract%3)) * pow(10, 3-len_fract%3));
			len_fract-=len_fract%3;
		}
		
		for (long long i = len_fract; i>0; i-=3){
			if (i < 3){fractional.push_back(std::stoll(str_fractional.substr(0, i)) * pow(10, 3-i));}
			else{fractional.push_back(std::stoll(str_fractional.substr(i-3, 3)));}
		}		
	}
	(*this).delete_zeros();
}

BigNum::BigNum(const char* str) : BigNum(std::string(str)){}
BigNum::BigNum(const long long num) : BigNum(std::to_string(num)){}
BigNum::BigNum(const long double num) : BigNum(std::to_string(num)) {}
BigNum::BigNum(const double num) : BigNum(std::to_string(num)) {}
BigNum::BigNum(const int num) : BigNum(std::to_string(num)) {}

// Создание литерала с плавающей точкой

BigNum operator ""_bn(const char* lit)
{
    std::string str = lit;
    BigNum p = str;
    return p;
}


BigNum operator ""_bn(const char* lit, size_t)
{
    std::string str = lit;
    BigNum p = str;
    return p;
}
// BigNum operator ""_bn(long double num)
// {
//     std::string str = std::__cxx11::to_string(num); 
//     BigNum p = str;
//     return p;
// }

// Вывод числа

std::ostream& operator <<(std::ostream& os, const BigNum& num)
{
    os << num.to_string();
    return os;
}


// Вспомогательные функции
std::string BigNum::to_string() const
{
    std::ostringstream os;
    if (is_negative){os << "-";}

    long long size_fract = fractional.size();
    long long size_int = integer.size();

    for (long long i = size_int-1; i >= 0; i--){
		if(i != size_int-1 && integer[i] < 10){
			os << "00";
			os << std::to_string(integer[i]);	
		}
		else if(i != size_int-1 && integer[i] < 100){
			os << "0";
			os << std::to_string(integer[i]);
		}    	
		else{
    		os << std::to_string(integer[i]);	
    	}
    }
    if(size_fract != 0){
    	os << ".";
    }

    for (long long i = size_fract-1; i >= 0; i--){
    	if(fractional[i] < 10){
			os << "00";
			os << std::to_string(fractional[i]);	
		}
		else if(fractional[i] < 100){
			os << "0";
			os << std::to_string(fractional[i]);
		}    	
		else{
    		os << std::to_string(fractional[i]);	
    	}	
    }

    return os.str();
}


// Унарный минус
BigNum operator-(const BigNum& other){
	BigNum help = other;
	help.is_negative = !other.is_negative;
	return help;
}




// Операторы сравнения
bool BigNum::operator==(const BigNum& other){
	if ((*this).integer.size() == other.integer.size() && (*this).fractional.size() == other.fractional.size() && (*this).is_negative == other.is_negative){
		
		long long size_int = (*this).integer.size();
		
		for (long long i = 0; i < size_int; i++){
			if((*this).integer[i] != other.integer[i]){return false;}
		}

		long long size_fract = (*this).fractional.size();
		
		for (long long i = 0; i < size_fract; i++){
			if ((*this).fractional[i] != other.fractional[i]){return false;}
		}

		return true;
	
	}
	
	return false;
}

bool BigNum::operator!=(const BigNum& other){
	
	if ((*this) == other){return false;}
	else{return true;}

}

bool BigNum::operator<(const BigNum& other){
	BigNum cpy_other = other;

	if((*this).is_negative != other.is_negative){	
		if ((*this).is_negative == true){return true;}
		else{return false;}
	}
	
	else if((*this).integer.size() < other.integer.size() && (*this).is_negative == true || (*this).integer.size() > other.integer.size() && (*this).is_negative == false){return false;}
	else if((*this).integer.size() < other.integer.size() && (*this).is_negative == false || (*this).integer.size() > other.integer.size() && (*this).is_negative == true){return true;}

	else{
		long long size_int = (*this).integer.size();
		if ((*this).fractional.size() > other.fractional.size()){
			cpy_other.fractional.resize(fractional.size(), 0);
		}
		else{
			(*this).fractional.resize(other.fractional.size(), 0);	
		}
		long long size_fract = (*this).fractional.size();

		if ((*this).is_negative == true){
			for (long long i = size_int-1; i >= 0; i--){
				if((*this).integer[i] > cpy_other.integer[i]){return true;}
				else if((*this).integer[i] < cpy_other.integer[i]){return false;}
			}
		
			for (long long i = size_fract-1; i >= 0; i--){
				if ((*this).fractional[i] > cpy_other.fractional[i]){return true;}
				else if((*this).fractional[i] < cpy_other.fractional[i]){return false;}	
			}
			return false;
		}

		else{
			for (long long i = size_int-1; i >= 0; i--){
				if((*this).integer[i] > cpy_other.integer[i]){return false;}
				else if((*this).integer[i] < cpy_other.integer[i]){return true;}
			}
		
			for (long long i = size_fract-1; i >= 0; i--){
				if ((*this).fractional[i] > cpy_other.fractional[i]){return false;}
				else if((*this).fractional[i] < cpy_other.fractional[i]){return true;}	
			}
			return false;
		}
	}
}

bool BigNum::operator<=(const BigNum& other){
	if ((*this) == other || (*this) < other){return true;}
	else{return false;}
}

bool BigNum::operator>(const BigNum& other){
	if((*this) <= other) {return false;}
	else{return true;}
}

bool BigNum::operator>=(const BigNum& other){
	if((*this) < other){return false;}
	else{return true;}
}


// Присваивание
BigNum& BigNum::operator=(const BigNum& other){
	(*this).is_negative = other.is_negative;
	long long size_int = other.integer.size();
	long long size_fract = other.fractional.size();

	(*this).integer.resize(size_int);
	(*this).fractional.resize(size_fract);

	for (long long i = 0; i < size_int; i++){
		(*this).integer[i] = other.integer[i];
	}

	for (long long i = 0; i < size_fract; i++){
		(*this).fractional[i] = other.fractional[i];
	}

	return (*this);
}

BigNum& BigNum::operator=(const char* str){
	(*this) = bignum_create(str);
	return (*this);
}

BigNum& BigNum::operator+=(const BigNum& other){
	long long size_int = std::max((*this).integer.size(), other.integer.size());
	
	BigNum cpy_other = other;

	integer.resize(size_int, 0);
	cpy_other.integer.resize(size_int, 0);

	
	long long size_fract = std::max((*this).fractional.size(), cpy_other.fractional.size());


	fractional.insert(fractional.cbegin(), abs(fractional.size() - size_fract), 0);
	
	cpy_other.fractional.insert(cpy_other.fractional.cbegin(), abs(cpy_other.fractional.size() - size_fract), 0);

	if ((*this).is_negative == cpy_other.is_negative){
		int need_plus = 0;
		for (long long i = 0; i < size_fract; i++){
			(*this).fractional[i]+=cpy_other.fractional[i];
			if((*this).fractional[i] >= (*this).BASE){
				(*this).fractional[i]-=(*this).BASE;
				if(i + 1 != size_fract){
					(*this).fractional[i+1] += 1;
				}
				else{
					need_plus = 1;
				}
			}
		}

		(*this).integer[0] += need_plus;

		for (long long i = 0; i < size_int; i++){
			(*this).integer[i]+=cpy_other.integer[i];
			if((*this).integer[i] >= (*this).BASE){
				(*this).integer[i]-=(*this).BASE;
				if(i + 1 != size_int){
					(*this).integer[i+1] += 1;
				}
				else{
					(*this).integer.push_back(1);
				}
			}
		}

	}

	else{
		if (((*this).is_negative == true && (-(*this)) > cpy_other) || ((*this).is_negative == false && (-(*this)) < cpy_other)){
			int need_minus = 0;
			for (long long i = 0; i < size_fract; i++){
				(*this).fractional[i]-=cpy_other.fractional[i];
				if((*this).fractional[i] < 0){
					(*this).fractional[i]+=(*this).BASE;
					if(i + 1 != size_fract){
						(*this).fractional[i+1] -= 1;
					}
					else{
						need_minus = 1;
					}
				}
			}
			(*this).integer[0] -= need_minus;

			for (long long i = 0; i < size_int; i++){
				(*this).integer[i]-=cpy_other.integer[i];
				if((*this).integer[i] < 0){
					(*this).integer[i]+=(*this).BASE;
					(*this).integer[i+1] -= 1;
				}
			}
		}
		
		else if(((*this).is_negative == true && (-(*this)) <= cpy_other) || ((*this).is_negative == false && (-(*this)) >= cpy_other)){
			int need_minus = 0;

			for (long long i = 0; i < size_fract; i++){
				cpy_other.fractional[i]-=(*this).fractional[i];
				if(cpy_other.fractional[i] < 0){
					cpy_other.fractional[i]+=cpy_other.BASE;
					if(i + 1 != size_fract){
						cpy_other.fractional[i+1] -= 1;
					}
					else{
						need_minus = 1;
					}
				}
			}
			
			cpy_other.integer[0] -= need_minus;

			for (long long i = 0; i < size_int; i++){
				cpy_other.integer[i]-=(*this).integer[i];
				if(cpy_other.integer[i] < 0){
					cpy_other.integer[i]+=cpy_other.BASE;
					cpy_other.integer[i+1] -= 1;
				}
			}
			
			(*this) = cpy_other;
			
		}

	}
	(*this).delete_zeros();
	return (*this);
}

BigNum& BigNum::operator-=(const BigNum& other){
	BigNum cpy_other = -other;
	(*this) += cpy_other;
	return (*this);
}

BigNum& BigNum::operator*=(const BigNum& other){
	
	(*this).is_negative = (*this).is_negative != other.is_negative;
	
	long long size_other = other.integer.size() + other.fractional.size();
	long long size_this = (*this).integer.size() + (*this).fractional.size();
	std::vector<long long> ans;
	ans.resize(size_other+size_this, 0);
	long long ans_size = ans.size();

	std::vector<long long> this_num = (*this).fractional;
	std::vector<long long> other_num = other.fractional;

	long long size_int_this = (*this).integer.size();
	long long size_int_other = other.integer.size();

	long long ans_point = (*this).fractional.size() + other.fractional.size();

	for (long long i = 0; i < size_int_this; i++){
		this_num.push_back((*this).integer[i]);
	}
	for (long long i = 0; i < size_int_other; i++){
		other_num.push_back(other.integer[i]);
	}


	for (long long i = 0; i < size_this; i++){
		for(long long j = 0; j < size_other; j++){
			if(i+j == ans_size){
				ans.push_back(this_num[i]*other_num[j]);
				ans_size++;
			}
			else{
				ans[i+j] += this_num[i]*other_num[j]; 
			}
		}
	}

	for (long long i = 0; i < ans_size; i++){
		if(ans[i] >= (*this).BASE){
			if(i+1 == ans_size){
				ans.push_back(ans[i] / (*this).BASE);
			}
			else{
				ans[i+1] += ans[i] / (*this).BASE;
			}
			ans[i] %= (*this).BASE;
		}
	}

	(*this).integer.resize(ans_size - ans_point);
	(*this).fractional.resize(ans_point);
	for (long long i = 0; i < ans_point; i++){
		(*this).fractional[i] = ans[i];
	}
	for (long long i = ans_point; i < ans_size; i++){
		(*this).integer[i-ans_point] = ans[i];
	}

	(*this).delete_zeros();

	return (*this);
}

bool is_zero(const BigNum& that){
	BigNum zero1 = "0";
	BigNum zero2 = "0.0";
	if (zero1 == that || zero2 == that){return true;}
	else{return false;}
}

BigNum& BigNum::operator/=(const BigNum& other){
	if(BigNum(0) != other && BigNum(0.0) != other){
		
	(*this).is_negative = (*this).is_negative != other.is_negative;
	
	// for (long long i = 0; i < 35; i++){
	// 	(*this).fractional.emplace((*this).fractional.cbegin(), 0);
	// }

	long long size_this = (*this).integer.size() + (*this).fractional.size();
	long long size_other = other.integer.size() + other.fractional.size();

	// std::vector<long long> ans;
	// std::vector<long long> help;
	BigNum ans, help, other_num;
	ans.is_negative = false;
	help.is_negative = false;
	other_num.is_negative = false;
	std::vector<long long> this_num = (*this).fractional;
	other_num.integer = other.fractional;



	long long size_int_this = (*this).integer.size();
	long long size_int_other = other.integer.size();

	long long ans_point = (*this).fractional.size() - other.fractional.size();

	for (long long i = 0; i < size_int_this; i++){
		this_num.push_back((*this).integer[i]);
	}
	for (long long i = 0; i < size_int_other; i++){
		other_num.integer.push_back(other.integer[i]);
	}
	other_num.delete_zeros();

	for (long long i = 0; i < size_other; i++){
		this_num.emplace(this_num.cbegin(), 0);
	}

	long long precision = 0;


	for (long long i = 0; i < size_this + size_other; i++){
		if (i < size_this){
			help.integer.emplace(help.integer.cbegin(), this_num[size_this+size_other-i-1]);
			help.delete_zeros();
			ans.integer.emplace(ans.integer.cbegin(), 0);
			if (help < other_num){continue;}
			else{
				while((help < other_num) == 0){
					help-=other_num;
					ans.integer[0]+=1;
					if (is_zero(help) && i+1 == size_this){
						break;
					}
				}
			}
		}
		else{
			if (is_zero(help)){break;}
			else{
				precision+=1;
				help.integer.emplace(help.integer.cbegin(), this_num[size_this+size_other-i-1]);
				help.delete_zeros();
				ans.integer.emplace(ans.integer.cbegin(), 0);
				if (help < other_num){continue;}
				else{
					while((help < other_num) == 0){
						help-=other_num;
						ans.integer[0]+=1;				
						if (is_zero(help)){
							break;
						}
					}
				}
			}
		}
	}
	

	ans_point+=precision;
	long long size_ans = ans.integer.size();
	(*this).integer.clear();
	(*this).fractional.clear();
	if(ans_point > 0){
		for (long long i = 0; i < ans_point && i < size_ans; i++){
			(*this).fractional.push_back(ans.integer[i]);
		}
		for(long long i = ans_point; i < size_ans; i++){
			(*this).integer.push_back(ans.integer[i]);
		}
	}
	else{
		ans_point = -ans_point;
		(*this).integer.resize(ans_point, 0);
		for (long long i = 0; i < size_ans; i++){
			(*this).integer.push_back(ans.integer[i]);
		}
	}
	(*this).delete_zeros();

	return (*this);
	}
	throw "Division by zero";
}

// Арифметика

BigNum BigNum::operator+(const BigNum& other){
	BigNum p = (*this);
	p+=other;
	return p;
}

BigNum BigNum::operator-(const BigNum& other){
	BigNum p = (*this);
	p-=other;
	return p;
}

BigNum BigNum::operator*(const BigNum& other){
	BigNum p = (*this);
	p*=other;
	return p;
}

BigNum BigNum::operator/(const BigNum& other){
	BigNum p = (*this);
	p/=other;
	return p;
}

// Число Пи
BigNum Pi(long long precision_pi){
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
		chisl.set_precision(precision_pi);
		ans+= pow_sixteen[i]*(chisl/znam);
	}
	ans.set_precision(precision_pi);
	// ans.fractional.erase(ans.fractional.cbegin(), ans.fractional.cbegin() + ans.fractional.size()-precision_pi/3-1);
	return ans;
}