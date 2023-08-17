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
		const std::string type,		// 해당 로그의 타입(INFO, WARNGIN, ERROR)
		const std::string function, // 해당 로그를 호출한 함수의 이름 __FUNCTION__을 사용하여 표시
		const std::string file,		// 해당 로그를 호출한 파일의 경로 __FILE__를 사용하여 표시
		const std::string line,		// 해당 로그를 호출한 줄 번호 __LINE__ 사용하여 표시
		const std::string format,
		...
	);
};

