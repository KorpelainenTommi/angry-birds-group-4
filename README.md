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


# Repository organization
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Project Implementation 
You must use git repository for the work on the project, making frequent enough commits so 
that the project group (and course staff) can follow the progress.

The completed project work will be demonstrated to the group's advisor at a demo session. 
The final demonstrations are arranged on week 50. After the final demonstrations project group 
evaluates another project, and self-evaluates own project. In addition, project members will 
give a confidential individual assessment of each group member

The course staff should be able to easily compile the project work using makefile and related 
instructions provided in the git repository. The final output should be in the **master branch** of the git repository.

# Working practices
Each project group is assigned an advisor from the project teaching personnel. 
There will be a dedicated Teams channel for each project topic to facilitate discussion between 
the groups in the same topic and the advisor. 

**The group should meet weekly.** The weekly meeting does not need to be long if there are no special issues 
to discuss, and can be taken remotely as voice/video chat on the group Teams channel (or Zoom or other similar tool), 
preferably at a regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project repository in the `Meeting-notes.md` file. 
    * The commits within the week should have some commit messages referring to the meeting notes so 
      that the project advisor can follow the progress.  
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple of members should be present in each meeting. 
> Regular absence from meetings will affect in individual evaluation.

# Source code documentation
It is strongly recommended to use Doxygen to document your source code.
Please go over the *Project Guidelines* for details.

# TODOs (Date)
You can create a list of TODOs in this file.
The recommended format is:
- Complete class implementation **foo**. Assigned to \<Member 1\>
- Test ...
