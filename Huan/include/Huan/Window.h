#pragma once
#include "HuanPCH.h"
#include "Core.h"
#include "Events/Event.h"

namespace Huan
{	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(std::string title = "Huan Engine",
		            unsigned int width = 1280, unsigned int height = 720)
			: title(std::move(title)), width(width), height(height)
		{
		}
	};

	class HUAN_API Window
	{
	public:
		using eventCallbackFunc = std::function<void(Event&)>;
		virtual ~Window() {};

		virtual void* getNativeWindow() const = 0;
		virtual void onUpdate() = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const eventCallbackFunc& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};
}
