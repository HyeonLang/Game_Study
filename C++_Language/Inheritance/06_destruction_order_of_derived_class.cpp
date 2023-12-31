// 06_destruction_order_of_derived_class.cpp

/*
	持失切 授辞税 蝕授生稽 社瑚切 硲窒
	胡煽 持失吉 梓端澗 陥献 梓端人 希 弦精 淫域研 故壱赤聖 溌懸戚 株陥.
	魚虞辞 持失税 蝕授生稽 梓端研 背薦馬澗 依戚 照穿馬陥.
*/
#include<iostream>
using namespace std;

class A
{
public:
	A() { cout << "A constructor" << endl; }
	~A() { cout << "A destructor" << endl; }

private:
	int a;
};

class B : public A
{
public:
	B() { cout << "B constructor" << endl; }
	~B() { cout << "B destructor" << endl; }

private:
	double b;
};

int main() {

	B b;

	/*
		鳶漁
		- 適掘什亜 姥繕端税 鳶漁 郊戚闘研 蓄亜馬食 cpu亜 羨悦馬奄 遂戚馬惟 背爽澗 奄狛
		- CPU亜 汽戚斗研 石聖 凶 切戟莫戚 設形 旭精 汽戚斗拭 砧腰 羨悦馬澗 依聖 号走
		- 析鋼旋生稽 亜舌 笛 呉獄 痕呪 滴奄拭 限仲 鳶漁 郊戚闘研 蓄亜廃陥.
	*/

	// a : 4byte
	sizeof(A);	// a a a a
	// b : 8byte + a : 4byte + padding : 4byte
	sizeof(B);	// a a a a け け け け b b b b b b b b : 旭精 byte 舘是稽 石奄 是背 希耕汽戚斗 諮脊 : padding

	class P1 {  
		char c;
		short s1;
		short s2;
	};
	sizeof(P1); // c け s1 s1 s2 s2 : 6byte
	//short莫拭 限仲 鳶漁郊戚闘 蓄亜

	class P2 { 
		char c1;
		double d;
		char c2;
	};
	sizeof(P2); // c1けけけけけけ  d d d d d d d d c2けけけけけけ : 24byte
	//double莫拭 限仲 鳶漁郊戚闘 蓄亜


	return 0;
}