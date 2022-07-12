#include <GLFW/glfw3.h> // We use this library as our desktop window managing system! Its what will create a window for us.

int main() {
    // This will initialize the GLFW library
    glfwInit();

    // Construct thr window with the constructor function
    GLFWwindow * window = glfwCreateWindow(640, 480, "BGFX Hello World With Comments!", nullptr, nullptr);

    // This is the window event loop. It will run until the window is closed.
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // This will destroy the window, don't worry this won't run right away, the while loop above will prevent this from running unless the window is closed.
    glfwTerminate();
    return 0;
}