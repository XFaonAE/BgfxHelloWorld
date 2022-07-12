#include <GLFW/glfw3.h> // We use this library as our desktop window managing system! It's what will create a window for us.

// These are libraries that contain bits and peices or BGFX.
#include <bgfx/bgfx.h>
#include <bgfx/platform.h> // This extends BGFX even more to connect platform dependent code to BGFX.
#include <bx/bx.h> // This library contains the base files for BGFX.

// This defines a property based on the platform, when either one is defined, GLFW allows us to access that windows specific os native window pointer.
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
// THE NEXT LINE MUST COME AFTER DEFINING THE ABOVE VARS, OR FUNCTIONS WILL NOT BE ACCESSIBLE.
#include <GLFW/glfw3native.h> // This library extends GLFW to add ways to access native window handles, like on windows, the hwnd, and linux the x11 pointer, etc...

int main() {
    // This will initialize the GLFW library
    if (!glfwInit()) {
        return -1;
    }

    // This will initialize BGFX
    bgfx::init();

    // Construct thr window with the constructor function
    GLFWwindow * window = glfwCreateWindow(640, 480, "BGFX Hello World With Comments!", nullptr, nullptr);

    bgfx::renderFrame();
    bgfx::Init init; // THis init tool will be used to store our native window handles and data.

#if BX_PLATFORM_LINUX
    init.platformData.ndt = glfwGetX11Display();
    init.platformData.nwh = (void*)glfwGetX11Window(window);
#elif BX_PLATFORM_WINDOWS
    init.platformData.nwh = glfwGetWin32Window(window);
#elif BX_PLATFORM_OSX
    init.platformData.nwh = glfwGetCocoaWindow(window);
#endif

    int width;
    int height;

    glfwGetWindowSize(window, &width, &height);

    init.resolution.width = width;
    init.resolution.height = height;
    init.resolution.reset = BGFX_RESET_VSYNC; // This will make the window vsync. if you have a 60 hertz display, bgfx will try to push out frames at 60 fps.

    // Check if the init tool was successful.
//    if (!bgfx::init(init)) {
//        return 1;
//    }

    const bgfx::ViewId kClearView = 0; // This is the view that will be used to clear the screen. This is our viewport id, 0 is the default viewport.

    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR); // This will clear the screen with a color.
    bgfx::setViewRect(kClearView, 0, 0, width, height); // This will tell BGFX where to render stuff.

    // This is the window event loop. It will run until the window is closed.
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int oldWidth = width;
        int oldHeight = height;

        // This is if the window size changed
        if (width != oldWidth || height != oldHeight) {
            bgfx::reset(width, height, BGFX_RESET_VSYNC);
            bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
        }

        // THis is a useless call to make sure that the default view is empty and not rendering anything.
        bgfx::touch(kClearView);

        // This is where we render our stuff.
        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 0, 0x0f, "Hello World!");

        // THis is where we render the frame
        bgfx::frame();
    }

    // This will destroy the window, don't worry this won't run right away, the while loop above will prevent this from running unless the window is closed.
    bgfx::shutdown();
    glfwTerminate();
    return 0;
}