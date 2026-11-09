#include <qs/editor/editor.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace qs {

bool Editor::init(Window &window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // panels can snap together
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window.handle(), true)) return false;
    if (!ImGui_ImplOpenGL3_Init("#version 450")) return false;

    m_initialized = true;
    return true;
}

Editor::~Editor() {
    if (!m_initialized) return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Editor::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // One dockspace over the whole window. PassthruCentralNode keeps the middle
    // transparent, so the 3D scene will show through there later.
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void Editor::drawStats(const FrameStats& s) {
    ImGui::Begin("Stats");
    ImGui::Text("Frame: %.2f ms (%.0f FPS)", s.frameMs, ImGui::GetIO().Framerate);
    ImGui::Separator();
    ImGui::Text("Steps this frame: %d", s.stepsThisFrame);
    ImGui::Text("Total steps:      %ld", s.totalSteps);
    ImGui::Text("Simulated time:   %.2f s", s.simTime);
    ImGui::Text("Alpha:            %.3f", s.alpha);
    ImGui::Separator();
    ImGui::Checkbox("Show ImGui demo window", &m_showDemo);
    ImGui::End();

    if (m_showDemo) ImGui::ShowDemoWindow(&m_showDemo);
}

void Editor::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
