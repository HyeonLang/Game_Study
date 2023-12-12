#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
   Type inference : 자료형 추론
   - auto and decltype
   // http://thbecker.net/articles/auto_and_decltype/section_01.html -> 자세한 내용은 여기에
*/

void ex1()
{
    vector<int> vec;
    // 너무김
    for (std::vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); iter++)
        cout << *iter;

    //auto로 추론해서 사용 가능
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
        cout << *iter;

    for (auto iter : vec)
        cout << iter;
}

void ex2()
{
    //타입을 자동으로 추론해줌
    int x = int();
    auto auto_x = x;

    // 
    /*
       타입을 추론할 때 꾸며주는 옵션을 제거함
       -> 키워드가 제거된 원본의 타입만 받는다.
    */
    const int& crx = x;
    auto auto_crx1 = crx;
    const auto& auto_crx2 = crx;
}


//templat type deduction(inference) -> auto랑 유사함 -> 자료형만 가져감
template<typename T>
void func_ex3(T arg) {}

void ex3()
{
    const int& crx = 123;
    func_ex3(crx);
}

void ex4()
{
    //const붙은 자료형을 auto&로 가져올떄는
    //const auto&가 됨
    const int c = 10;
    auto& rc = c;
}

void ex5()
{
    int i = 77;
    auto&& r1_1 = i; // int&& --> int&로 수정
    auto&& r1_2 = 77;// int&&
}

void ex6()
{
    int x = 77;
    const int* p1 = &x;
    auto p2 = p1; // const int*
}

struct S
{
    S() : x(77) {}
    int x;
};

void ex7()
{
    int x = 77;
    const int cx = 77;
    const int& crx = x;
    const S* p = new S();

    // 어떻게 추론될까
    auto a = x;
    auto b = cx;
    auto c = crx;
    auto d = p;
    auto e = p->x;

    //decltype -> declaration type -> 처음 선언된 자료형을 가져온다 
    typedef decltype(x) x_type;
    typedef decltype(cx) cx_type;
    typedef decltype(crx) crx_type;
    typedef decltype(p->x) s_x_type;

    // () -> add reference to l-value -> &를 추가한다.
    typedef decltype((x)) x_with_parens_type;
    typedef decltype((cx)) cx_with_parens_type;
    typedef decltype((crx)) crx_with_parens_type;
    typedef decltype((p->x)) s_x_with_parens_type;

}

const S foo() { return S(); }
const int& foobar() { return 123; }

void ex8()
{
    auto a = foo();
    // decltype()안에 있는 것들은 연산 x, 자료형만 유추하는 것 : 함수가 호출되지 않는다.
    typedef decltype(foo()) foo_type;

    auto b = foobar();
    typedef decltype(foobar()) foobar_type;

    // 이런식으로도 사용가능
    decltype(foobar()) c = foobar();

    std::vector<int> vec{ 1, 2, 3 };

    auto iter = vec.begin();
    decltype(vec.begin()) iter2 = vec.begin();

    // [] 반환값이 &형태라 다름
    auto first_element = vec[0]; // int
    decltype(vec[1]) second_element = vec[1]; // int&

}

void ex9()
{
    int x = 0;
    int y = 0;
    const int cx = 66;
    const int cy = 77;
    double d1 = 3.14;
    double d2 = 1.57;

    typedef decltype(x * y) prod_xy_type;
    auto a = x * y;


    // int임 -> 단독으로 썼을떄는 cosnt int가 맞지만 계산 결과는 새로운 값을 만든 것이기 떄문에 순수한 r-value임
    typedef decltype(cx * cy) prod_cxcy_type;  // return is(pure-r-value) : int
    auto b = cx * cy;

    // 두개의 결과값이 같은 자료형이고 l-value라면 -> & 형태로 리턴
    typedef decltype(false ? d1 : d2) cond_type; // result is lvalue : double&
    auto c = false ? d1 : d2;

    typedef decltype(false ? 1.0 : 1.0) cond_type; // : double
    auto c = false ? 1.0 : 1.0;

    // 두개의 결과값이 다른 자료형일 때는 큰 자료형으로 형변환 되어 리턴 -> &은 사라짐
    typedef decltype(true ? x : d2) cond_type_mixed; // promotion of x to double
    auto d = true ? x : d2;

}

// 값이 같을 경우 레퍼런스 형태가 나가는데 x와 y가 지역변수라 값이 소멸함 -> 문제 발생
template <typename T, typename S>
auto fpmin_wrong(T x, S y) -> decltype(x < y ? x : y) // -> 반환형 지정, 가독성을 위함
{
    return x < y ? x : y;
}

// 이런식으로 레퍼런스를 지워 수정을 해야함 
template <typename T, typename S>
auto fpmin(T x, S y) -> typename std::remove_reference<decltype(x < y ? x : y)>::type
{
    return x < y ? x : y;
}

void ex10()
{
    int i = 33;
    double d = 1.1;
    int& j = i;

    typedef decltype(fpmin_wrong(d, d)) fpmin_wrong_type1;
    typedef decltype(fpmin_wrong(i, d)) fpmin_wrong_type2;
    typedef decltype(fpmin_wrong(j, d)) fpmin_wrong_type3;

    typedef decltype(fpmin(d, d)) fpmin_type1;
    typedef decltype(fpmin(i, d)) fpmin_type2;
    typedef decltype(fpmin(j, d)) fpmin_type3;
}

void ex11()
{
    std::vector<int> vec; //empty : 캐퍼시티가 0임
    typedef decltype(vec[0]) integer; // 직접 실행이 아니라 값만 추론하는거라 오류가 나지 않는다.
}

template <typename T>
class SomeFunctor
{
public:
    typedef T result_type;

    SomeFunctor() {}
    result_type operator()() { return result_type(); }
};

void ex12()
{
    SomeFunctor<int> func;

    typedef decltype(func)::result_type integer; // 네임스페이스를 통해 타입 안에 있는 타입을 꺼내온다.
}

void ex13()
{
    // 반환값 ()차이에따라 다를 수 있음 
    auto lambda = []() {return 77; };
    decltype(lambda) lambda2(lambda);   // int
    decltype((lambda)) lambda3(lambda); // int&

    cout << "Lambda functions" << endl;
    cout << &lambda << " " << &lambda2 << endl;
    cout << &lambda << " " << &lambda3 << endl;

}

void ex14()
{
    //generic lambda
    //람다에서는 매개변수 auto들어갈 수 있음 
    auto lambda = [](auto x, auto y)
    {
        return x + y;
    };

    cout << lambda(1.1, 2) << " " << lambda(3, 4) << " " << lambda(4.5, 2.2f) << endl; // 더블 인트 더블
}

int main()
{
    //ex13();
    ex14();
    return 0;
}