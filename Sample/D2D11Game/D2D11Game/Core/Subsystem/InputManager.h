#pragma once
#include "ISubsystem.h"

enum KEY_STATE : uint
{
	KEY_UNKNOWN = 0,
	KEY_FREE = 1U << 0,
	KEY_DOWN = 1U << 1,
	KEY_UP = 1U << 2,
	KEY_HOLD = 1U << 3
};

enum MOUSE_BUTTON
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE
};


class InputManager final : public ISubsystem
{
public:
	InputManager(Context* const context);
	~InputManager();

	virtual bool Initialize() override;
	virtual void Update() override;

	const POINT& GetMousePosition() const { return mouse_position; }

	const bool& GetKeyState(const BYTE& key, const uint& states) const { return key_state[key] & states; }


	const KEY_STATE& GetMouseState(const MOUSE_BUTTON& button) const { return mouse_state[button]; }

	const bool& IsKeyFREE(const BYTE& key) { return key_state[key] == KEY_FREE; }
	const bool& IsKeyDown(const BYTE& key) { return key_state[key] == KEY_DOWN; }
	const bool& IsKeyUP(const BYTE& key) { return key_state[key] == KEY_UP; }
	const bool& IsKeyHold(const BYTE& key) { return key_state[key] == KEY_HOLD; }

public:
	LPDIRECTINPUT8 direct_input_device = nullptr;
	LPDIRECTINPUTDEVICE8 key_device = nullptr;
	LPDIRECTINPUTDEVICE8 mouse_device = nullptr;

	BYTE input_key_state[256];
	DIMOUSESTATE input_mouse_state;

	KEY_STATE key_state[256];
	KEY_STATE mouse_state[3];
	POINT mouse_position;
};

