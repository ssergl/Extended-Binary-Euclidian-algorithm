#include "BigInt.h"
#include "BigInt.h"
#include <time.h>
#include <cstring>

BigInt::BigInt()
{
	SIZE = 0;
	mass = nullptr;
	sign = '+';
}

BigInt::BigInt(long long int number)
{
	if (number < 0) sign = '-';
	else sign = '+';
	if (number % BASE == number) {
		SIZE = 1;

		mass = new uint32_t[SIZE];
		mass[0] = number;
	}
	else {
		SIZE = 2;

		mass = new uint32_t[SIZE];

		mass[0] = number % BASE;
		mass[1] = number / BASE;
	}
}

BigInt::BigInt(int number)
{
	if (number < 0) sign = '-';
	else sign = '+';
	SIZE = 1;

	mass = new uint32_t[SIZE];
	mass[0] = number;
}

BigInt::BigInt(size_t n, int value)
{
	SIZE = n;

	if (value != 0)
	{
		mass = new uint32_t[SIZE];
	}
	else {
		mass = (uint32_t*)calloc(SIZE, sizeof(uint32_t));
		if (mass == NULL)
		{
			throw std::invalid_argument("NULL in BigInt");
		}
	}
	sign = '+';
}

BigInt::BigInt(const char* s)
{
	if (s == nullptr) throw std::invalid_argument("This string is nullptr in BigInt!");

	size_t size_of_str = strlen(s);

	check_for_digits(s, size_of_str);
	bool sign = set_sign(s);

	size_t i;
	if (sign == false) i = quantity_of_leading_zeroes_in_constuctor(s, size_of_str) + 1;
	else i = quantity_of_leading_zeroes_in_constuctor(s, size_of_str);

	set_SIZE_of_BigInt(size_of_str);

	uint32_t Digit;
	BigInt powerOfTen(SIZE, 0);
	BigInt Number(SIZE, 0);
	powerOfTen.add_with_shortnumber_void(1);
	size_t count = 0;

	for (; i < size_of_str; i++)
	{
		Digit = static_cast <uint32_t>(s[size_of_str - 1 - count]) - '0';
		Number.operatorplus_in_constructor(powerOfTen.mull_with_shortnumber(Digit));
		powerOfTen.mull_with_shortnumber_void(10);
		count++;
	}

	i = Number.SIZE - 1;
	count = 0;
	while (Number.mass[i] == 0 && i > 0) {
		count++;
		i--;
	}

	SIZE = Number.SIZE - count;
	mass = new uint32_t[SIZE];

	for (i = 0; i < SIZE; i++) {
		mass[i] = Number.mass[i];
	}
}

BigInt BigInt::BigRand(uint64_t n)
{
	char* s = new char[n + 1];

	s[n] = '\0';
	s[0] = '1' + rand() % 9;
	for (size_t i = 1; i < n; i++)
	{
		s[i] = '0' + rand() % 10;
	}
	BigInt a(s);

	delete[] s;
	return a;
}

BigInt::~BigInt()
{
	delete[] mass;
}

void BigInt::operatorplus_in_constructor(const BigInt &other) 
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator+!");

	uint64_t i, sum, part = 0;
	for (i = 0; i < this->SIZE; i++)
	{
		sum = static_cast<uint64_t> (this->mass[i]) + static_cast<uint64_t> (other.mass[i]) + part;
		this->mass[i] = sum % BASE;
		part = sum / BASE;
	}
}

void BigInt::set_SIZE_of_BigInt(size_t size_of_str)
{
	if (size_of_str % 9 == 0)
	{
		SIZE = size_of_str / 9;
	}
	else {
		SIZE = size_of_str / 9 + 1;
	}
}


bool BigInt::set_sign(const char* s)
{
	if (s == nullptr) throw std::invalid_argument("This string is nullptr");
	if (s[0] == '-')
	{
		sign = '-';
		return false;
	}
	if (s[0] <= '9' && s[0] >= '0')
	{
		sign = '+';
		return true;
	}
	else std::invalid_argument("Error! The sign is incorrect in set_sign");
}

bool BigInt::get_sign() const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in get_sign!");
	if (this->sign == '-')
	{
		return false;
	}
	if (this->sign == '+')
	{
		return true;
	}
	else throw std::invalid_argument("Error! The sign is incorrect in get_sign");
}

void BigInt::check_for_digits(const char* s, size_t strlen)
{
	if (s == nullptr) throw std::invalid_argument("This string is nullptr in check_for_digits");
	size_t i;
	if (s[0] == '-') {
		if (strlen == 1) throw std::invalid_argument("'-' is not a number");
		for (i = 1; i < strlen; i++)
		{
			if (s[i] < '0' || s[i] > '9') throw std::invalid_argument("This is not number");
		}
	}
	else {
		for (i = 0; i < strlen; i++)
		{
			if (s[i] < '0' || s[i] > '9') throw std::invalid_argument("This is not number");
		}
	}
}

size_t BigInt::quantity_of_leading_zeroes_in_constuctor(const char* s, size_t strlen)
{
	if (s == nullptr) throw std::invalid_argument("This string is nullptr");
	size_t count = 0;
	while (s[count] == '0' && strlen - count > 1)
	{
		count++;
	}
	return count;
}

BigInt::BigInt(const BigInt& other)
{
	if (other.mass == nullptr) throw std::invalid_argument("Copy value is nullptr!");
	if (this == &other) return;
	else {
		this->mass = new uint32_t[other.SIZE];
		this->SIZE = other.SIZE;
		this->sign = other.sign;

		for (size_t i = 0; i < this->SIZE; i++)
		{
			this->mass[i] = other.mass[i];
		}
	}
}


BigInt BigInt::mull_with_shortnumber(int number) const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in mull_with_shortnumber!");
	uint32_t part = 0;
	uint64_t tmp;
	BigInt result(this->SIZE, -1);

	for (int i = 0; i < this->SIZE; i++) {
		tmp = static_cast<uint64_t>(this->mass[i]) * number + part;
		part = tmp / BASE;
		result.mass[i] = tmp % BASE;
	}
	return result;
}

void BigInt::mull_with_shortnumber_void(int number) const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in mull_with_shortnumber!");
	uint32_t part = 0;
	uint64_t tmp;

	for (int i = 0; i < this->SIZE; i++) {
		tmp = static_cast<uint64_t>(this->mass[i]) * number + part;
		part = tmp / BASE;
		this->mass[i] = tmp % BASE;
	}
}

void BigInt::add_with_shortnumber_void(int number) const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in add_with_shortnumber!");
	uint32_t part = 0;
	uint64_t tmp;

	for (int i = 0; i < this->SIZE; i++) {
		tmp = static_cast<uint64_t>(this->mass[i]) + number + part;
		part = tmp / BASE;
		this->mass[i] = tmp % BASE;
		if (part == 0) break;
		number = 0;
	}
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (other.mass == nullptr) throw std::invalid_argument("Assigned value is nullptr!");
	if (this != &other)
	{
		if (this->mass != nullptr)
		{
			delete[] this->mass;
		}
		this->mass = new uint32_t[other.SIZE];
		this->SIZE = other.SIZE;
		this->sign = other.sign;

		for (size_t i = 0; i < this->SIZE; i++)
		{
			this->mass[i] = other.mass[i];
		}
	}
	return *this;
}

uint64_t BigInt::add_in_operatorplus(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator add_in_operatorplus!");
	uint64_t this_last_elem = static_cast<uint64_t>(this->mass[this->SIZE - 1]);
	uint64_t other_last_elem = static_cast<uint64_t>(other.mass[other.SIZE - 1]);
	if (this->SIZE > other.SIZE) 
	{
		if (this_last_elem + 1 >= BASE && (other_last_elem + static_cast<uint64_t>(this->mass[other.SIZE - 1]) + 1 >= BASE)) return 1;
		else return 0;
	}
	if (other.SIZE > this->SIZE) 
	{
		if (other_last_elem + 1 >= BASE && (this_last_elem + static_cast<uint64_t>(other.mass[this->SIZE - 1]) + 1 >= BASE)) return 1;
		else return 0;
	}
	if (this->SIZE == other.SIZE) 
	{
		if (BASE > this_last_elem + other_last_elem + 1)
		{
			return 0;
		}
		else return 1;
	}
	return 0;
}


BigInt BigInt::operator+(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator+!");
	size_t maxSize_of_op = maxSize(*this, other);
	size_t minSize_of_op = minSize(*this, other);
	
	if (this->sign == '+' && other.sign == '-') {
		BigInt tmp = other;
		tmp.sign = '+';
		return *this - tmp;
	}
	if (this->sign == '-' && other.sign == '+') {
		BigInt tmp = other;
		return tmp + *this;
	}
	size_t add = add_in_operatorplus(other);
	BigInt result(maxSize_of_op + add, -1);
	if (add == 1) 
	{
		result.mass[result.SIZE - 1] = 0;
	}

	bool condition = (*this).comparisson_by_abs(other);
	
	sum_in_operatorplus(result, *this, other, maxSize_of_op, minSize_of_op);
	
	delete_extra_zeroes(result);
	if (this->sign == '-' && other.sign == '-') result.sign = '-';
	return result;
}

void BigInt::sum_in_operatorplus(BigInt& result, const BigInt& thisob, const BigInt& otherob, size_t maxSize_of_op, size_t minSize_of_op)
{
	uint64_t i, sum, part = 0;

	bool condition = (thisob).comparisson_by_abs(otherob);
	for (i = 0; i < minSize_of_op; i++)
	{
		sum = static_cast<uint64_t> (thisob.mass[i]) + static_cast<uint64_t> (otherob.mass[i]) + part;
		result.mass[i] = sum % BASE;
		part = sum / BASE;
	}
	if (condition == true) {
		for (i = minSize_of_op; i < maxSize_of_op; i++)
		{
			sum =  static_cast<uint64_t> (thisob.mass[i]) + part;
			result.mass[i] = sum % BASE;
			part = sum / BASE;
		}
	}
	if (condition == false) {
		for (i = minSize_of_op; i < maxSize_of_op; i++)
		{
			sum = static_cast<uint64_t> (otherob.mass[i]) + part;
			result.mass[i] = sum % BASE;
			part = sum / BASE;
		}
	}
	if (part != 0) result.mass[i] = part;
}

BigInt BigInt::operator+=(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator+=!");
	*this = *this + other;
	return *this;
}


BigInt BigInt::operator-(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator-!");
	if (*this == other) return 0;
	if (this->sign == '+' && other.sign == '-') {
		BigInt tmp = other;
		tmp.sign = '+';
		return *this + tmp;
	}
	if (this->sign == '-' && other.sign == '+') {
		BigInt tmp = *this;
		tmp.sign = '+';
		return -(tmp + other);
	}

	size_t maxSize_of_op = maxSize(*this, other);
	size_t minSize_of_op = minSize(*this, other);
	BigInt result(maxSize_of_op, -1);

	for (size_t i = minSize_of_op - 1; i < maxSize_of_op; i++)
	{
		result.mass[i] = 0;
	}

	bool condition = (*this).comparisson_by_abs(other);
	
	sub_in_operatorminus(result, *this, other, maxSize_of_op, minSize_of_op, condition);

	delete_extra_zeroes(result);
	if (condition == false && this->sign == '+' && other.sign == '+') result.sign = '-';
	if (condition == false && this->sign == '-' && other.sign == '-') result.sign = '+';
	if (condition == true && this->sign == '+' && other.sign == '+') result.sign = '+';
	if (condition == true && this->sign == '-' && other.sign == '-') result.sign = '-';
	return result;
}

void BigInt::sub_in_operatorminus(BigInt& result, const BigInt& thisob, const BigInt& otherob, size_t maxSize_of_op, size_t minSize_of_op, bool condition)
{
	long long int sub = 0;
	int part = 0;
	size_t i;
	if (condition == true) {
		for (i = 0; i < minSize_of_op; i++)
		{
			sub = static_cast<long long int> (thisob.mass[i]) - static_cast<long long int> (otherob.mass[i]) - part;
			result.mass[i] = sub < 0 ? sub + BASE : sub;
			part = sub < 0 ? 1 : 0;
		}
		for (i = minSize_of_op; i < maxSize_of_op; i++)
		{
			sub = static_cast<long long int> (thisob.mass[i]) - part;
			result.mass[i] = sub < 0 ? sub + BASE : sub;
			part = sub < 0 ? 1 : 0;
		}
	}
	if (condition == false) {
		for (i = 0; i < minSize_of_op; i++)
		{
			sub = static_cast<long long int> (otherob.mass[i]) - static_cast<long long int> (thisob.mass[i]) - part;
			result.mass[i] = sub < 0 ? sub + BASE : sub;
			part = sub < 0 ? 1 : 0;
		}
		for (i = minSize_of_op ; i < maxSize_of_op; i++)
		{
			sub = static_cast<long long int> (otherob.mass[i]) - part;
			result.mass[i] = sub < 0 ? sub + BASE : sub;
			part = sub < 0 ? 1 : 0;
		}
	}	
}

bool BigInt::comparisson_by_abs(const BigInt& other) const
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator+=!");
	if (this->SIZE > other.SIZE)
	{
		return true;
	}
	if (this->SIZE < other.SIZE)
	{
		return false;
	}
	if (this->SIZE == other.SIZE)
	{
		size_t i = this->SIZE - 1;
		while (this->mass[i] == other.mass[i] && i > 0) {
			i--;
		}
		if (this->mass[i] > other.mass[i]) return true;
		else return false;
	}
}

BigInt BigInt::operator-=(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator+=!");
	*this = *this - other;
	return *this;
}

BigInt BigInt::operator-()
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in operator-!");
	if (this->sign = '-') this->sign = '+';
	if (this->sign = '+') this->sign = '-';
	return *this;
}

void BigInt::delete_extra_zeroes(BigInt& a) const
{
	if (a.mass == nullptr) throw std::invalid_argument("Nullptr in delete_extra_zeroes!");
	long long int i = a.SIZE - 1;
	while (a.mass[i] == 0 && i > 0) 
	{
		i--;
	}

	if (i == a.SIZE - 1) return;

	BigInt tmp(i + 1, -1);
	tmp.sign = a.sign;
	for (size_t i = 0; i < tmp.SIZE; i++)
	{
		tmp.mass[i] = a.mass[i];
	}
	a = tmp;
}

size_t BigInt::maxSize(const BigInt& op1, const BigInt& op2) const
{
	if (op1.mass == nullptr || op2.mass == nullptr) throw std::invalid_argument("Nullptr in maxSize!");
	size_t max = op1.SIZE > op2.SIZE ? op1.SIZE : op2.SIZE;
	return max;
}

size_t BigInt::minSize(const BigInt& op1, const BigInt& op2) const
{
	if (op1.mass == nullptr || op2.mass == nullptr) throw std::invalid_argument("Nullptr in minSize!");
	size_t min = op1.SIZE < op2.SIZE ? op1.SIZE : op2.SIZE;
	return min;
}

bool BigInt::operator<(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator<!");
	size_t i;
	if (this->sign == other.sign) {
		if (this->sign == '+') {
			if (this->SIZE == other.SIZE) {
				i = this->SIZE - 1;
				while (this->mass[i] == other.mass[i] && i > 0) {
					i--;
				}
				if (this->mass[i] < other.mass[i]) return true;
				else return false;
			}
			else return this->SIZE < other.SIZE;
		}
		if (this->sign == '-') {
			if (this->SIZE == other.SIZE) {
				i = this->SIZE - 1;
				while (this->mass[i] == other.mass[i] && i > 0) {
					i--;
				}
				if (this->mass[i] > other.mass[i]) return true;
				else return false;
			}
			else return this->SIZE > other.SIZE;
		}
	}
	else if (this->sign == '-' && other.sign == '+') {
		return true;
	}
	else if (other.sign == '-' && this->sign == '+') {
		return false;
	}
	return false;
}

bool BigInt::operator>(const BigInt& other) {
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator> !");
	return !((*this < other) || comparisson_of_mass(*this, other));
}

bool BigInt::operator<= (const BigInt& other) {
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator<= !");
	return ((*this < other) || comparisson_of_mass(*this, other));
}
bool BigInt::operator>=(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator>= !");
	return ((*this > other) || comparisson_of_mass(*this, other));
}
bool BigInt::operator==(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator== !");
	return ((this->sign == other.sign) && comparisson_of_mass(*this, other));
}

bool BigInt::operator!=(const BigInt& other)
{
	if (this->mass == nullptr || other.mass == nullptr) throw std::invalid_argument("Nullptr in operator!= !");
	return !(*this == other);
}

bool BigInt::comparisson_of_mass(const BigInt& a, const BigInt& b) {
	if (a.mass == nullptr || b.mass == nullptr) throw std::invalid_argument("Nullptr in comparisson_of_mass !");
	if (a.SIZE != b.SIZE) 
	{
		return false;
	}
	else
	{
		size_t i = 0;
		while (a.mass[i] == b.mass[i] && i < a.SIZE) 
		{
			i++;
		}		
		if (i == a.SIZE) return true;
		else return false;
	}
}

BigInt BigInt::operator>>(int shift)
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in right_bitshift !");
	if (shift == 0) return *this;
	if (this->SIZE == 1 && this->mass[0] == 0) return *this;
	if (shift < 0) throw std::invalid_argument("Shift must be possitive");
	if (shift > 31)
	{
		int j = shift / 32;
		if (this->SIZE <= j) {
			return 0; 
		}
		BigInt result(this->SIZE - j, -1);

		for (size_t i = 0; i < this->SIZE - j; i++)
		{
			result.mass[i] = this->mass[i + j];
		}
		result.right_bitshift(shift % 32);
		delete_extra_zeroes(result);
		result.sign = this->sign;
		return result;
	}
	BigInt result = *this;
	result.right_bitshift(shift);
	delete_extra_zeroes(result);
	result.sign = this->sign;
	return result;
}

void BigInt::operator>>=(int shift)
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in right_bitshift !");
	if (shift == 0) return;
	if (this->SIZE == 1 && this->mass[0] == 0) return;
	if (shift < 0) throw std::invalid_argument("Shift must be possitive");
	if (shift > 31)
	{
		int j = shift / 32;
		if (this->SIZE <= j) {
			throw std::invalid_argument("too much shift for operator>>=");
		}
		for (size_t i = 0; i < this->SIZE - j; i++)
		{
			this->mass[i] = this->mass[i + j];
		}
		(*this).right_bitshift(shift % 32);
		delete_extra_zeroes(*this);
	}
	(*this).right_bitshift(shift);
	delete_extra_zeroes(*this);
}

BigInt BigInt::operator<<(int shift)
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in right_bitshift !");
	if (shift == 0) return *this;
	if (this->SIZE == 1 && this->mass[0] == 0) return *this;
	if (shift < 0) throw std::invalid_argument("Shift must be possitive");
	uint64_t add = (static_cast<uint64_t>(this->mass[this->SIZE - 1]) << static_cast<uint64_t>(shift % 32)) < static_cast<uint64_t>(BASE - 1) ? 0 : 1;
	if (shift > 31)
	{
		int j = shift / 32;
		BigInt result(this->SIZE + j + add, -1);

		for (size_t i = 0; i < j; i++)
		{
			result.mass[i] = 0;
		}
		for (size_t i = 0; i < this->SIZE; i++)
		{
			result.mass[i + j] = this->mass[i];
		}
		if (add != 0) result.mass[result.SIZE - 1] = 0;
		result.left_bitshift(shift % 32);
		delete_extra_zeroes(result);
		result.sign = this->sign;
		return result;
	}
	BigInt result(this->SIZE + add, -1);
	for (size_t i = 0; i < this->SIZE; i++)
	{
		result.mass[i] = this->mass[i];
	}
	if (add != 0) result.mass[result.SIZE - 1] = 0;
	result.left_bitshift(shift);
	delete_extra_zeroes(result);
	result.sign = this->sign;
	return result;
}

void BigInt::right_bitshift(int shift) const
{
	if (this->mass == nullptr ) throw std::invalid_argument("Nullptr in right_bitshift !");
	uint32_t bit_parity = (this->mass[this->SIZE - 1] << (32 - shift));
	this->mass[this->SIZE - 1] = this->mass[this->SIZE - 1] >> shift;
	uint32_t tmp;

	for (long long int i = this->SIZE - 2; i >= 0; i--)
	{
		tmp = this->mass[i];
		this->mass[i] = ((this->mass[i] >> shift) | bit_parity);
		bit_parity = (tmp << (32 - shift));
	}
}

void BigInt::left_bitshift(int shift) const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in left_bitshift !");
	uint32_t bit_parity = this->mass[0] >> (32 - shift);
	this->mass[0] = this->mass[0] << shift;
	uint32_t tmp;

	for (size_t i = 1; i < this->SIZE; i++)
	{
		tmp = this->mass[i];
		this->mass[i] = (this->mass[i] << shift) | bit_parity;
		bit_parity = tmp >> (32 - shift);
	}
}

BigInt BigInt::from32_to10() const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in from32_to10 !");

	BigInt Number10(2 * this->SIZE + 1, 0);

	Number10.add_with_shortnumber_in_10(this->mass[this->SIZE - 1]);
	for (long long int i = this->SIZE - 2; i >= 0; i--)
	{
		Number10.mull_with_shortnumber_in_10(BASE);
		Number10.add_with_shortnumber_in_10(this->mass[i]);
	}
	delete_extra_zeroes(Number10);

	return Number10;
}

void BigInt::add_with_shortnumber_in_10(uint64_t number) const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in add_with_shortnumber_10 !");
	uint32_t part = 0;
	uint64_t tmp;

	for (int i = 0; i < this->SIZE; i++) 
	{
		tmp = static_cast<uint64_t>(this->mass[i]) + number + part;
		part = tmp / BASEof10;
		this->mass[i] = tmp % BASEof10;
		number = 0;
	}
}

void BigInt::mull_with_shortnumber_in_10(uint64_t number) const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in mull_with_shortnumber_10 !");
	uint32_t part = 0;
	uint64_t tmp;

	for (int i = 0; i < this->SIZE; i++) {
		tmp = static_cast<uint64_t>(this->mass[i]) * number + part;
		part = tmp / BASEof10;
		this->mass[i] = tmp % BASEof10;
	}
}

int BigInt::rtwo()
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in rtwo !");
	return (this->mass[0] % 2);
}

void BigInt::check_nullptr() const
{
	if (this->mass == nullptr) throw std::invalid_argument("There is nullptr!");
}

void BigInt::Number_in_32() const
{
	if (this->mass == nullptr) throw std::invalid_argument("Nullptr in Number_in_32 !");
	std::cout << std::endl;
	std::cout << "Number in 2^32: " << std::endl;
	if (this->sign == '-')
	{
		std::cout << this->sign;
	}
	for (long long int i = this->SIZE - 1; i >= 0; i--)
	{
		std::cout << this->mass[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}

std::ostream& operator<< (std::ostream& os, const BigInt& a)
{
	if (a.mass == nullptr) throw std::invalid_argument("Nullptr in ostream& operator<< !");
	BigInt Number10 = a.from32_to10();
	char** str;
	str = new char* [Number10.SIZE];
	for (size_t i = 0; i < Number10.SIZE; i++)
	{
		str[i] = new char[10];
	}
	snprintf(str[Number10.SIZE - 1], 10, "%d", Number10.mass[Number10.SIZE - 1]);
	long long int i;
	for (i = Number10.SIZE - 2; i >= 0; i--)
	{
		snprintf(str[i], 10, "%09d", Number10.mass[i]);
	}

	if (a.sign == '-') os << a.sign;
	for (i = Number10.SIZE - 1; i >= 0; i--)
	{
		os << str[i];
	}
	for (size_t i = 0; i < Number10.SIZE; i++)
	{
		delete str[i];
	}
	delete[] str;

	return os;
}

