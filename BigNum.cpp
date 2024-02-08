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
		for (long long i = len; i>0; i-=9){
			if (i < 9){help.integer.push_back(std::stoll(str.substr(0, i)));}
			else{help.integer.push_back(std::stoll(str.substr(i-9, 9)));}
		}
	}
	else{
		
		std::string str_integer = str.substr(0, found_point);
		std::string str_fractional = str.substr(found_point+1);
		long long len_int = str_integer.length();
		long long len_fract = str_fractional.length();

		for (long long i = len_int; i>=0; i-=9){
			if (i < 9){help.integer.push_back(std::stoll(str_integer.substr(0, i)));}
			else{help.integer.push_back(std::stoll(str_integer.substr(i-9, 9)));}
		}
		if(len_fract%9 != 0){
			help.fractional.push_back(std::stoll(str_fractional.substr(len_fract - len_fract%9, len_fract%9)) * pow(10, 9-len_fract%9));
			len_fract-=len_fract%9;
		}
		for (long long i = len_fract; i>=0; i-=9){
			if (i < 9){
				help.fractional.push_back(std::stoll(str_fractional.substr(0, i)) * pow(10, 9-i));
			}
			else{help.fractional.push_back(std::stoll(str_fractional.substr(i-9, 9)));}
		}		
	}

	return help;
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
		
		for (long long i = len; i>0; i-=9){
			if (i < 9){integer.push_back(std::stoll(str.substr(0, i)));}
			else{integer.push_back(std::stoll(str.substr(i-9, 9)));}
		}
	}
	else{
		
		std::string str_integer = str.substr(0, found_point);
		std::string str_fractional = str.substr(found_point+1);
		long long len_int = str_integer.length();
		long long len_fract = str_fractional.length();

		for (long long i = len_int; i>0; i-=9){
			if (i < 9){integer.push_back(std::stoll(str_integer.substr(0, i)));}
			else{integer.push_back(std::stoll(str_integer.substr(i-9, 9)));}
		}

		if(len_fract%9 != 0){
			help.fractional.push_back(std::stoll(str_fractional.substr(len_fract - len_fract%9, len_fract%9)) * pow(10, 9-len_fract%9));
			len_fract-=len_fract%9;
		}
		
		for (long long i = len_fract; i>0; i-=9){
			if (i < 9){fractional.push_back(std::stoll(str_fractional.substr(0, i)) * pow(10, 9-i));}
			else{fractional.push_back(std::stoll(str_fractional.substr(i-9, 9)));}
		}		
	}
}

BigNum::BigNum(const char* str) : BigNum(std::string(str))
{}

// Вспомогательные функции
BigNum& delete_zeros(BigNum& that){
	long long size_int = that.integer.size();
	long long size_fract = that.fractional.size();
	auto iter_int = that.integer.cbegin();
	auto iter_fract = that.fractional.cbegin();

	for (long long i = 0; i < size_int; i++){
		if(that.integer[i] == 0 && i != size_int-1){
			that.integer.erase(iter_int);
			iter_int = that.integer.cbegin();
		}
		else{
			break;
		}
	}

	for (long long i = 0; i < size_fract; i++){
		if(that.fractional[i] == 0 && i != size_fract - 1){
			that.fractional.erase(iter_fract);
			iter_fract = that.fractional.cbegin();
		}
		else{
			break;
		}
	}
	if ((that.fractional.size() == 0 || that.fractional.size() == 1) && that.integer.size() == 1 && that.integer[0] == 0){
		that.is_negative = false; 
	}

	return that;
}

bool operator<(const std::vector<long long>& that, const std::vector<long long>& other){
	if (that.size() < other.size()){return true;}
	else if(that.size() > other.size()){return false;}
	else{
		long long size = that.size();
		for(long long i = size-1; i >= 0; i++){
			if(that[i] < other[i]){return true;}
			else if(that[i] > other[i]){return false;}
		}
		return false;
	}
}

std::vector<long long>& operator-=(std::vector<long long>& that, const std::vector<long long>& other){
	long long size = that.size();
	for (long long i = 0; i < size; i++){
		that[i]-=other[i];
		if(that[i] < 0){
			that[i] += base;
			that[i+1]-=1;
		}
	}
	return that;
}

bool is_vec_zero(std::vector<long long>& that){
	long long size = that.size();
	for (long long i = 0; i < size; i++){
		if (that[i] != 0){return false;}
	}
	return true;
}



// Унарный минус
BigNum operator-(const BigNum& other){
	BigNum help = other;
	help.is_negative = !help.is_negative;
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
		
		else if(((*this).is_negative == true && (*this) <= cpy_other) || ((*this).is_negative == false && (-(*this)) >= cpy_other)){
			BigNum help = other;
			int need_minus = 0;
			for (long long i = 0; i < size_fract; i++){
				help.fractional[i]-=(*this).fractional[i];
				if(help.fractional[i] < 0){
					help.fractional[i]+=help.BASE;
					if(i + 1 != size_fract){
						help.fractional[i+1] -= 1;
					}
					else{
						need_minus = 1;
					}
				}
			}
			
			help.integer[0] -= need_minus;

			for (long long i = 0; i < size_int; i++){
				help.integer[i]-=(*this).integer[i];
				if(help.integer[i] < 0){
					help.integer[i]+=help.BASE;
					help.integer[i+1] -= 1;
				}
			}

			delete_zeros(help);			
			// std::cout << help.fractional.size() << std::endl;
			(*this) = help;
			
		}

	}
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

	delete_zeros((*this));

	return (*this);
}

BigNum& BigNum::operator/=(const BigNum& other){

	(*this).is_negative = (*this).is_negative != other.is_negative;
	
	long long size_this = (*this).integer.size() + (*this).fractional.size();
	long long size_other = other.integer.size() + other.fractional.size();
	
	std::vector<long long> ans;
	std::vector<long long> this_num = (*this).fractional;
	std::vector<long long> other_num = other.fractional;
	std::vector<long long> help;


	long long size_int_this = (*this).integer.size();
	long long size_int_other = other.integer.size();

	long long ans_point = (*this).fractional.size() - other.fractional.size();

	for (long long i = 0; i < size_int_this; i++){
		this_num.push_back((*this).integer[i]);
	}
	for (long long i = 0; i < size_int_other; i++){
		other_num.push_back(other.integer[i]);
	}

	for (long long i = 0; i < size_other; i++){
		this_num.push_back(0);
	}


	long long precision = 0;
	for (long long i = 0; i < size_this + size_other; i++){
		if (i < size_this){
			help.emplace(help.cbegin(), this_num[i]);
			ans.emplace(ans.cbegin(), 0);
			if (help < other_num){continue;}
			else{
				while(! (help < other_num)){
					help-=other_num;
					ans[0]+=1;
					if (is_vec_zero(help) && i+1 == size_this){
						break;
					}
				}
			}
		}
		else{
			precision+=1;
			if (is_vec_zero(help)){break;}
			else{
				help.emplace(help.cbegin(), this_num[i]);
				ans.emplace(ans.cbegin(), 0);
				if (help < other_num){continue;}
				else{
					while(! (help < other_num)){
						help-=other_num;
						ans[0]+=1;
						if (is_vec_zero(help)){
							break;
						}
					}
				}
			}
		}
	}

	ans_point+=precision;
	long long size_ans = ans.size();
	(*this).integer.clear();
	(*this).fractional.clear();
	if(ans_point > 0){
		for (long long i = 0; i < ans_point && i < size_ans; i++){
			(*this).fractional.push_back(ans[i]);
		}
		for(long long i = ans_point; i < size_ans; i++){
			(*this).integer.push_back(ans[i]);
		}
	}
	else{
		ans_point = -ans_point;
		(*this).integer.resize(ans_point, 0);
		for (long long i = 0; i < size_ans; i++){
			(*this).integer.push_back(ans[i]);
		}
	}
	return (*this);
}


