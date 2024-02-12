#include <iostream>
#include "BigNum.hpp"
#include <ctime>
#include <typeinfo>
#include "../include/test_system.hpp"

//--------------
// Test helpers
//--------------


//------------------------------------------
// Creating and Assignment testing functions
//------------------------------------------

using namespace TestSystem;

bool test_cr_empty()
{
    try
    {
        BigNum a;
    }
    catch (const std::exception& exc)
    {
        return FAIL;
    }

    return OK;
}

bool test_cr_standard()
{
    try
    {
        BigNum a = "16216.26264";
    }
    catch (const std::exception& exc)
    {
        return FAIL;
    }

    return OK;
}

bool test_cr_literal()
{
    try
    {
        BigNum a = "1234.678"_bn;
    }
    catch (const std::exception& exc)
    {
        return FAIL;
    }

    return OK;
}

bool test_assigment_BigNums()
{
    BigNum a = "1245.56890";
    BigNum b;
    b = a;
    return (b == a)? OK : FAIL;
}

bool test_literal_type()
{
    BigNum a;
    return (typeid("123"_bn).name() == typeid(a).name())? OK : FAIL;
}


//---------------------------
// Arithmetics Test Functions
//---------------------------


bool test_plus()
{
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    bool check1 = (a + b == BigNum(124.125-12063.65));
    bool check2 = (a + c == BigNum(124.125-124.125));
    bool check3 = (b + c == BigNum(-12063.65-124.125));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_minus()
{
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    bool check1 = (a - b == BigNum(124.125+12063.65));
    bool check2 = (a - c == BigNum(124.125+124.125));
    bool check3 = (b - c == BigNum(-12063.65+124.125));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_multiplicate()
{
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    bool check1 = (a * b == BigNum(124.125*(-12063.65)));
    bool check2 = (a * c == BigNum(124.125*(-124.125)));
    bool check3 = (b * c == BigNum(-12063.65*(-124.125)));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_division()
{
    BigNum a = "1.0";
    BigNum b = "2.0";
    BigNum c = "5.2";
    BigNum d = "3.0";
    bool check1 = (a / b == BigNum(0.5));
    bool check2 = (c / a == BigNum(5.2));
    bool check3 = (c / b == BigNum(2.6));
    // std::cout << a/b << std::endl;
    bool check4 = (a / d == "0.333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"_bn);
    return (check1 && check2 && check3 && check4)? OK : FAIL;
}

bool test_division_by_zero()
{
    BigNum a = "124.125";
    BigNum b = "0";
    try
    {
        BigNum c = a/b;
    }
    catch (...)
    {
        return OK;
    }

    return FAIL;
}

//-------------------------------------------
// Arithmetics with assignment test functions
//-------------------------------------------

bool test_plus_assignment()
{
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    a+=b;
    b+=c;
    c+=a;
    bool check1 = (a == BigNum(124.125-12063.65));
    bool check2 = (b == BigNum(-12063.65-124.125));
    bool check3 = (c == BigNum(-124.125-12063.65+124.125));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_minus_assignment()
{
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    a-=b;
    b-=c;
    c-=a;
    bool check1 = (a == BigNum(124.125+12063.65));
    bool check2 = (b == BigNum(-12063.65+124.125));
    bool check3 = (c == BigNum(-124.125-12063.65-124.125));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_multiplicate_assignment()
{
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    a*=b;
    b*=c;
    c*=a;
    bool check1 = (a == BigNum(124.125*(-12063.65)));
    bool check2 = (b == BigNum(-12063.65*(-124.125)));
    bool check3 = (c == "185864844.044531250");
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_division_assignment()
{
    BigNum a = "1.0";
    BigNum b = "2.0";
    BigNum c = "5.2";
    BigNum d = "3.0";
    a/=b;
    c/=a;
    d/=a;
    bool check1 = (a == BigNum(0.5));
    bool check2 = (c == BigNum(10.4));
    bool check3 = (d == BigNum(6.0));
    return (check1 && check2 && check3)? OK : FAIL;
}


//--------------
// Test palette
//--------------

int main(void)
{
    // Creating and assignment tests
    run_test("create empty BigNum",           test_cr_empty         );
    run_test("create standard BigNum",        test_cr_standard      );
    run_test("create BigNum with literal",    test_cr_literal       );
    run_test("assignment of BigNums",          test_assigment_BigNums);
    run_test("check equality of types",       test_literal_type     );
    
    // Arithmetics tests
    run_test("testing operator plus",         test_plus             );
    run_test("testing operator minus",        test_minus            );
    run_test("testing operator multiplicate", test_multiplicate     );
    run_test("testing operator division",        test_division         );
    run_test("check division by zero",        test_division_by_zero );

    // Arithmetics wigh assignment tests
    run_test("testing operator plus with assignment",        test_plus_assignment  );
    run_test("testing operator minus with assignment",        test_minus_assignment  );
    run_test("testing operator multiplicate with assignment",        test_multiplicate_assignment  );
    run_test("testing operator division with assignment",        test_division_assignment  );    
    return EXIT_SUCCESS;
}
