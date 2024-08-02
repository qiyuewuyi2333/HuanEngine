#include "HuanPCH.h"
#include "Huan/Core.h"
#include "ImGui/ImGuiLayer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
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
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		Application::setImGuiContext(ImGui::CreateContext());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application* app = Application::getInstance();
		GLFWwindow* window = static_cast<GLFWwindow*>(app->getWindow().getNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	// void ImGuiLayer::onUpdate()
	// {
	// 	ImGuiIO& io = ImGui::GetIO();
	// 	Application* app = Application::getInstance();
	// 	io.DisplaySize = ImVec2(app->getWindow().getWidth(), app->getWindow().getHeight());
	//
	// 	float time = (float)glfwGetTime();
	// 	io.DeltaTime = myTime > 0.0f ? (time - myTime) : (1.0f / 60.0f);
	// 	myTime = time;
	//
	// 	ImGui_ImplOpenGL3_NewFrame();
	// 	ImGui::NewFrame();
	//
	// 	static bool show = true;
	// 	ImGui::ShowDemoWindow(&show);
	//
	// 	ImGui::Render();
	// 	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// }

	void ImGuiLayer::onImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application* app = Application::getInstance();
		io.DisplaySize = ImVec2(static_cast<float>(app->getWindow().getWidth()), static_cast<float>(app->getWindow().getHeight()));

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
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
