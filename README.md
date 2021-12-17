# Mildly Annoyed Nth Year Students!
The game is an Aalto themed spin-off on the original Angry Birds game, where instead of birds, the player hurls Aalto students from different guilds. The goal of the game is to destroy the fuksis (first-year-students) hiding in the fort, but without destroying any beer bottles that might be in the level.

# Group
- Tommi Korpelainen
- Aleksi Rintanen
- Ilari Tulkki
- Joonas Palmulaakso

# Building the project
1. Make sure CMake is installed, and added to PATH. You can verify this with `cmake --version`.
(refer to [Installing CMake](https://cmake.org/install/))

2. Navigate to the root directory of the project, or specify it in the next step with `-S <path-to-dir>`

3. Generate a build system with CMake, for example `cmake -S . -B build`. Additionally, you may need to provide the preferred generator, for example `cmake -S . -B build -G "MinGW Makefiles"` (listed in the CMake documentation in [cmake-generators(7)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html))

4. Build the project with `cmake --build build`

For single-configuration generators like Make, this will build the project in release mode unless specified with `-D CMAKE_BUILD_TYPE=Debug`. For generators like Visual Studio, this is instead specified with `--config` in step 4. and defaults to `Debug`

5. Make sure that when running the application, you run it from the output
folder (build/), and not the project folder (angry-birds-group-4/). This way,
relative file paths used by the application will point to the correct data/ folder.

(It’s not a huge problem, but levels will get saved to data/ in the project folder,
which isn’t originally intended)

### SFML dependencies (Linux)
SFML depends on a few other libraries that must be installed.
On Windows and macOS, all the required dependencies are provided alongside SFML.

On Linux, make sure to install these before building:

- freetype
- x11
- xrandr
- udev
- opengl
- flac
- ogg
- vorbis
- vorbisenc
- vorbisfile
- openal
- pthread

The exact name of the packages may vary from distribution to distribution. Once those packages are installed, don't forget to install their development headers as well.


# Playing

For more instructions, take a look at doc/Project_Documentation.pdf

Game:
Aim and shoot the cannon with left mouse click, activate abilities with right mouse click.
Cannon power is based on mouse distance to the cannon.
Zoom with mouse scroll, and move the camera with middle mouse click.
Destroy all Fuksis to win the level. If you run out of Teekkaris, you lose.
To get full points, try to finish a level with as few Teekkari as possible. All Teekkaris left will give large extra points.

Editor:
Select an object from the list by clicking. Left click to place object, right click to delete.
Objects can be dragged inside the level. Arrow up and arrow down rotate the object.
Add Teekkaris by clicking them in the list. This will add them to the sidebar on the left.
Click them on the left sidebar to remove.
