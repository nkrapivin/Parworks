# Parworks
Fixing YYG Steamworks extension mistakes

See the wiki for now https://github.com/nkrapivin/Parworks/wiki

And the `Obj_Steam_controller` object, it was made by YYG originally and has some Parworks example usage.

## Building (Windows)

Cd to `_DLL_SOURCE`.

Use Visual Studio 2022 with C++ support to build the DLL.

Then copy `Release/Par.dll` into `../../extensions/Par` and copy `x64/Release/Par_x64.dll` into `../../../extensions/Par`.

## Building (Linux)

Install the Steam Runtime SDK container, be it Docker or whatever.

Valve's Guide: https://gitlab.steamos.cloud/steamrt/scout/sdk/-/blob/steamrt/scout/README.md

Switch inside the container, cd to repo dir, then cd to `_DLL_SOURCE`, and type `make`.

Then copy all .so files into `../extensions/Par/`.

## Building (macOS)

Install the Xcode Command-Line tools with C++ STL support.

(Make sure you can make at least C++ STL console app projects)

Cd to repo dir, then cd to `_DLL_SOURCE`, and type `make -f Makefile.mac`.

Then copy all .dylib files into `../extensions/Par/`.
