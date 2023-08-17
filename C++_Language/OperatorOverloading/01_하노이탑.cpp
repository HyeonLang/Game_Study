// 하노이 탑 높이 N을 입력받아 

#include <iostream>
#include <stack>
using namespace std;

int N;
int min_count = 987654321;
stack<int> h1;
stack<int> h2;
stack<int> h3;

bool checkEnd() {
	if (h3.size() == N) return true;
	return false;
}

bool checkMove(int num, stack<int> h) {
	if (!h.empty()) {
		if (h.top() > num) return false;
	}
	return true;
}

void Hanoi(int count) {
	if (min_count < count) return;
	
	if (checkEnd()) {
		min_count = min(min_count, count);
	}

	if (!h1.empty()) {
		if (checkMove(h1.top(), h2)) {
			h2.push(h1.top());
			h1.pop();
			Hanoi(count + 1);
		}
		if (checkMove(h1.top(), h3)) {
			h3.push(h1.top());
			h1.pop();
			Hanoi(count + 1);
		}
	}
	if (!h2.empty()) {
		if (checkMove(h2.top(), h1)) {
			h1.push(h2.top());
			h2.pop();
			Hanoi(count + 1);
		}
		if (checkMove(h2.top(), h3)) {
			h3.push(h2.top());
			h2.pop();
			Hanoi(count + 1);
		}
	}
	if (!h3.empty()) {
		if (checkMove(h3.top(), h1)) {
			h1.push(h3.top());
			h3.pop();
			Hanoi(count + 1);
		}
		if (checkMove(h3.top(), h2)) {
			h2.push(h3.top());
			h3.pop();
			Hanoi(count + 1);
		}
	}
}

int main() {
	
	cin >> N;
	for (int n = N; n > 0; n--) {
		h1.push(n);
	}
	
	Hanoi(0);
	cout << min_count;
}