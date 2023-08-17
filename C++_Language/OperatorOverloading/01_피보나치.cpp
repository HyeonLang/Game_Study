// N번째 피보나치 수까지 출력

#include <iostream>

using namespace std;



void fibonacci(int count, int n1, int n2) {
	cout << n1 + n2 << endl;
	if(count - 1 != 0)
		fibonacci(count - 1, n2, n1 + n2); 
}


int main() {
	int N;
	cin >> N;
	cout << 1 << endl;
	if (N > 1)
		fibonacci(N-1, 0, 1);
}