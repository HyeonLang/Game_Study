// 04_dependencies.cpp
// ����

#include<iostream>
#include<chrono> // �ð� ���� ���̺귯�� : ������ �ð� ���� ����
using namespace std;
using namespace std::chrono; // �ð� ���� �Լ�

class Timer //�ð� ���� Ŭ���� ����
{
public:
	Timer()
	{
		start_time = high_resolution_clock::now(); //����ð����� �ʱ�ȭ
	}

	void Elapsed() //���
	{
		auto current_time = high_resolution_clock::now(); // ������ �ð� - ����ð�
		
		//milli������ double������ �ð� ����
		duration<double, std::milli> delta = current_time - start_time; // �� �ð� ���̿� ���� ������ double���� milli�� ����

		//�Լ� ȣ�� ������ ������ ��
		//start_time = current_time;

		cout << delta.count() << std::endl; //count() : delta�� �ð� ����
	}
private:
	time_point<high_resolution_clock> start_time;// �ð��� �����ϴ� �ڷ��� ��ü
};

class Worker
{
public:
	void DoSomething()
	{
		// ���� ����
		// �ʿ��� ���� ������ ���� ���� : �ð������� ���� Timer Ŭ���� ���
		Timer timer; //���� ���� : �ʿ並 ���ϸ� ��������
		for (int i = 0; i < 100'000'000; i++)
			;
		timer.Elapsed(); //for���� ��� ���� ���� �ð��� ����
	}
};

int main()
{
	Worker w;
	w.DoSomething();

	return 0;
}

// ����
// chrono���� 

