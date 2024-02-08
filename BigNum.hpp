#ifndef HEADER_GUARD_VECTOR_HPP_INCLUDED
#define HEADER_GUARD_VECTOR_HPP_INCLUDED

#include <cstdlib>

namespace BigNumSpace{
	struct BigNum{
		static const long long BASE = 1000*1000*1000; // числа в массиве не больше 10^9
		static const long long SIZE = 10; // числа максимум 10^90
		
		bool is_negative; // наличие знака "-"

		int precision;

		long long integer[SIZE]; // массив из чисел до запятой по базе BASE
		long long fractional[SIZE]; // массив из чисел после запятой по базе BASE

	}
	
	// Созадние числа
	BigNum bignum_create(std::string str);
	
	// Арифметика
	BigNum operator+(const BigNum& that, const BigNum& other);
	BigNum operator-(const BigNum& that, const BigNum& other);
	BigNum operator*(const BigNum& that, const BigNum& other);
	BigNum operator/(const BigNum& that, const BigNum& other);

	// Присваивание
	BigNum& operator=(BigNum& that, const BigNum& other);
	BigNum& operator+=(BigNum& that, const BigNum& other);
	BigNum& operator-=(BigNum& that, const BigNum& other);
	BigNum& operator*=(BigNum& that, const BigNum& other);
	BigNum& operator/=(BigNum& that, const BigNum& other);

	// Сравнение
	bool operator==(const BigNum& that, const BigNum& other);
	bool operator!=(const BigNum& that, const BigNum& other);
	bool operator>(const BigNum& that, const BigNum& other);
	bool operator<(const BigNum& that, const BigNum& other);
	bool operator<=(const BigNum& that, const BigNum& other);
	bool operator>=(const BigNum& that, const BigNum& other);
}