#include <BigNum-version-2.hpp>


using namespace BigNumSpace;

BigNum bignum_create(std::string str){
	BigNum to_return;

	if(str[0] == '-'){
		to_return.is_negative = true;
		str = str.substr(1);
	}
	else{
		to_return.is_negative = false;
	}

	long long found_point = str.find(".");
	long long len = str.length();

	if (found_point == std::string::npos){
		
		for (long long i = len-1; i>=0; i-=9){
			if (i < 9){to_return.integer.push_back(std::stoll(str.substr(0, i)));}
			else{to_return.integer.push_back(std::stoll(str.substr(i-9, 9)));}
		}
	}
	else{
		
		std::string str_integer = str.substr(0, found_point);
		std::string str_fractional = str.substr(found_point+1);

		for (long long i = to_return.SIZE_INT-1; i>=0; i-=9){
			if (i < 9){to_return.integer.push_back(std::stoll(str_integer.substr(0, i)));}
			else{to_return.integer.push_back(std::stoll(str_integer.substr(i-9, 9)));}
		}

		for (long long i = to_return.SIZE_FRACT-1; i>=0; i-=9){
			if (i < 9){to_return.fractional.push_back(std::stoll(str_fractional.substr(0, i)));}
			else{to_return.fractional.push_back(std::stoll(str_fractional.substr(i-9, 9)));}
		}		
	}
}

// Вспомогательные функции
BigNum& delete_zeros(BigNum& that){
	long long size_int = that.integer.size();
	long long size_fract = that.fractional.size();
	auto iter_int = that.integer.cbegin();
	auto iter_fract = that.fractional.cbegin();

	for (long long i = 0; i < size_int; i++){
		if(that.integer[i] == 0){
			that.integer.erase(iter_int);
			iter_int = that.integer.cbegin();
		}
		else{
			break;
		}
	}

	for (long long i = 0; i < size_fract; i++){
		if(that.fractional[i] == 0){
			that.fractional.erase(iter_fract);
			iter_fract = that.fractional.cbegin();
		}
		else{
			break;
		}
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
		else{return false;}
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
BigNum& operator-(const BigNum& that){
	BigNum help = that;
	help.is_negative = !help.is_negative;
	return help;
}




// Операторы сравнения
bool operator==(const BigNum& that, const BigNum& other){
	if (that.integer.size() == other.integer.size() && that.fractional.size() == other.fractional.size() && that.is_negative == other.is_negative){
		
		long long size_int = that.integer.size();
		
		for (long long i = 0; i < size_int; i++){
			if(that.integer[i] != other.integer[i]){return false;}
		}

		long long size_fract = that.fractional.size();
		
		for (long long i = 0; i < size_fract; i++){
			if (that.fractional[i] != other.fractional[i]){return false;}
		}

		return true;
	
	}
	
	return false;
}

bool operator!=(const BigNum& that, const BigNum& other){
	
	if (that == other){return false;}
	else{return true;}

}

bool operator<(const BigNum& that, const BigNum& other){
	if(that.is_negative != other.is_negative){	
		if (that.is_negative == true){return true;}
		else{return false;}
	}
	
	else if(that.integer.size() < other.integer.size() && that.is_negative == true || that.integer.size() > other.integer.size() && that.is_negative == false){return false;}
	else if(that.integer.size() < other.integer.size() && that.is_negative == false || that.integer.size() > other.integer.size() && that.is_negative == true){return true;}

	else{
		long long size_int = that.integer.size();
		if (that.fractional.size() > other.fractional.size()){
			other.fractional.resize(that.fractional.size(), 0);
		}
		else{
			that.fractional.resize(other.fractional.size(), 0);	
		}
		long long size_fract = that.fractional.size();

		if (that.is_negative == true){
			for (long long i = size_int-1; i >= 0; i--){
				if(that.integer[i] > other.integer[i]){return true;}
				else if(that.integer[i] < other.integer[i]){return false;}
			}
		
			for (long long i = size_fract-1; i >= 0; i--){
				if (that.fractional[i] > other.fractional[i]){return true;}
				else if(that.fractional[i] < other.fractional[i]){return false;}	
			}
			return false;
		}

		else{
			for (long long i = size_int-1; i >= 0; i--){
				if(that.integer[i] > other.integer[i]){return false;}
				else if(that.integer[i] < other.integer[i]){return true;}
			}
		
			for (long long i = size_fract-1; i >= 0; i--){
				if (that.fractional[i] > other.fractional[i]){return false;}
				else if(that.fractional[i] < other.fractional[i]){return true;}	
			}
			return false;
		}
	}
}

bool operator<=(const BigNum& that, const BigNum& other){
	if (that == other || that < other){return true;}
	else{return false;}
}

bool operator>(const BigNum& that, const BigNum& other){
	if(that <= other) {return false;}
	else{return true;}
}

bool operator>=(const BigNum& that, const BigNum& other){
	if(that < other){return false;}
	else{return true;}
}


// Присваивание
BigNum& operator=(BigNum& that, const BigNum& other){
	that.SIZE_INT = other.SIZE_INT;
	that.SIZE_FRACT = other.SIZE_FRACT;

	that.is_negative = other.is_negative;
	
	long long size_int = other.integer.size();
	long long size_fract = other.fractional.size();

	that.integer.resize(size_int);
	that.fractional.resize(size_fract);

	for (long long i = 0; i < size_int; i++){
		that.integer[i] = other.integer[i];
	}

	for (long long i = 0; i < size_fract; i++){
		that.fractional[i] = other.fractional[i];
	}

	return that;
}

BigNum& operator=(BigNum& that, const std::string str){
	BigNum p = bignum_create(str);
	that = p;
	return that;
}

BigNum& operator+=(BigNum& that, const BigNum& other){
	long long size_int = max(that.integer.size(), other.integer.size());
	
	that.integer.resize(size_int, 0);
	other.integer.resize(size_int, 0);

	long long size_fract = max(that.fractional.size(), other.fractional.size())

	auto iter_that = that.integer.cbegin();
	auto iter_other = other.integer.cbegin();

	that.integer.insert(iter_that, that.fractional.size() - size_fract, 0);
	other.integer.insert(iter_other, other.fractional.size() - size_fract, 0);

	if (that.is_negative == other.is_negative){
		int need_plus = 0;
		for (long long i = 0; i < size_fract; i++){
			that.fractional[i]+=other.fractional[i];
			if(that.fractional[i] >= that.BASE){
				that.fractional[i]-=that.BASE;
				if(i + 1 != size_fract){
					that.fractional[i+1] += 1;
				}
				else{
					need_plus = 1;
				}
			}
		}
		that.integer[0] += need_plus;

		for (long long i = 0; i < size_int; i++){
			that.integer[i]+=other.integer[i];
			if(that.integer[i] >= that.BASE){
				that.integer[i]-=that.BASE;
				if(i + 1 != size_int){
					that.integer[i+1] += 1;
				}
				else{
					that.integer.push_back(1);
				}
			}
		}
	}

	else{
		if ((that.is_negative == true && (-that) > other) || (that.is_negative == false && (-that) < other)){
			int need_minus = 0;
			for (long long i = 0; i < size_fract; i++){
				that.fractional[i]-=other.fractional[i];
				if(that.fractional[i] < 0){
					that.fractional[i]+=that.BASE;
					if(i + 1 != size_fract){
						that.fractional[i+1] -= 1;
					}
					else{
						need_minus = 1;
					}
				}
			}
			that.integer[0] += need_plus;

			for (long long i = 0; i < size_int; i++){
				that.integer[i]-=other.integer[i];
				if(that.integer[i] < 0){
					that.integer[i]+=that.BASE;
					that.integer[i+1] -= 1;
				}
			}
		}
		
		else if((that.is_negative == true && that <= other) || (that.is_negative == false && (-that) >= other)){
			BigNum help = other;
			int need_minus = 0;
			for (long long i = 0; i < size_fract; i++){
				help.fractional[i]-=that.fractional[i];
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
			help.integer[0] += need_plus;

			for (long long i = 0; i < size_int; i++){
				help.integer[i]-=that.integer[i];
				if(help.integer[i] < 0){
					help.integer[i]+=help.BASE;
					help.integer[i+1] -= 1;
				}
			}
			delete_zeros(help);			
			that = help;
		}

	}
}

BigNum& operator-=(BigNum& that, const BigNum& other){
	that += (-other);
	return that;
}

BigNum& operator*=(BigNum& that, const BigNum& other){
	
	that.is_negative = that.is_negative != other.is_negative;
	
	long long size_other = other.integer.size() + other.fractional.size();
	long long size_that = that.integer.size() + that.fractional.size();
	std::vector<long long> ans;
	ans.resize(size_other+size_that, 0);
	long long ans_size = ans.size();

	std::vector<long long> that_num = that.fractional;
	std::vector<long long> other_num = other.fractional;

	long long size_int_that = that.integer.size();
	long long size_int_other = other.integer.size();

	long long ans_point = that.fractional.size() + other.fractional.size();

	for (long long i = 0; i < size_int_that; i++){
		that_num.push_back(that.integer[i]);
	}
	for (long long i = 0; i < size_int_other; i++){
		other_num.push_back(other.integer[i]);
	}


	for (long long i = 0; i < size_that; i++){
		for(long long j = 0; j < size_other; j++){
			if(i+j == ans_size){
				ans.push_back(that_num[i]*other_num[j]);
				ans_size++;
			}
			else{
				ans[i+j] += that_num[i]*other_num[j]; 
			}
		}
	}

	for (long long i = 0; i < ans_size; i++){
		if(ans[i] >= that.BASE){
			if(i+1 == ans_size){
				ans.push_back(ans[i] / that.BASE);
			}
			else{
				ans[i+1] += ans[i] / that.BASE;
			}
			ans[i] %= that.BASE;
		}
	}

	that.integer.resize(size_ans - ans_point);
	that.fractional.resize(ans_point);
	for (long long i = 0; i < ans_point; i++){
		that.fractional[i] = ans[i];
	}
	for (long long i = ans_point; i < size_ans; i++){
		that.integer[i-ans_point] = ans[i];
	}

	delete_zeros(that);

	return that;
}

BigNum& operator/=(BigNum& that, const BigNum& other){

	that.is_negative = that.is_negative != other.is_negative;
	
	long long size_that = that.integer.size() + that.fractional.size();
	long long size_other = other.integer.size() + other.fractional.size();
	
	std::vector<long long> ans;
	std::vector<long long> that_num = that.fractional;
	std::vector<long long> other_num = other.fractional;
	std::vector<long long> help;


	long long size_int_that = that.integer.size();
	long long size_int_other = other.integer.size();

	long long ans_point = that.fractional.size() - other.fractional.size();

	for (long long i = 0; i < size_int_that; i++){
		that_num.push_back(that.integer[i]);
	}
	for (long long i = 0; i < size_int_other; i++){
		other_num.push_back(other.integer[i]);
	}

	for (long long i = 0; i < size_other; i++){
		that_num.push_back(0);
	}


	long long precision = 0;
	for (long long i = 0; i < size_that + size_other; i++){
		if (i < size_that){
			help.emplace(help.cbegin(), that_num[i]);
			ans.emplace(ans.cbegin(), 0);
			if (help < other_num){continue;}
			else{
				while(! (help < other_num)){
					help-=other_num;
					ans[0]+=1;
					if (is_vec_zero(help) && i+1 == size_that){
						break;
					}
				}
			}
		}
		else{
			precision+=1;
			if (is_vec_zero(help)){break;}
			else{
				help.emplace(help.cbegin(), that_num[i]);
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
	that.integer.clear();
	that.fractional.clear();
	if(ans_point > 0){
		for (long long i = 0; i < ans_point && i < size_ans; i++){
			that.fractional.push_back(ans[i]);
		}
		for(long long i = ans_point; i < size_ans; i++){
			that.integer.push_back(ans[i]);
		}
	}
	else{
		ans_point = -ans_point;
		that.integer.resize(ans_point, 0);
		for (long long i = 0; i < size_ans; i++){
			that.integer.push_back(ans[i]);
		}
	}
	return that;
}


