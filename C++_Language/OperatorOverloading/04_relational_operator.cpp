// 04_relational_operator.cpp

#include<iostream>
#include<vector>   // 동적 배열 : 꽉 차면 본인의 1.5배가 되도록 늘려준다.
#include<algorithm> // 여러 알고리즘이 정의되어 있음
using namespace std;

class Won
{
public:
    Won(int value = 0) : value(value) {}

    auto Getvalue()const { return value; }
    void SetValue(const int& value) { this->value = value; }

    bool operator == (const Won& rhs)const
    {
        // 비교할 값을 전부 써주어야 한다.
        return value == rhs.value && value1 == rhs.value1;
    }

    bool operator != (const Won& rhs) const
    {
        //return value != rhs.value || value1 != rhs.value1;
        return !(*this == rhs); // 위의 만들어둔 == 연산자를 뒤집어 간단하게 만들 수 있다.

    }

    friend ostream& operator << (ostream& out, const Won& won)
    {
        out << won.value;
        return out;
    }

    bool operator < (const Won& rhs) const {
        return value < rhs.value;
    }

    bool operator > (const Won& rhs) const {
        return value > rhs.value;
    }

private:
    int value;
    int value1;

};

bool test(const Won& lhs, const Won& rhs)
{
    return lhs.Getvalue() > rhs.Getvalue();
}

int main()
{
    Won w1(10), w2{ 20 };

    if (w1 == w2)
    {

    }

    vector<Won> wons(20, 0);

    
    for (auto& won : wons) {
        cout << won << " ";
    }
    cout << endl;

    int i = 0;
    for (auto& won : wons) {
        won.SetValue(i);
        i++;
    }

    for (auto& won : wons) {
        cout << won << " ";
    }
    cout << endl;

    random_shuffle(wons.begin(), wons.end());

    for (auto& won : wons) {
        cout << won << " ";
    }
    cout << endl;

    // 정렬,  < 연산자 정의가 필요함
    sort(wons.begin(), wons.end());

    for (auto& won : wons) {
        cout << won << " ";
    }
    cout << endl;
    
    //사용자가 정의한 함수를 사용해 정렬 가능
    sort(wons.begin(), wons.end(), test);

    for (auto& won : wons) {
        cout << won << " ";
    }
    cout << endl;

    // 람다식 사용 : 익명 함수
    // 과제 : 람다식 조사, for each문
    sort(wons.begin(), wons.end(),
        [](const Won& lhs, const Won& rhs)
        {
            return lhs.Getvalue() < rhs.Getvalue();
        });

    for (const auto& won : wons)
        cout << won << " ";
    cout << endl;



    return 0;
}