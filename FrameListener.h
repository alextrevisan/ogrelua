#ifndef FRAMELISTENER_H
#define FRAMELISTENER_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}

#include <OgreFrameListener.h>

class FrameListener: public Ogre::FrameListener
{
public:
    FrameListener(){}
    void setFrameRenderingQueued(lua_State* L)
    {
        if(lua_isfunction(L,-1))
        {
            mL = L;
            FrameRenderingQueued = luaL_ref(L,LUA_REGISTRYINDEX);
        }
        else
        {
            printf("error not a function");
        }
    }
    void setFrameStarted(lua_State* L)
    {
        if(lua_isfunction(L,-1))
        {
            mL = L;
            FrameStarted = luaL_ref(L,LUA_REGISTRYINDEX);
        }
        else
        {
            printf("error not a function");
        }
    }
    void setFrameEnded(lua_State* L)
    {
        if(lua_isfunction(L,-1))
        {
            mL = L;
            FrameEnded = luaL_ref(L,LUA_REGISTRYINDEX);
        }
        else
        {
            printf("error not a function");
        }
    }

    bool frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
	    if(FrameRenderingQueued==0) return true;
        lua_rawgeti(mL, LUA_REGISTRYINDEX, FrameRenderingQueued);
        lua_newtable(mL);
        lua_pushstring(mL, "timeSinceLastFrame");
        lua_pushnumber(mL, evt.timeSinceLastFrame);
        lua_settable(mL, -3);
        lua_pushstring(mL, "timeSinceLastEvent");
        lua_pushnumber(mL, evt.timeSinceLastEvent);
        lua_settable(mL, -3);
        if(lua_pcall(mL,1,1,0)!=0)
        {
            printf("error running function: %s\n",lua_tostring(mL, -1));
            return false;
        }
        else
        {
            return lua_toboolean(mL, -1);
        }
	}
	bool frameStarted(const Ogre::FrameEvent& evt)
	{
	    if(FrameStarted==0) return true;
        lua_rawgeti(mL, LUA_REGISTRYINDEX, FrameStarted);

        lua_newtable(mL);
        lua_pushstring(mL, "timeSinceLastFrame");
        lua_pushnumber(mL, evt.timeSinceLastFrame);
        lua_settable(mL, -3);
        lua_pushstring(mL, "timeSinceLastEvent");
        lua_pushnumber(mL, evt.timeSinceLastEvent);
        lua_settable(mL, -3);

        if(lua_pcall(mL,1,1,0)!=0)
        {
            printf("error running function: %s\n",lua_tostring(mL, -1));
            return false;
        }
        else
        {
            return lua_toboolean(mL, -1);
        }
	}
	bool frameEnded(const Ogre::FrameEvent& evt)
	{
	    if(FrameEnded==0) return true;
        lua_rawgeti(mL, LUA_REGISTRYINDEX, FrameEnded);
        lua_newtable(mL);
        lua_pushstring(mL, "timeSinceLastFrame");
        lua_pushnumber(mL, evt.timeSinceLastFrame);
        lua_settable(mL, -3);
        lua_pushstring(mL, "timeSinceLastEvent");
        lua_pushnumber(mL, evt.timeSinceLastEvent);
        lua_settable(mL, -3);
        if(lua_pcall(mL,1,1,0)!=0)
        {
            printf("error running function: %s\n",lua_tostring(mL, -1));
            return false;
        }
        else
        {
            return lua_toboolean(mL, -1);
        }
	}
private:
    int FrameStarted = 0;
    int FrameRenderingQueued = 0;
    int FrameEnded = 0;
    lua_State* mL;
};

#endif // FRAMELISTENER_H
