// 07_multi_inheritance.cpp
// 다중 상속

/*
   Multi Inheritance - 다중 상속
   - 한 클래스가 두 개 이상의 클래스를 상속받는 것
   - 다중 상속이 좋은 방식은 아니기 때문에 다른 언어에서는
   허용하지 않는 경우도 있다.
*/

// 과제 : 다중 상속의 문제점 조사, 다이아몬드 상속 문제 조사

#include<iostream>
using namespace std;

class USBDevice
{

public:
    USBDevice() = default;
    explicit USBDevice(int id) : id(id) {}

    auto GetID() const { return id; }
    void PlugAndPlay() {}

private:
    int id;
};

class NetworkDevice
{
public:
    NetworkDevice() = default;
    NetworkDevice(int id) : id(id) {}

    auto GetID() const { return id; }
    void Networking() {}

private:
    int id;
};

// 두 개 이상의 클래스를 상속받고 있음. -> 다중 상속
class USBNetworkDevice : public USBDevice, public NetworkDevice
{
public:
    USBNetworkDevice(int usb_id, int net_id)
        : USBDevice(usb_id)   // 원하는 생성자 호출 방식을 결정하여 생성
        , NetworkDevice(net_id)
    {}

    USBNetworkDevice(int id)
        : USBDevice(id)
        , NetworkDevice(id)
    {}
};

int main()
{
    USBNetworkDevice device(1.10, 2.10);
    device.PlugAndPlay();
    device.Networking();

    // 기반 클래스의 멤버 함수가 중복되어 **모호함**
    //device.GetID(); // error = ambiguous

    // 해결방법1 -> 중복된 함수이름을 변경 -> 번거로움

    // 해결방법2 -> 이름 지정하여 사용하자 
    cout << device.USBDevice::GetID() << endl;
    cout << device.NetworkDevice::GetID() << endl;

    return 0;
}