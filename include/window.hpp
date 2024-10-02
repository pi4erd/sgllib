#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <tuple>


class Window {
public:
    Window(std::string title, const std::vector<std::tuple<int, int>> &hints);
    virtual ~Window();

    bool shouldClose(void) { return glfwWindowShouldClose(window); }
    void close(void) { glfwSetWindowShouldClose(window, true); }
    void pollEvents(void) { glfwPollEvents(); }
    void swapBuffers(void) { glfwSwapBuffers(window); }

    void toggleFullscreen() {
        if(!fullscreen) {
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            int width, height, xpos, ypos;
            glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

            glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, GLFW_DONT_CARE);
            fullscreen = true;
        } else {
            glfwSetWindowMonitor(window, nullptr, 0, 0, 1280, 720, GLFW_DONT_CARE);
            fullscreen = false;
        }
    }

    int width, height;

public: // abstracts
    virtual void render(double delta) = 0;
    virtual void update(double delta) = 0;

protected: // Virtuals
    virtual void mouseScroll(double dx, double dy) {
        (void)dx, (void)dy;
    }
    virtual void resize(int width, int height) {
        this->width = width;
        this->height = height;
    }
    virtual void keyboardCallback(int key, int action, int scancode, int mod) {
        (void)key;
        (void)action;
        (void)scancode;
        (void)mod;
    }
    virtual void mouseButton(int key, int action, int mod) {
        (void)key;
        (void)action;
        (void)mod;
    }
    GLFWwindow *getWindow(void) { return window; }

private:
    bool fullscreen = false;

    GLFWwindow *window;
};
