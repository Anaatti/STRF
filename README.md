# STRF game library

The STRF library is a collection of useful functions and classes for games and any other graphical programs using OpenGL 2. The library uses some other libraries, including GLFW, GLEW and PNG, for windowing, input handling and other things.

The available functionality of the library is not very well documented and the code does not contain many comments as there have never been actual plans to publicly release the library. The reason is that there are certainly better game libraries and engines available than this one as STRF is not trying to compete with them, rather just work as a collection of useful stuff for the original creator of the library. However, as the library is released under the MIT license, you are free to learn from the library and copy just the useful parts.

The STRF library is not being worked on anymore as there is a newer version of the library using SDL2 instead of GLFW (not released anywhere yet).

## Usage

This library can be compiled into a shared or static library and has been tested to work on Windows and Linux. To compile the software, the external libraries **glew, glfw, opengl, glu, png** and **z** need to be available and linked. Note that this library has only been tested to work with the GLFW version 2.7 and not the new 3.0.

## Available functionality

The main functionality of this library include a very easy way to open an OpenGL window, load textures from BMP and PNG-files, load and control GLSL shaders, create FBOs, control FPS, draw text, take screenshots and offer a logging system. In addition, smaller useful functionalities are available for drawing and math for example.

You may find certain parts of this library highly useful such as texture and shader loading as those can be a real pain when using OpenGL. If you really want to learn this library, a good way is to read the random remarks below and look at the example programs.

### Random remarks

#### Opening a window

The library makes it very easy to query supported screen resolutions and open either a fullscreen, windowed or resizable OpenGL window. Using any OpenGL calls in the main program will work as expected. The library also provides easy means of drawing two dimensional objects at the borders of the screen to make it easy to support any aspect ratios.

#### Textures

The texture-class can load textures from BMP and PNG-files and from bitmaps located in the memory. The class can also store the file path or data used to load the texture. Originally the idea was to make it easy to reload the texture but the feature is not completely finished as there never was any need for that.

The library also provides a screenshot-functionality to save the screen buffer into a BMP-file.

#### Shaders

The shader-class can load shaders from GLSL-shader files and define uniform values for those. The class also provides an easy way to set those uniform values. In addition, there is a possibility to include a built-in random number generator for loaded shaders. Lastly, the library also defines two built-in shaders called basic\_shader, used with texturing, and color\_shader, used without textures.

#### FBOs

The fbo-class provides an easy way to draw into textures. There is also the older 'framebuffer'-functionality available that can copy the screen buffer into a texture although it should generally be a better idea to use FBOs instead.

#### Drawing text

The library contains a built-in monospace font that will be used when using the text drawing functions provided by the library. The small program that generates this font is located in the font-folder.

#### Logging

There is a logging system that mostly just wraps std::cout and std::cerr into a custom class. Doing this is probably silly, but originally the reason was to reduce the executable size of the program that is using this library. The thing is, that on Windows (using MinGW) including iostream grows the executable size by hundreds of kilobytes, so not having to include that, the file size could decrease by something like 90%. The sad part is that including something like fstream in the main program renders this idea completely useless. Luckily, this is not the only task of this custom logging class as it can also redirect all the program output into a log file in addition to the console.

#### The many wrapper functions

So, the library contains a lot of wrapper functions for numerous GLFW and GLU-functions. The GLFW-wrappers were quite necessary due to how OpenGL contexts work. The GLU-wrappers are there just to remove the requirement to include GLU in the main program, at least in the case you happen to need the certain GLU-functions that have wrappers.

## History

The STRF library was created by Antti Vainio and used in his various projects. The first version of this library was a collection of all the useful parts from the game [Strafe](https://www.anttivainio.net/strafe) and some extra stuff, which is where this library got its name from. The first project, this library saw use in, was the next game by Antti Vainio, [The Apocalyptic One Two](https://www.anttivainio.net/12). After that, the library has been used in his [demos](https://www.anttivainio.net/videos) and the various [music visualizers](https://www.anttivainio.net/music). Currently this library is being replaced by a new one that uses SDL2.
