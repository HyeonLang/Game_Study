#pragma once
// Context.h

#include"stdafx.h"
#include"Subsystem/ISubsystem.h"

class Context final
{
public:
	Context() = default;
	~Context()
	{
		for (auto iter = subsystems.rbegin(); iter != subsystems.rend(); iter++)
			SAFE_DELETE(*iter);

	}

	const bool InitializeSubsystems()
	{
		bool result = true;

		for (const auto& subsystem : subsystems)
			if (subsystem->Initialize() == false)
				result = false;

		return result;
	}

	template<typename T>
	const T* const RegisterSubsystem()
	{
		static_assert(std::is_base_of<ISubsystem, T>::value == true, "Provided type does not implement ISubsystem");

		subsystems.emplace_back(new T(this));

		return static_cast<T*>(subsystems.back());
	}

	template<typename T>
	T* const GetSubsystem()
	{
		static_assert(std::is_base_of<ISubsystem, T>::value == true, "Provided type does not implement ISubsystem");

		for (const auto& subsystem : subsystems)
			if (typeid(T) == typeid(*subsystem))
				return static_cast<T*>(subsystem);

		return nullptr;
	}

	void UpdateSubsystems()
	{
		for (const auto& subsystem : subsystems)
			subsystem->Update();
	}

private:
	std::vector<ISubsystem*> subsystems;
};