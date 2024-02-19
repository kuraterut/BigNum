#ifndef HEADER_GUARD_VECTOR_HPP_INCLUDED
#define HEADER_GUARD_VECTOR_HPP_INCLUDED

#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <sstream>

#define base 1000


struct BigNum
{
	// Поля структуры (Длинное число)
	private:
	static const long long BASE = base;

	std::vector<long long> integer;
	std::vector<long long> fractional;
	

	public:
	bool is_negative;
	// Конструкторы
	BigNum() = default;
	BigNum(const char* str);
	BigNum(const std::string strcon);
	BigNum(const long long num);
	BigNum(const long double num);
	BigNum(const double num);
	BigNum(const int num);

 	
	
	// Создание числа
	BigNum bignum_create(const char* strch);
	BigNum& delete_zeros();
	// Арифметика
	BigNum operator+(const BigNum& other);
	BigNum operator-(const BigNum& other);
	BigNum operator*(const BigNum& other);
	BigNum operator/(const BigNum& other);
	BigNum operator%(const BigNum& other);

	// Присваивание
	BigNum& operator=(const BigNum& other);
	BigNum& operator=(const char* str);
	BigNum& operator+=(const BigNum& other);
	BigNum& operator-=(const BigNum& other);
	BigNum& operator*=(const BigNum& other);
	BigNum& operator/=(const BigNum& other);

	// Сравнение
	bool operator==(const BigNum& other);
	bool operator!=(const BigNum& other);
	bool operator>(const BigNum& other);
	bool operator<(const BigNum& other);
	bool operator<=(const BigNum& other);
	bool operator>=(const BigNum& other);
    
    //Настройка точности
    BigNum& set_precision(long long precision);
    std::string to_string() const;

		
	

};

// Литерал с плавающей точкой
BigNum operator ""_bn(const char* lit);
BigNum operator ""_bn(const char* lit, size_t);
// BigNum operator ""_bn(long double num);

// Вывод числа
// std::string operator<<(const BigNum& that);

std::ostream& operator <<(std::ostream& os, const BigNum& num);

// Унарный минус
BigNum operator-(const BigNum& other);

// Число pi 
BigNum Pi(long long precision_pi);



#endif

