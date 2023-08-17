
#include <iostream>
using namespace std;

/*
   과제 : class 캐스팅
      - Hour 클래스가 Minute, Second, Milli_Second 클래스로 캐스팅되도록 처리

   + 추가 과제
      - Milli_Second 클래스가 Hour, Minute, Second 클래스로 캐스팅되도록 처리

*/

class Minute;
class Second;
class Milli_Second;

class Hour
{
public:
    Hour(int h) : h(h) {}
    int getH() { return h; }
    void setH(int h) { this->h = h; }

    operator Minute();
    operator Second();
    operator Milli_Second();

private:
    int h;
};

class Minute
{
public:
    Minute(int m) : m(m) {}
    int getM() { return m; }
    void setM(int m) { this->m = m; }

    operator Hour();
    operator Second();
    operator Milli_Second();

private:
    int m;
};

class Second
{
public:
    Second(int s) : s(s) {}
    int getS() { return s; }
    void setS(int s) { this->s = s; }

    operator Hour();
    operator Minute();
    operator Milli_Second();

private:
    int s;
};

class Milli_Second
{
public:
    Milli_Second(int ms) : ms(ms) {}
    int getMS() { return ms; }
    void setMS(int ms) { this->ms = ms; }

    operator Hour();
    operator Minute();
    operator Second();

private:
    int ms;
};

void PrintHour(Hour h)
{
    cout << h.getH() << "시간" << endl;
}

void PrintMinute(Minute m)
{
    cout << m.getM() << "분" << endl;
}

void PrintSecond(Second s)
{
    cout << s.getS() << "초" << endl;
}

void PrintMilli_Second(Milli_Second ms)
{
    cout << ms.getMS() << "밀리초" << endl;
}

Hour::operator Minute()
{
    return Minute(h * 60);
}

Hour::operator Second()
{
    return Second(h * 60 * 60);
}

Hour::operator Milli_Second()
{
    return Milli_Second(h * 60 * 60 * 1000);
}

Minute::operator Hour()
{
    return Hour(m / 60);
}

Minute::operator Second()
{
    return Second(m * 60);
}

Minute::operator Milli_Second()
{
    return Milli_Second(m * 60 * 1000);
}

Second::operator Hour()
{
    return Hour(s / 3600);
}

Second::operator Minute()
{
    return Minute(s / 60);
}

Second::operator Milli_Second()
{
    return Milli_Second(s * 1000);
}

Milli_Second::operator Hour()
{
    return Hour(ms / (1000 * 3600));
}

Milli_Second::operator Minute()
{
    return Minute(ms / (1000 * 60));
}

Milli_Second::operator Second()
{
    return Second(ms / 1000);
}

int main()
{
    Hour h(10);

    PrintHour(h);
    PrintMinute(h);
    PrintSecond(h);
    PrintMilli_Second(h);

    return 0;
}