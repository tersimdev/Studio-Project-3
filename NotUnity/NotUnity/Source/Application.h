#ifndef APPLICATION_H
#define APPLICATION_H

#include "Utility//Math//Stopwatch.h"

//forward declarations
struct GLFWwindow;
class Application
{
public:
	Application();
	~Application();

	void Create();
	void Run();
	void Exit();

	int GetWindowHeight();
	int GetWindowWidth();
	int GetWindowHalfHeight();
	int GetWindowHalfWidth();
	
private:
	int m_window_width = 1280;
	int m_window_height = m_window_width / 16 * 9;
	
	const unsigned char FPS = 60;
	const double frameTime = 1000.0 / FPS;

	GLFWwindow* m_window;
	Stopwatch m_timer;

	static bool IsKeyPressed(unsigned short key);
	bool ShouldQuit();

	void CheckForInput();
	void InputReset();

	static void error_callback(int error, const char* description);
	static void resize_callback(GLFWwindow* window, int w, int h);
	static void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif