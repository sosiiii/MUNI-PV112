// ################################################################################
// Common Framework for Computer Graphics Courses at FI MUNI.
//
// Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
// All rights reserved.
// ################################################################################

#include "application.hpp"

// ----------------------------------------------------------------------------
// Constructors & Destructors
// ----------------------------------------------------------------------------

Application::Application(int initial_width, int initial_height, std::vector<std::string> arguments) : PV112Application(initial_width, initial_height, arguments) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Reserved for future lesson.
    glCreateVertexArrays(1, &vao);

    compile_shaders();
}

Application::~Application() {
    glDeleteVertexArrays(1, &vao);
    delete_shaders();
}

// ----------------------------------------------------------------------------
// Methods
// ----------------------------------------------------------------------------

void Application::delete_shaders() {
    // Task 2.2 Delete the program.
}

void Application::compile_shaders() {
    delete_shaders();

    // Task 2.1: Compile vertex & fragment shaders.
    // Help: - There is a variable 'lecture_shaders_path' that contains path to the folder with shaders.
    //       - Use the helper function load_file from utilities to load the contents of a file into a string.
    //       - Method data() callable on std::string type can give you raw C99 pointer that OpenGL takes as an input.
    //         Example: const std::string vertex_shader_string = load_file(lecture_shaders_path / "main.vert");
    //                  const char* vertex_shader_source = vertex_shader_string.data();
    //       - Create a function so that you don't need to copy paste the code for both vertex and the fragment shaders.
    GLuint vshader = load_shader(GL_VERTEX_SHADER, "main.vert");
    GLuint fshader = load_shader(GL_FRAGMENT_SHADER, "main.frag");
    // Task 2.2: Link the shaders to create a program. Do not forget to delete shaders after linking.
    program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
   
    glLinkProgram(program);

    glDetachShader(program, vshader);
    glDetachShader(program, fshader);

    glDeleteShader(vshader);
    glDeleteShader(fshader);

    // Task 2.4: Link the second set of shaders.

    GLuint vshader2 = load_shader(GL_VERTEX_SHADER, "my.vert");
    GLuint fshader2 = load_shader(GL_FRAGMENT_SHADER, "my.frag");

    program2 = glCreateProgram();

    glAttachShader(program2, vshader2);
    glAttachShader(program2, fshader2);

    glLinkProgram(program2);

    glDetachShader(program2, vshader2);
    glDetachShader(program2, fshader2);
    glDeleteShader(vshader2);
    glDeleteShader(fshader2);
    
    std::cout << "Shaders are reloaded." << std::endl;
}
void Application::update(float delta) {}

void Application::render() {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);

    // Task 2.3: Use the compiled program for drawing.
    // Task 2.4: Use glViewport to render two triangles side by side.
    glUseProgram(ui_reverse_sides ? program : program2);
    glViewport(0,0,width*0.5,height);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Task 2.4: Use the new program to draw the second triangle.

    glViewport(width*0.5,0,width*0.5,height);
    glUseProgram(ui_reverse_sides ? program2 : program);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}
GLuint Application::load_shader(GLenum type, std::string name){
    GLuint shader = glCreateShader(type);
    const std::string shader_string = load_file(lecture_shaders_path / name);
    const char* shader_source = shader_string.data();
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    return shader;
}


// ----------------------------------------------------------------------------
// Input Events
// ----------------------------------------------------------------------------

void Application::render_ui() {
    const float unit = ImGui::GetFontSize();

    ImGui::Begin("Configuration", nullptr, ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowSize(ImVec2(10 * unit, 20 * unit));
    ImGui::SetWindowPos(ImVec2(2 * unit, 2 * unit));
    ImGui::RadioButton("Default", &ui_reverse_sides, 0);
    ImGui::RadioButton("Switch sides", &ui_reverse_sides, 1);
    ImGui::End();
}

void Application::on_resize(int width, int height) {
    // Calls the default implementation to set the class variables.
    IApplication::on_resize(width, height);
}

void Application::on_mouse_move(double x, double y) {}

void Application::on_mouse_button(int button, int action, int mods) {}

void Application::on_key_pressed(int key, int scancode, int action, int mods) {
    // Calls the default implementation that invokes compile_shaders when 'R key is hit.
    PV112Application::on_key_pressed(key, scancode, action, mods);

    // Task 2.5: Switch the order of used programs for drawing on pressing keyboard key of your choice.
    //           Use for example if(action == GLFW_PRESS && key == GLFW_KEY_S){} to decide when the switch happens.
    //           For the interoperation of UI and Inputs use the same variable used in UI `ui_reverse_sides`
    if(action == GLFW_PRESS && key == GLFW_KEY_S){
        ui_reverse_sides = !ui_reverse_sides;
    }
}
