#include "BigInt.h"
#include <stdlib.h>
#include <chrono>
#include <time.h>

using std::cout;
using std::endl;

bool check_for_null(BigInt& a, BigInt& b, BigInt& x, BigInt& y, BigInt& d)
{
    BigInt null = "0";
    if (a == null && b == null) {
        throw std::invalid_argument("The numbers are equal to zero in Algorithm");
    }
    if (a == null) {
        d = b;
        x = 0;
        y = 1;
        return false;
    }
    if (b == null) {
        throw std::invalid_argument("b is null");
        return false;
    }
    return true;
}

bool swap(BigInt& a, BigInt& b)
{
    if (a >= b) return false;
    else {
        BigInt tmp;
        tmp = a;
        a = b;
        b = tmp;
        return true;
    }
}

void first_func(BigInt& a, BigInt& b, int& k)
{
    while (a.rtwo() == 0 && b.rtwo() == 0)
    {
        a >>= 1;
        b >>= 1;
        k++;
    }
}

void second_func(BigInt& a, BigInt& b, BigInt& u, BigInt& v, BigInt& A, BigInt& B, BigInt& C, BigInt& D)
{
    BigInt null = 0;
    while (u != null) {
        while (u.rtwo() == 0) {
            u >>= 1;
            if (A.rtwo() == 0 && B.rtwo() == 0) {
                A >>= 1;
                B >>= 1;
            }
            else {
                A = (A + b);
                A >>= 1;
                B = (B - a);
                B >>= 1;
            }
        }
        while (v.rtwo() == 0) {
            v >>= 1;
            if (C.rtwo() == 0 && D.rtwo() == 0) {
                C >>= 1;
                D >>= 1;
            }
            else {
                C = (C + b);
                C >>= 1;
                D = (D - a);
                D >>= 1;
            }
        }
        if (u >= v) {
            u = u - v;
            A = A - C;
            B = B - D;
        } 
        else {
            v = v - u;
            C = C - A;
            D = D - B;
        }
    }
}

void print_gcd(BigInt& a, BigInt& b, BigInt& x, BigInt& y, BigInt& d)
{
    std::cout << "x * a + y * b = gcd(a, b)" << std::endl;
    std::cout << "(" << x << ")" << " * " << a;
    std::cout << " + ";
    std::cout << "(" << y << ")" << " * " << b;
    std::cout << " = " << d << std::endl;
}

void Algorithm(BigInt& a, BigInt& b, BigInt& x, BigInt& y, BigInt& d)
{
    a.check_nullptr();
    b.check_nullptr();
    if ((a.get_sign() && b.get_sign()) == false) {
        throw std::invalid_argument("The numbers supplied to the input are negative in Algorithm!");
    }
    if (check_for_null(a, b, x, y, d) == false) return;

    BigInt a1 = a;
    BigInt b1 = b;
    bool s_swap = swap(a1, b1);
    int k = 0;
    first_func(a1, b1, k);

    BigInt u = a1;
    BigInt A = 1;
    BigInt B = 0;
    d = b1;
    x = 0;
    y = 1;

    second_func(a1, b1, u, d, A, B, x, y);

    if (s_swap == true) {
        BigInt tmp = x;
        x = y;
        y = tmp;
    }
    
    d = d << k;
}


int main()
{
    try {
        srand(time(0));
        BigInt a;
        BigInt b;
        BigInt x;
        BigInt y;
        BigInt d;

        size_t i;
        size_t counter = 600;
        for (i = 1; i < 7; i++) 
        {
            std::cout << i << " ";
            
            a = a.BigRand(counter);
            b = b.BigRand(counter);

            auto begin = std::chrono::high_resolution_clock::now();

            Algorithm(a, b, x, y, d);
            auto end = std::chrono::high_resolution_clock::now();

            cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;
            counter *= 2;
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
