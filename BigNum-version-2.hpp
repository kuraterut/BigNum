#ifndef HEADER_GUARD_VECTOR_HPP_INCLUDED
#define HEADER_GUARD_VECTOR_HPP_INCLUDED

#include <cstdlib>
namespace BigNumSpace{
	struct BigNum
	{
		static const long long BASE = 1000*1000*1000;

		bool is_negative;

		std::vector<long long> integer;
		std::vector<long long> fractional;

	};
	
	// Созадние числа
	BigNum bignum_create(std::string str);

    // Унарный минус
	BigNum& operator-(BigNum& that);
	
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
    
    // Вывод числа
	std::string operator<<(const BigNum& that);

	// Литерал с плавающей точкой
	Big

	// Число pi 


}

