#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Random.h"
#include "Title.h"

int main(void) {

    glfwInit();

    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 700, "GUI RPS Game", NULL, NULL);

    if (!window) {

        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImFont* font = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 18.0f);

    RPS* rps = new RPS();
    Title* title = new Title();

    char* windowTitle = (char*)"";

    char* com = (char*)"";
    char* user = (char*)"";

    char* message = (char*)"";
    char* won = (char*)"";

    static bool reset = true;
    static bool showResult = false;

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.30f, 0.30f, 0.30f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main code goes here

        if (ImGui::BeginMainMenuBar()) {

            if (ImGui::BeginMenu("Game")) {

                if (ImGui::MenuItem("Close")) { return 0; }

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (reset == true) {

            user = (char*)"";
            com = rps -> random();
            windowTitle = title -> random();
            reset = false;
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 1.3f));

        ImGui::Begin("Choice", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Make your choice...");

        if (ImGui::Button("Rock"))
            user = (char*)"Rock";

        if (ImGui::Button("Paper"))
            user = (char*)"Paper";

        if (ImGui::Button("Scissors"))
            user = (char*)"Scissors";

        ImGui::End();

        if (strcmp(user, com) == 0) {

            message = (char*)"Its a draw!";
            won = (char*)"Nobody won!";
            showResult = true;
        }
        else if (strcmp(user, "Rock") == 0 && strcmp(com, "Scissors") == 0) {

            message = (char*)"You chose Rock and computer chose Scissors";
            won = (char*)"You won!";
            showResult = true;
        }
        else if (strcmp(user, "Paper") == 0 && strcmp(com, "Rock") == 0) {

            message = (char*)"You chose Paper and computer chose Scissors";
            won = (char*)"You won!";
            showResult = true;
        }
        else if (strcmp(user, "Scissors") == 0 && strcmp(com, "Paper") == 0) {

            message = (char*)"You chose Scissors and computer chose Paper";
            won = (char*)"You won!";
            showResult = true;
        }
        else if (strcmp(com, "Rock") == 0 && strcmp(user, "Scissors") == 0) {

            message = (char*)"You chose Scissors and computer chose Rock";
            won = (char*)"Computer won!";
            showResult = true;
        }
        else if (strcmp(com, "Paper") == 0 && strcmp(user, "Rock") == 0) {

            message = (char*)"You chose Rock and computer chose Paper";
            won = (char*)"Computer won!";
            showResult = true;
        }
        else if (strcmp(com, "Scissors") == 0 && strcmp(user, "Paper") == 0) {

            message = (char*)"You chose Paper and computer chose Scissors";
            won = (char*)"Computer won!";
            showResult = true;
        }

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.0f));

        if (showResult == true) {

            ImGui::Begin(windowTitle, NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::Text(message);
            ImGui::Text(won);

            if (ImGui::Button("Reset")) {

                reset = true;
                showResult = false;
            }

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    delete rps;
    delete title;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}