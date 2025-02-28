#include "ImGuiLayer.h"

#include "Application.h"
#include "OpenGLRender.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "glfw/glfw3.h"

namespace Sunset
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
		OnDetach();
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::StyleColorsDark();
		io.DisplaySize = ImVec2{1280, 720};
		BasicApp& app = BasicApp::Get();
		GLFWwindow* WinPtr = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(WinPtr, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		//ImGuiViewport* viewport = ImGui::GetMainViewport();
		//ImGui::SetNextWindowPos(viewport->Pos);
		//ImGui::SetNextWindowSize(viewport->Size);
		//ImGui::SetNextWindowViewport(viewport->ID);

		//window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
		//	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		//window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		//ImGui::Begin("DockSpace Demo", nullptr, window_flags);
		//ImGui::PopStyleVar(2);

		//// Création du DockSpace
		//ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		//ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

		//ImGui::End();

		bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Begin("Camera info");

		Camera* cam = BasicApp::Get().GetCam();
		ImGui::Text("Camera info:");
		std::string text = std::format("	Position : x:{}, y:{}, z:{}", cam->m_Position.x, cam->m_Position.y, cam->m_Position.z);
		ImGui::Text(text.c_str());
		text = std::format("	UpVector : x:{}, y:{}, z:{}", cam->m_UpVector.x, cam->m_UpVector.y, cam->m_UpVector.z);
		ImGui::Text(text.c_str());
		text = std::format("	ForwardVec : x:{}, y:{}, z:{}", cam->m_ForwardVector.x, cam->m_ForwardVector.y, cam->m_ForwardVector.z);
		ImGui::Text(text.c_str());
		text = std::format("	Rotation : roll:{}", cam->roll);
		float s8_min = 0;
		float s8_max = 360;
		ImGui::SliderScalar("Camera rotation", ImGuiDataType_Float, &(cam->roll), &s8_min, &s8_max);
		ImGui::Text(text.c_str());

		ImGui::End();

		ImGui::Begin("Log");
		if (ImGui::Button("Clear"))
		{
			Logger::Get().clear();
		}

		if (ImGui::BeginListBox("##Log", ImVec2(-FLT_MIN, -FLT_MIN)))
		{

			for (const auto& msg : Logger::Get())
			{
				ImGui::TextUnformatted(msg.c_str());
			}
			ImGui::EndListBox();
		}
		ImGui::End();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_currentcontext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_currentcontext);
		}
	}

}