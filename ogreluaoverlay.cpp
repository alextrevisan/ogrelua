extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}

#include "LuaIntf/LuaIntf.h"

#include <Ogre.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayElement.h>
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFont.h>
#include <Overlay/OgreFontManager.h>

extern "C"
{
    LUALIB_API int luaopen_ogreluaoverlay(lua_State *L);
}
#define MAJOR "0"
#define MINOR "1"
#define PATCH "1"
#define MYNAME "ogreluaoverlay " MAJOR "." MINOR "." PATCH
#define MYVERSION MYNAME " library for " LUA_VERSION " / Jan 2016"

LUALIB_API int luaopen_ogreluaoverlay(lua_State *L)
{
    using namespace LuaIntf;

    LuaBinding(L)
        .beginModule("Ogre")
            .beginClass<Ogre::OverlayContainer::ChildIterator>("OverlayContainerChildIterator")
                .addFunction("hasMoreElements", &Ogre::OverlayContainer::ChildIterator::hasMoreElements)
                .addFunction("getNext", &Ogre::OverlayContainer::ChildIterator::getNext)
            .endClass()
            .beginClass<Ogre::OverlayContainer>("OverlayContainer")
                .addFunction("getChildIterator", &Ogre::OverlayContainer::getChildIterator)
                .addFunction("removeChild", &Ogre::OverlayContainer::removeChild)
            .endClass()
            .beginClass<Ogre::OverlayElement>("OverlayElement")
                .addFunction("setCaption", &Ogre::OverlayElement::setCaption)
                .addFunction("getParent", &Ogre::OverlayElement::getParent)
                .addFunction("getName", &Ogre::OverlayElement::getName)
                .addFunction("_getDerivedLeft", &Ogre::OverlayElement::_getDerivedLeft)
                .addFunction("_getDerivedTop", &Ogre::OverlayElement::_getDerivedTop)
                .addFunction("getWidth", &Ogre::OverlayElement::getWidth)
                .addFunction("getHeight", &Ogre::OverlayElement::getHeight)
            .endClass()
            .beginClass<Ogre::Overlay>("Overlay")
            .endClass()
            .beginClass<Ogre::DisplayString>("DisplayString")
            .endClass()
            .beginClass<Ogre::Font>("Font")
                .addFunction("getGlyphAspectRatio", &Ogre::Font::getGlyphAspectRatio)
            .endClass()
            .beginClass<Ogre::FontPtr>("FontPtr")
                .addFunction("getPointer", &Ogre::FontPtr::getPointer)
            .endClass()
            .beginClass<Ogre::FontManager>("FontManager")
                .addStaticFunction("getSingleton", &Ogre::FontManager::getSingleton)
                .addFunction("getByName", &Ogre::FontManager::getByName)
            .endClass()
            .beginClass<Ogre::TextAreaOverlayElement>("TextAreaOverlayElement")
                .addFunction("getFontName", &Ogre::TextAreaOverlayElement::getFontName)
                .addFunction("getSpaceWidth", &Ogre::TextAreaOverlayElement::getSpaceWidth)
                .addFunction("getCharHeight", &Ogre::TextAreaOverlayElement::getCharHeight)
            .endClass()
            .beginClass<Ogre::OverlayManager>("OverlayManager")
                .addStaticFunction("getSingleton", &Ogre::OverlayManager::getSingleton)
                .addFunction("getOverlayElement", &Ogre::OverlayManager::getOverlayElement)
                .addFunction("getByName", &Ogre::OverlayManager::getByName)
                .addFunction("destroyOverlayElement", (void(Ogre::OverlayManager::*)(Ogre::OverlayElement*, bool))&Ogre::OverlayManager::destroyOverlayElement)
                .addFunction("getViewportWidth", &Ogre::OverlayManager::getViewportWidth)
            .endClass();
    return 1;
}
