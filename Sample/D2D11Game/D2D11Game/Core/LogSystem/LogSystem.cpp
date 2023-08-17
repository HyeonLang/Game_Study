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
		// ����� �α� �����͸� ������ string
		std::string	Log = "";

		// ���� ���� ������ ����
		va_list List = nullptr;

		// ���� ���� �������� ���� ��ġ�� �޴´�.
		va_start(List, format);
		{
			// vsprintf_s() : string�� size ��ŭ arg_format(����)�� arg_list(����)�� ���� ���ڿ��� ����� �ش�.
			size_t Size = _vscprintf(format.c_str(), List) + sizeof('\0');

			// ������� ũ�⸸ŭ �����Ҵ��� �޴´�.
			char* Message = new char[Size];

			// vsprintf_s() : string�� size ��ŭ arg_format(����)�� arg_list(����)�� ���� ���ڿ��� ����� �ش�.
			vsprintf_s(Message, Size, format.c_str(), List);

			// �ش� �α׸� ��� ȣ������ ������ �־��ش�.
			Log += "CALLER\t: ";
			Log += function + " (";
			Log += file + ", ";
			Log += line + ")\n";
			Log += type + "\t: ";

			// �ϼ��� ���ڿ��� �����ش�.
			Log += std::string(Message) + "\n\n";

			// ����� �����Ѵ�.
			delete[] Message;
		}
		va_end(List); // List NULL �ʱ�ȭ

		// �ش� �α� �����͸� ����Ѵ�.
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
