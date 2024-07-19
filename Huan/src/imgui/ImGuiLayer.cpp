#include "HuanPCH.h"
#include "Huan/Core.h"
#include "ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "imgui.h"
#include "Events/EventDispatcher.h"
#include "Huan/Application.h"
#include "Huan/KeyCodes.h"
#include "util/Log.h"


namespace Huan
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();

		io.IniFilename = "imgui.ini";

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = HUAN_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = HUAN_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = HUAN_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = HUAN_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = HUAN_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = HUAN_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = HUAN_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = HUAN_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = HUAN_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = HUAN_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = HUAN_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = HUAN_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = HUAN_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = HUAN_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = HUAN_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = HUAN_KEY_A;
		io.KeyMap[ImGuiKey_C] = HUAN_KEY_C;
		io.KeyMap[ImGuiKey_V] = HUAN_KEY_V;
		io.KeyMap[ImGuiKey_X] = HUAN_KEY_X;
		io.KeyMap[ImGuiKey_Y] = HUAN_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = HUAN_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach()
	{
	}

	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application* app = Application::getInstance();
		io.DisplaySize = ImVec2(app->getWindow().getWidth(), app->getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = myTime > 0.0f ? (time - myTime) : (1.0f / 60.0f);
		myTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	/**
	 * handle those events could be pass
	 * @param e 
	 */
	void ImGuiLayer::onEvent(Event& e)
	{
		dispatcher.reset(e);
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleMouseMovedEvent));
		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleMouseButtonPressedEvent));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleMouseButtonReleasedEvent));
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleMouseScrolledEvent));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleKeyPressedEvent));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleKeyReleasedEvent));
		dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleKeyTypedEvent));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(ImGuiLayer::handleWindowResizeEvent));
	}

	bool ImGuiLayer::handleMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getX(), e.getY());
		return false;
	}

	bool ImGuiLayer::handleMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		HUAN_CLIENT_INFO(" ImGui: {0}", e.toString());
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::handleMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		HUAN_CLIENT_INFO(" ImGui: {0}", e.toString());
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::handleMouseScrolledEvent(MouseScrolledEvent& e)
	{
		HUAN_CLIENT_INFO(" ImGui: {0}", e.toString());
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.getXOffset();
		io.MouseWheel += e.getYOffset();

		return false;
	}

	bool ImGuiLayer::handleKeyPressedEvent(KeyPressedEvent& e)
	{
		printKeyName(e);
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[HUAN_KEY_LEFT_CONTROL] || io.KeysDown[HUAN_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[HUAN_KEY_LEFT_SHIFT] || io.KeysDown[HUAN_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[HUAN_KEY_LEFT_ALT] || io.KeysDown[HUAN_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[HUAN_KEY_LEFT_SUPER] || io.KeysDown[HUAN_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::handleKeyReleasedEvent(KeyReleasedEvent& e)
	{
		printKeyName(e);
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::handleKeyTypedEvent(KeyTypedEvent& e)
	{
		printKeyName(e);
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.getKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::handleWindowResizeEvent(WindowResizeEvent& e)
	{
		HUAN_CLIENT_INFO(" ImGui: {0}", e.toString());
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.getWidth(), e.getHeight());

		return false;
	}
	void ImGuiLayer::printKeyName(KeyEvent& e)
	{
		static auto keycodeMap = createKeycodeMap();  // Create map once and reuse it

		HUAN_CLIENT_TRACE(" ImGui: {0}: {1}", e.toString(), keycodeMap[e.getKeyCode()]);
	}
}
