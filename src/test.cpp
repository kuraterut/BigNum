#include <iostream>
#include "BigNum.hpp"
#include <ctime>
#include <typeinfo>
#include "../include/test_system.hpp"

//------------------------------------------
// Creating and Assignment testing functions
//------------------------------------------

using namespace TestSystem;

bool test_cr_empty(){    
    BigNum a;

    return OK;
}

bool test_cr_standard(){
    BigNum a = "16216.26264";

    return OK;
}

bool test_cr_literal(){
    BigNum a = "1234.678"_bn;
    BigNum b = 125235.125135_bn;

    return OK;
}

bool test_assigment_BigNums(){
    BigNum a = "1245.56890";
    BigNum b;
    b = a;
    return (b == a)? OK : FAIL;
}

bool test_literal_type(){
    BigNum a;
    return (typeid("123"_bn).name() == typeid(a).name())? OK : FAIL;
}


//---------------------------
// Arithmetics Test Functions
//---------------------------


bool test_plus(){
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    bool check1 = (a + b == BigNum(124.125-12063.65));
    bool check2 = (a + c == BigNum(124.125-124.125));
    bool check3 = (b + c == BigNum(-12063.65-124.125));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_minus(){
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    bool check1 = (a - b == BigNum(124.125+12063.65));
    bool check2 = (a - c == BigNum(124.125+124.125));
    bool check3 = (b - c == BigNum(-12063.65+124.125));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_multiplicate(){
    BigNum a = "124.125";
    BigNum b = "-12063.65";
    BigNum c = "-124.125";
    bool check1 = (a * b == BigNum(124.125*(-12063.65)));
    bool check2 = (a * c == BigNum(124.125*(-124.125)));
    bool check3 = (b * c == BigNum(-12063.65*(-124.125)));
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_division(){
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

bool test_division_by_zero(){
    BigNum a = "124.125";
    BigNum b = "0";
    try{
        BigNum c = a/b;
    }

    catch (...){
        return OK;
    }

    return FAIL;
}

//-------------------------------------------
// Arithmetics with assignment test functions
//-------------------------------------------

bool test_plus_assignment(){
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

bool test_minus_assignment(){
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

bool test_multiplicate_assignment(){
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

bool test_division_assignment(){
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


//--------------------------
// Comparison test functions
//--------------------------

bool test_equality(){
    BigNum a = "125156374.125";
    BigNum b = "1251535.77235236";
    BigNum c = "1251535.77235236";
    BigNum d = "-1251535.77235236";
    bool check1 = (a == b);
    bool check2 = (c == b);
    bool check3 = (d == c);
    return (!check1 && check2 && !check3)? OK : FAIL;
}

bool test_not_equality(){
    BigNum a = "125156374.125";
    BigNum b = "1251535.77235236";
    BigNum c = "1251535.77235236";
    BigNum d = "-1251535.77235236";
    bool check1 = (a != b);
    bool check2 = (c != b);
    bool check3 = (d != c);
    return (check1 && !check2 && check3)? OK : FAIL;
}

bool test_more_than(){
    BigNum a = "125156374.125";
    BigNum b = "1251535.77235236";
    BigNum c = "1251535.77235236";
    BigNum d = "-1251535.77235236";
    bool check1 = (a > b);
    bool check2 = (c > b);
    bool check3 = (c > d);
    return (check1 && !check2 && check3)? OK : FAIL;
}

bool test_less_than(){
    BigNum a = "125156374.125";
    BigNum b = "1251535.77235236";
    BigNum c = "1251535.77235236";
    BigNum d = "-1251535.77235236";
    bool check1 = (b < a);
    bool check2 = (c < b);
    bool check3 = (d < c);
    return (check1 && !check2 && check3)? OK : FAIL;
}

bool test_more_or_equality(){
    BigNum a = "125156374.125";
    BigNum b = "1251535.77235236";
    BigNum c = "1251535.77235236";
    BigNum d = "-1251535.77235236";
    bool check1 = (a >= b);
    bool check2 = (c >= b);
    bool check3 = (c >= d);
    return (check1 && check2 && check3)? OK : FAIL;
}

bool test_less_or_equality(){
    BigNum a = "125156374.125";
    BigNum b = "1251535.77235236";
    BigNum c = "1251535.77235236";
    BigNum d = "-1251535.77235236";
    bool check1 = (a <= b);
    bool check2 = (c <= b);
    bool check3 = (d <= c);
    return (!check1 && check2 && check3)? OK : FAIL;
}
// Pi
bool calculating_Pi(){
    clock_t start = clock();
    BigNum my_Pi = Pi(100);
    clock_t finish = clock();
    std::cout << "\nPi calculating Time: "<< (double)(finish-start)/CLOCKS_PER_SEC<< " sec" << std::endl;
    std::cout << my_Pi << std::endl;
    BigNum rightPi = "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982"_bn;
    return (my_Pi == rightPi)? OK : FAIL;
}


//--------------
// Test palette
//--------------

int main(void)
{
    // Creating and assignment tests
    run_test("create empty BigNum",                                 test_cr_empty               );
    run_test("create standard BigNum",                              test_cr_standard            );
    run_test("create BigNum with literal",                          test_cr_literal             );
    run_test("assignment of BigNums",                               test_assigment_BigNums      );
    run_test("check equality of types",                             test_literal_type           );
    
    // Arithmetics tests
    run_test("testing operator plus",                               test_plus                   );
    run_test("testing operator minus",                              test_minus                  );
    run_test("testing operator multiplicate",                       test_multiplicate           );
    run_test("testing operator division",                           test_division               );
    run_test("check division by zero",                              test_division_by_zero       );

    // Arithmetics wigh assignment tests
    run_test("testing operator plus with assignment",               test_plus_assignment        );
    run_test("testing operator minus with assignment",              test_minus_assignment       );
    run_test("testing operator multiplicate with assignment",       test_multiplicate_assignment);
    run_test("testing operator division with assignment",           test_division_assignment    );

    // Comparison tests
    run_test("testing operator equality",                           test_equality               );
    run_test("testing operator not equality",                       test_not_equality           );
    run_test("testing operator more than",                          test_more_than              );
    run_test("testing operator less than",                          test_less_than              );
    run_test("testing operator more or equal than",                 test_more_or_equality       );
    run_test("testing operator less or equal than",                 test_less_or_equality       );

    //Calculating Pi
    run_test("calculating Pi",                                      calculating_Pi              );
    
    return EXIT_SUCCESS;
}
