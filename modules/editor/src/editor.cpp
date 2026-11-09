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
    io.ConfigWindowsMoveFromTitleBarOnly = true;   // dragging inside a panel must not move it

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
    ImGui::Text("Viewport:         %d x %d", s.viewportW, s.viewportH);
    ImGui::Separator();
    ImGui::Checkbox("Show ImGui demo window", &m_showDemo);
    ImGui::End();

    if (m_showDemo) ImGui::ShowDemoWindow(&m_showDemo);
}

ViewportInput Editor::drawViewport(uint32_t sceneTexture, int& width, int& height) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    const ImVec2 size = ImGui::GetContentRegionAvail();
    width = static_cast<int> (size.x);
    height = static_cast<int> (size.y);

    if (sceneTexture && width > 0 && height > 0) {
        ImGui::Image((ImTextureID)(intptr_t)sceneTexture, size, ImVec2(0, 1), ImVec2(1, 0));
    }

    ViewportInput in;
    const ImGuiIO& io = ImGui::GetIO();
    const bool hovered = ImGui::IsWindowHovered();
    if (hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Middle)) m_dragging = true;
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Middle)) m_dragging = false;

    if (m_dragging) {
        in.orbit = !io.KeyShift;
        in.pan = io.KeyShift;
        in.dx = io.MouseDelta.x;
        in.dy = io.MouseDelta.y;
    }
    if (hovered) in.scroll = io.MouseWheel;

    ImGui::End();
    ImGui::PopStyleVar();
    return in;
}

void Editor::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
