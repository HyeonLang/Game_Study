#pragma once

namespace LogSystem
{
	enum class TARGET
	{
		ALL,
		CONSOLE,
		FILE
	};

	extern void SetTarget(const TARGET target);

	extern void SetLog
	(
		const std::string type,		// �ش� �α��� Ÿ��(INFO, WARNGIN, ERROR)
		const std::string function, // �ش� �α׸� ȣ���� �Լ��� �̸� __FUNCTION__�� ����Ͽ� ǥ��
		const std::string file,		// �ش� �α׸� ȣ���� ������ ��� __FILE__�� ����Ͽ� ǥ��
		const std::string line,		// �ش� �α׸� ȣ���� �� ��ȣ __LINE__ ����Ͽ� ǥ��
		const std::string format,
		...
	);
};

