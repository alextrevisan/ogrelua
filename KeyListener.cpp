#include "KeyListener.h"

KeyListener::KeyListener()
{
    //ctor
}

KeyListener::~KeyListener()
{
    //dtor
}

bool KeyListener::keyPressed(const OIS::KeyEvent& e)
{
    if(KeyPressedListener==0) return true;
    lua_rawgeti(mL, LUA_REGISTRYINDEX, KeyPressedListener);

    LuaIntf::Lua::push(mL,e);

    if(lua_pcall(mL,1,1,0)!=0)
    {
        printf("error running function on keyPressed event: %s\n",lua_tostring(mL, -1));
        return false;
    }
    else
    {
        bool ret = lua_toboolean(mL, -1);
        lua_pop(mL, 1);
        return ret;
    }
}

bool KeyListener::keyReleased(const OIS::KeyEvent& e)
{
    if(KeyReleasedListener==0) return true;
    lua_rawgeti(mL, LUA_REGISTRYINDEX, KeyReleasedListener);

    LuaIntf::Lua::push(mL,e);

    if(lua_pcall(mL,1,1,0)!=0)
    {
        printf("error running function on keyPressed event: %s\n",lua_tostring(mL, -1));
        return false;
    }
    else
    {
        bool ret = lua_toboolean(mL, -1);
        lua_pop(mL, 1);
        return ret;
    }
}

void KeyListener::setKeyPressedListener(lua_State* L)
{
    if(lua_isfunction(L,-1))
    {
        mL = L;
        KeyPressedListener = luaL_ref(L,LUA_REGISTRYINDEX);
    }
    else
    {
        printf("ERROR in setKeyPressedListener: parameter is not a function");
    }
}

void KeyListener::setKeyReleasedListener(lua_State* L)
{
    if(lua_isfunction(L,-1))
    {
        mL = L;
        KeyReleasedListener = luaL_ref(L,LUA_REGISTRYINDEX);
    }
    else
    {
        printf("ERROR in setKeyReleasedListener: parameter is not a function");
    }
}


