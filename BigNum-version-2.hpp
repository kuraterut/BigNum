#ifndef HEADER_GUARD_VECTOR_HPP_INCLUDED
#define HEADER_GUARD_VECTOR_HPP_INCLUDED

#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>

#define base 1000*1000*1000


struct BigNum
{
	BigNum() = default;
	BigNum(const char* str);
	BigNum(const std::string strcon);

	static const long long BASE = base;
	
	bool is_negative;
	
	std::vector<long long> integer;
	std::vector<long long> fractional;
	
	// Создание числа
	BigNum bignum_create(const char* strch);


    // Унарный минус
	// BigNum operator-(const BigNum& other);
	
	// Арифметика
	BigNum operator+(const BigNum& other);
	BigNum operator-(const BigNum& other);
	BigNum operator*(const BigNum& other);
	BigNum operator/(const BigNum& other);

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
    
    // Вывод числа
	// std::string operator<<(const BigNum& that);

	// Литерал с плавающей точкой

	// Число pi 


};

	
	

#endif

