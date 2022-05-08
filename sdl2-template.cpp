#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#ifdef _DEBUG
#pragma comment(lib, "SDL2d.lib")
#pragma comment(lib, "SDL2maind.lib")
#else
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#endif
#pragma comment(lib, "SDL2_image.lib")

#pragma comment(lib, "glu32.lib")    // OpenGL Utility library
#pragma comment(lib, "opengl32.lib") // Microsoft OpenGL library

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    int windowWidth = 1280;
    int windowHeight = 720;

    const char *glsl_version = "#version 100";

    // Tell SDL2 what to have in the OpenGL context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Tell SDL2 to make a window with an OpenGL context.
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow("SDL2 Template",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          windowWidth, windowHeight, window_flags);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        fprintf(stderr, "Failed to initialize WebGL context!\n");
        return 1;
    }
    SDL_GL_SetSwapInterval(1); // Enable vsync
    SDL_GL_MakeCurrent(window, glContext);

    // Handle the event loop.
    bool done = false;
    while (!done)
    {
        // Process all events for the current frame.
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
            }

            else if (e.type == SDL_WINDOWEVENT)
            {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    windowWidth = e.window.data1;
                    windowHeight = e.window.data2;
                }
            }

            else if (e.type == SDL_QUIT)
            {
                done = true;
            }

            else
            {
                // This is an unhandled event.
            }
        }

        // Leave the loop if we're done.
        if (done)
            break;

        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        // Set up OpenGL drawing commands.
        glViewport(0, 0, (int)windowWidth, (int)windowHeight);

        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glEnd();

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}
