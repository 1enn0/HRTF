/*
simple test for openal 3d-audio
===============================

some code taken from "thecplusplusguy" on youtube.com:
https://www.youtube.com/watch?v=tmVRpNFP9ys


keyboard shortcuts
==================
[1]         starting playback
[space]     stopping playback

[left]      move source in negative x direction
[right]     move source in positive x direction
[down]      move source in posti z direction
[up]        move source in positive z direction
[a]         move source in negative y direction
[q]         move source in positive y direction


initial values (xyz)
====================

source   position:      ( 0, 0, -5 )
listener position:      ( 0, 0,  0 )
listener orientation:   ( 0, 0, -1 ) (facing negative z-axis)
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <oalplus/al.hpp>
#include <oalplus/all.hpp>
#include <oalplus/alut.hpp>
#include <SDL/SDL.h>

int main (int argc, char** argv)
{
    // open the default device
    oalplus::Device device;

    // create a context using the device and make it current
    oalplus::CurrentContext context(device,oalplus::ContextAttribs().Add(oalplus::ContextAttrib::MonoSources, 1).Get());

    // create an instance of ALUT
    oalplus::ALUtilityToolkit alut(false, argc, argv);

    // create a listener and set its position, velocity and orientation
    oalplus::Listener listener;
    listener.Position(0.0f, 0.0f, 0.0f);
    listener.Velocity(0.0f, 0.0f, 0.0f);
    // orientation:     (at_x, at_y,  at_z, up_x, up_y, up_z)
    listener.Orientation(0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);


    // create and configure source 1
    oalplus::Buffer buffer1 = alut.CreateBufferFromFile("/home/lenno/openal_sandbox/pn.wav"); // you will have to edit the path here
    oalplus::Source source1;
    source1.Buffer(buffer1);
    source1.Looping(true);


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    SDL_Event event;
    Uint32 start;
    bool running = true;

    // create vector of six bools for each orientation: left, right, forward, backward, up, down
    // each one will be set to "true" if corresponding button is being pressed
    bool b[6] = {0, 0, 0, 0, 0, 0};

    // initial values for source
    float x = 0.0f, y= 0.0f, z = -5.0f;
    std::cout << "x: " << x << "   z: " << z << "   y: " << y << std::endl;


    while(running){
        start = SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                running=false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case SDLK_LEFT:
                    b[0] = true;
                    break;
                case SDLK_RIGHT:
                    b[1] = true;
                    break;
                case SDLK_UP:
                    b[2] = true;
                    break;
                case SDLK_DOWN:
                    b[3] = true;
                    break;
                case SDLK_q:
                    b[4] = true; // key q -> up
                    break;
                case SDLK_a: // key a -> down
                    b[5] = true;
                    break;
                case SDLK_1:
                    source1.Play();
                    break;
                case SDLK_SPACE:
                    source1.Pause();
                    break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym){
                case SDLK_LEFT:
                    b[0] = false;
                    break;
                case SDLK_RIGHT:
                    b[1] = false;
                    break;
                case SDLK_UP:
                    b[2] = false;
                    break;
                case SDLK_DOWN:
                    b[3] = false;
                    break;
                case SDLK_q:
                    b[4] = false; // key q -> up
                    break;
                case SDLK_a: // key a -> down
                    b[5] = false;
                    break;
                }
                break;
            }
        }

        // step by which direction values are incremented/decremented
        float step = 0.3f;

        if(b[0]){
            x -= step;
        }
        if(b[1]){
            x += step;
        }
        if(b[2]){
            z -= step;
        }
        if(b[3]){
            z += step;
        }
        if(b[4]){
            y += step;
        }
        if(b[5]){
            y -= step;
        }

        std::cout << "source position   " << "x: " << x << "   z: " << z << "   y: " << y << std::endl;

        // update position
        source1.Position(x, y, z);

        if(1000/30.0 > SDL_GetTicks() - start)
            SDL_Delay(1000/30.0 - (SDL_GetTicks() - start));

    }

    return 0;
}
