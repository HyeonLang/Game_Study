// 00_operator_overloading.cpp

/*
   operator overloding
   - 기존에 존재하던 기본 연산자를 사용자가 직접 정의하여 사용하는 것
   - 원래 연산이 불가능하던 타입간의 연산을 처리할 수 있다.
   - (.), (.*), (::), (?:), (#), (##)을 제외한 연산자는 오버로딩이 가능하다.
   => 참고 링크 : https://docs.microsoft.com/ko-kr/cpp/cpp/operator-overloading?view=msvc-170

   기본 선언 방식

   반환값 operator연산자(연산자가 받을 피연산자)
*/

class Number
{
public:
    Number(int num)
        : num(num)
    {

    }

    void SetNum(int num)
    {
        this->num = num;
    }

    int GetNum()
    {
        return num;
    }

private:
    int num;
};

int main()
{
    Number a(10), b(20);

    {
        int result = a.GetNum() + b.GetNum();
        a.SetNum(result);
    }

    // 오버로딩을 사용한 예시
    //a = a + b;
    //a += b;

    return 0;
}