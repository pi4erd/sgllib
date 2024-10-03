#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <eventloop.hpp>
#include <memory>
#include <window.hpp>

class App : public Window {
public:
    App() : Window("My app", {}) {
        glClearColor(1.0, 0.0, 1.0, 1.0);

        glfwSetWindowSize(getWindow(), 800, 600);
    }

protected:
    void render(double delta) override {
        glClear(GL_COLOR_BUFFER_BIT);

        swapBuffers();
    }

    void update(double delta) override {

    }
};

int main(void) {
    EventLoop event_loop(std::make_unique<App>());

    event_loop.run();
}
