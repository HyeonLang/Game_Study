#include "stdafx.h"
#include "LogSystem.h"

namespace LogSystem
{
	TARGET target = TARGET::ALL;

	std::filesystem::path log_path = "./MyLog.txt";

	void Print(LPCSTR log);

}


namespace LogSystem
{
	void SetTarget(const TARGET target)
	{
		LogSystem::target = target;
	}

	void SetLog(const std::string type, const std::string function, const std::string file, const std::string line, const std::string format, ...)
	{
		// 출력할 로그 데이터를 저장할 string
		std::string	Log = "";

		// 가변 인자 포인터 생성
		va_list List = nullptr;

		// 가변 인자 포인터의 시작 위치를 받는다.
		va_start(List, format);
		{
			// vsprintf_s() : string에 size 만큼 arg_format(형식)과 arg_list(인자)를 합쳐 문자열을 만들어 준다.
			size_t Size = _vscprintf(format.c_str(), List) + sizeof('\0');

			// 만들어질 크기만큼 동적할당을 받는다.
			char* Message = new char[Size];

			// vsprintf_s() : string에 size 만큼 arg_format(형식)과 arg_list(인자)를 합쳐 문자열을 만들어 준다.
			vsprintf_s(Message, Size, format.c_str(), List);

			// 해당 로그를 띄운 호출자의 정보를 넣어준다.
			Log += "CALLER\t: ";
			Log += function + " (";
			Log += file + ", ";
			Log += line + ")\n";
			Log += type + "\t: ";

			// 완성된 문자열을 합쳐준다.
			Log += std::string(Message) + "\n\n";

			// 사용후 해제한다.
			delete[] Message;
		}
		va_end(List); // List NULL 초기화

		// 해당 로그 데이터를 출력한다.
		Print(Log.c_str());

	}

	void Print(LPCSTR log)
	{
		switch (target)
		{
		case LogSystem::TARGET::ALL:
			
		case LogSystem::TARGET::CONSOLE:
		{

			if (target != TARGET::ALL)
				break;
		}

		case LogSystem::TARGET::FILE:
		{

			if (target != TARGET::ALL)
				break;
		}

		break;
		}

	}
};
