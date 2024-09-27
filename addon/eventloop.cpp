#include <GLFW/glfw3.h>
#include <eventloop.hpp>

void EventLoop::run(VsyncInterval vsyncInterval) {
    glfwSwapInterval((int)vsyncInterval);

    double prevTime = glfwGetTime();

    while(!app->shouldClose()) {
        double time = glfwGetTime();
        double delta = time - prevTime;
        prevTime = time;

        app->pollEvents();

        app->update(delta);
        app->render(delta);
    }
}
