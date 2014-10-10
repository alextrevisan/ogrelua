g++.exe -std=c++11 -Wall -DBUILD_DLL -O3 -I..\LuaJIT-2.0.3\src -I..\OgreSDK\include\OGRE -c FrameListener.cpp -o FrameListener.o

g++.exe -std=c++11 -Wall -DBUILD_DLL -O3 -I..\LuaJIT-2.0.3\src -I..\OgreSDK\include\OGRE -c main.cpp -o main.o

g++.exe -shared  -Wl,--dll  FrameListener.o main.o  -o ogrelua.dll -s ..\LuaJIT-2.0.3\src\lua51.dll ..\OgreSDK\lib\release\libOgreMain.dll.a

pause