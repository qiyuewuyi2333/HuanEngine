#pragma once

#include "Huan/Window.h"

namespace Huan
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		void onUpdate() override;
		unsigned int getWidth() const override { return myData.width; }
		unsigned int getHeight() const override { return myData.height; }

		void setEventCallback(const eventCallbackFunc& callback) override { myData.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

	private:
		GLFWwindow* myWindow = nullptr;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
			eventCallbackFunc eventCallback;
		};
		WindowData myData;
	};
}