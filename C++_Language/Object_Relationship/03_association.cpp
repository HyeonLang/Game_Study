// 03_association.cpp
// 연계
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Patient
{
public:
	Patient(const string& name)
		: name(name)
	{}

	void AddDoctor(class Doctor* const doctor) //class Doctor* < 전방 선언 : 코드가 밑에 있음
	{
		doctors.push_back(doctor);
	}

	void MeetDoctor(); // Doctor의 정의부가 뒤에 있으므로 헤더와 바디를 나눠야한다.

private:
	string name;
	friend class Doctor;
	vector<class Doctor*> doctors;
};

class Doctor
{
public:
	Doctor(const string& name)
		: name(name)
	{}

	void AddPatient(class Patient* const patient)
	{
		patients.push_back(patient);
	}

	void MeetPatient()	// Patient의 정의부가 앞에 있으므로 바로 정의 가능
	{
		for (const auto& patient : patients)
			cout << "Meet Patient : " << patient->name << endl;
	}

private:
	string name;
	friend class Patient;
	vector<class Patient*> patients;
};

//
void Patient::MeetDoctor()
{
	for (const auto& doctor : doctors)
		cout << "Meet Doctor : " << doctor->name << endl;
}


int main()
{
	Patient* p1 = new Patient("Kim");
	Patient* p2 = new Patient("Part");
	Patient* p3 = new Patient("Lee");

	Doctor* d1 = new Doctor("Doc. Lee");
	Doctor* d2 = new Doctor("Doc. Kim");

	// Associztion(연계)
	// 장기간으로 치료를 받을 경우 의사와 환자인 경우 의사도 환자를 알아야하고, 환자도 의사를 알아야한다.
	// 서로가 서로에게 영향을 끼질 수 있다. (좋지 않은 경우, 하나 바뀌면 둘 다 수정될 수 있기 때문 <커플링관계> : 피하는 것이 좋다.)
	p1->AddDoctor(d1);
	d1->AddPatient(p1);

	p2->AddDoctor(d2);
	d2->AddPatient(p2);

	p3->AddDoctor(d2);
	d2->AddPatient(p3);

	p2->MeetDoctor();
	d2->MeetPatient();

	// 먼저 만들어진 클래스는 다른 클래스와 관계를 가질수 있기 때문에
	// 다른 클래스보다 먼저 지우게 되면 문제가 생길 수 있다. 
	// 그렇기 때문에 **생성 된 순서의 역순**으로 해제하는게 좋다. (공식)
	delete d2; // 생성된 **역순**으로 해제한다. 먼저 생성된 클래스는 다른 클래스와 관계를 맺고 있을 가능성이 높기 때문이다.
	delete d1;
	delete p3;
	delete p2;
	delete p1;


	return 0;
}
