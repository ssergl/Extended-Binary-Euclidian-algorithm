#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

typedef size_t uint64_t;
typedef unsigned int uint32_t;

class BigInt
{
private:
	uint32_t* mass;
	char sign;

	size_t SIZE;

	const size_t BASE = 4294967296;
	const size_t BASEof10 = 1000000000;
public:
	BigInt();
	BigInt(size_t n, int value);
	BigInt(const char* s);
	BigInt(long long int value);
	BigInt(int value);
	BigInt(const BigInt& other);
	~BigInt();

	BigInt& operator=(const BigInt& other);
	BigInt operator+(const BigInt& other);
	BigInt operator+=(const BigInt& other);
	BigInt operator-(const BigInt& other);
	BigInt operator-=(const BigInt& other);
	BigInt operator>>(int shift);
	BigInt operator<<(int shift);
	void operator>>=(int shift);
	BigInt operator-();
	void operatorplus_in_constructor(const BigInt &other);

	bool operator<(const BigInt& other);
	bool operator>(const BigInt& other);
	bool operator<= (const BigInt& other);
	bool operator>=(const BigInt& other);
	bool operator==(const BigInt& other);
	bool operator!=(const BigInt& other);

	BigInt BigRand(uint64_t n);
	BigInt mull_with_shortnumber(int value) const;
	void right_bitshift(int shift) const;
	void left_bitshift(int shift) const;
	BigInt from32_to10() const;

	bool comparisson_of_mass(const BigInt& a, const BigInt& b);
	bool comparisson_by_abs(const BigInt& other) const;
	bool set_sign(const char* s);
	bool get_sign() const;
	
	void mull_with_shortnumber_void(int number) const;
	void add_with_shortnumber_void(int value) const;
	void delete_extra_zeroes(BigInt& number) const;
	void check_for_digits(const char* s, size_t strlen);
	void set_SIZE_of_BigInt(size_t);
	void add_with_shortnumber_in_10(uint64_t number) const;
	void mull_with_shortnumber_in_10(uint64_t number) const;
	void Number_in_32() const;
	void sum_in_operatorplus(BigInt& result, const BigInt& thisob, const BigInt& otherob, size_t maxSize_of_op, size_t minSize_of_op);
	void sub_in_operatorminus(BigInt& result, const BigInt& thisob, const BigInt& otherob, size_t maxSize_of_op, size_t minSize_of_op, bool condition);

	size_t maxSize(const BigInt& a, const BigInt& b) const;
	size_t minSize(const BigInt& a, const BigInt& b) const;
	size_t quantity_of_leading_zeroes_in_constuctor(const char* s, size_t strlen);
	uint64_t add_in_operatorplus(const BigInt& other);
	
	int rtwo();
	void check_nullptr() const;
	
	friend std::ostream& operator<< (std::ostream&, const BigInt&);
};

std::ostream& operator<< (std::ostream&, const BigInt&);
#endif