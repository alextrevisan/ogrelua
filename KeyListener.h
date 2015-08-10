#ifndef KEYLISTENER_H
#define KEYLISTENER_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}
#include "LuaIntf/LuaIntf.h"
#include <OIS.h>

class KeyListener : public OIS::KeyListener
{
    public:
        KeyListener();
        virtual ~KeyListener();
        void setKeyPressedListener(lua_State* L);
        void setKeyReleasedListener(lua_State* L);
        bool keyPressed( const OIS::KeyEvent &e );
        bool keyReleased( const OIS::KeyEvent &e );
    private:
        int KeyPressedListener = 0;
        int KeyReleasedListener = 0;
        lua_State* mL;
};

#endif // KEYLISTENER_H
