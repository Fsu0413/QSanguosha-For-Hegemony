Open Source Sanguosha
==========

Lisense
------------
###Code
This game is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3.0
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

See the LICENSE file for more details.

###Material
Our Materials are under the terms of the Creative Commons
Attribution-NonCommercial-NoDerivatives 4.0 International (CC
BY-NC-ND 4.0)

**You are free to:**

Share — copy and redistribute the material in any medium or format

**Under the following terms:**

Attribution — You must give appropriate credit, provide a link to
the license, and indicate if changes were made. You may do so in
any reasonable manner, but not in any way that suggests the licensor
endorses you or your use.

NonCommercial — You may not use the material for commercial purposes.

NoDerivatives — If you remix, transform, or build upon the material,
you may not distribute the modified material.

See the CC BY-NC-ND 4.0 file for more details.

Introduction (By Moligaloo)
----------

Sanguosha is both a popular board game and online game,
this project try to clone the Sanguosha online version.
The whole project is written in C++,
using Qt's graphics view framework as the game engine.
I've tried many other open source game engines,
such as SDL, HGE, Clanlib and others,
but many of them lack some important features.
Although Qt is an application framework instead of a game engine,
its graphics view framework is suitable for my game developing.

Features
----------

1. Framework
    * Open source with Qt graphics view framework
    * Use Lua as AI and extension script

2. Operation experience
    * Full package (include all yoka extension package)
    * Keyboard shortcut
    * Double-click to use cards
    * Cards sorting (by card type and card suit)
    * Multilayer display when cards are more than an upperlimit

3. Extensible
    * Some MODs are available based on this game
    * Lua Packages are supported in this game

HOW TO BUILD
=========

### Windows

1.Download Qt from http://download.qt.io/official_releases/qt/ , make sure the downloaded version is 5.6.0 or later. Then install it.   
```
Note the directory MUST NOT HAVE ANY NON-ASCII CHARACTER if you use QtCreator: e.g. "E:\太阳神三国杀编译\Qt5.7.0" is UNUSABLE because of the Non-ASCII characters in the folder name.  
Note that we only support VS2015 and MinGW versions of Qt for windows, other versions are not supported.
```

2.(VS2015 version only) Download VS2015 from http://go.microsoft.com/fwlink/?LinkID=626924&clcid=0x804   
Install it. While installing, select "Microsoft Visual C++" and "Microsoft Foundation Class" since it is not installed by default and our project depends on it.  
```
Note YOU MUST NOT CHANGE THE INSTALL DIRECTORY OF VS2015 if you use QtCreator.
```

2.(MinGW version only) Manually set the environment variable.
```
1. Open your Qt install dir, enter "Tools", find a folder named "mingwxxx_32" and enter it, enter "bin", copy the full path of this directory.  
2. Right click "This PC" on the desktop, and click "Properties".  
3. Click "Advanced system settings" in the left column.  
4. Enter "Advanced" tab, click "Environment Variables..."  
5. Find a variable which name is "PATH"(case insensible) in "System variables", double click it.  
6. (Win 7/8.1) You'll see a dialog with 2 text input area, paste the copied path in the front of the pathes in the second input area, and add a semicolon ";" after it.  
6. (Win 10) You'll see a list with a lot of pathes, click "New" and paste the copied path, and use "Move Up" to make it become the first of the list.  
7. Press "OK" in all dialogs and logout, login again.  
8. Enter a command prompt, type "gcc --version" to check if the environment variable is successfully set or not.
```

3.Download SWIG from https://sourceforge.net/projects/swig/files/swigwin/ , make sure the downloaded version is 3.0.6 or later.  
extract it, and put the directory in environment variable PATH (it is just like phase 2 for MinGW, but using "swig -version" for step 8)

4.(Qt Creator) Open QSanguosha.pro using QtCreator, set a kit and press the hammer button in the bottom-left cornor.  
4.(Command Prompt) TBD

5.Install. TBD

### Linux / [(Free)(Net)(Open)]BSD

TBD

### macOS / OS X

TBD

### WinRT

TBD

### Android

TBD

### iOS

TBD