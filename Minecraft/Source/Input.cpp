#include "Input.h"
#include "Vector2D.h"

#include <vector>

namespace MC {

	struct KeyEvent {
		int m_Key, m_Action;
		KeyEvent(int key, int action)
			: m_Key(key), m_Action(action)
		{

		}
	};

	struct MouseEvent {
		int m_Button, m_Action;
		MouseEvent(int button, int action)
			: m_Button(button), m_Action(action)
		{

		}
	};

	static std::vector<KeyEvent> keyEvents;
	static std::vector<MouseEvent> mouseEvents;
	static Math::Vector2D mousePosition;

	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keyEvents.push_back(KeyEvent(key, action));
	}

	void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		mouseEvents.push_back(MouseEvent(button, action));
	}

	void Input::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePosition.x = (float) xpos;
		mousePosition.y = (float) ypos;
	}

	void Input::ProcessEvents(KeyboardInput& keyIn, MouseInput& mouseIn)
	{
		for (unsigned int i = 0; i < keyEvents.size(); i++) {
			if (keyIn.m_ShouldReceiveInput) {
				if (keyEvents.at(i).m_Action == GLFW_PRESS) {
					keyIn.m_KeysPressed.at(keyEvents.at(i).m_Key) = true;
					keyIn.m_KeysHeld.at(keyEvents.at(i).m_Key) = false;
					keyIn.m_KeysReleased.at(keyEvents.at(i).m_Key) = false;
				}
				else if (keyEvents[i].m_Action == GLFW_RELEASE) {
					keyIn.m_KeysPressed[keyEvents[i].m_Key] = false;
					keyIn.m_KeysHeld[keyEvents[i].m_Key] = false;
					keyIn.m_KeysReleased[keyEvents[i].m_Key] = true;
				}
			}
		}
		keyEvents.clear();
		for (unsigned int i = 0; i < mouseEvents.size(); i++) {
			if (mouseIn.m_ShouldReceiveInput) {
				if (mouseEvents.at(i).m_Action == GLFW_PRESS) {
					mouseIn.m_ButtonClicked.at(mouseEvents.at(i).m_Button) = true;
					mouseIn.m_ButtonHeld.at(mouseEvents.at(i).m_Button) = false;
					mouseIn.m_ButtonReleased.at(mouseEvents.at(i).m_Button) = false;
				}
				else if (mouseEvents.at(i).m_Action == GLFW_RELEASE) {
					mouseIn.m_ButtonClicked.at(mouseEvents.at(i).m_Button) = false;
					mouseIn.m_ButtonHeld.at(mouseEvents.at(i).m_Button) = false;
					mouseIn.m_ButtonReleased.at(mouseEvents.at(i).m_Button) = true;
				}
			}
		}
		if (mouseIn.m_ShouldReceiveInput) {
			mouseIn.m_MouseX = mousePosition.x;
			mouseIn.m_MouseY = mousePosition.y;
		}
		mouseEvents.clear();
	}

	void Input::Flush(KeyboardInput& keyIn, MouseInput& mouseIn)
	{
		for (int i = 0; i < KEYBOARD_KEYS_SIZE; i++) {
			if (keyIn.m_KeysPressed.at(i)) {
				keyIn.m_KeysPressed.at(i) = false;
				keyIn.m_KeysHeld.at(i) = true;
			}
			if (keyIn.m_KeysReleased.at(i)) {
				keyIn.m_KeysReleased.at(i) = false;
			}
		}

		for (int i = 0; i < MOUSE_BUTTONS_SIZE; i++) {
			if (mouseIn.m_ButtonClicked.at(i)) {
				mouseIn.m_ButtonClicked.at(i) = false;
				mouseIn.m_ButtonHeld.at(i) = true;
			}
			if (mouseIn.m_ButtonReleased.at(i)) {
				mouseIn.m_ButtonReleased.at(i) = false;
			}
		}
	}
}