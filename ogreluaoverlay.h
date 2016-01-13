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
#include <Overlay/OgreBorderPanelOverlayElement.h>
#include <Overlay/OgreOverlaySystem.h>

void register_overlay(lua_State *L)
{
    using namespace LuaIntf;

    LuaBinding(L)
        .beginModule("Ogre")
            .addConstant("GMM_RELATIVE", Ogre::GMM_RELATIVE)
            .addConstant("GMM_PIXELS", Ogre::GMM_PIXELS)
            .addConstant("GMM_RELATIVE_ASPECT_ADJUSTED", Ogre::GMM_RELATIVE_ASPECT_ADJUSTED)
            .beginClass<Ogre::DisplayString>("DisplayString")
                .addConstructor(LUA_ARGS(const std::string&))
            .endClass()
            .beginClass<Ogre::ColourValue>("ColourValue")
                //.addConstructor(LUA_ARGS(float,float,float,float))
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
            .beginClass<Ogre::Overlay>("Overlay")
                .addFunction("add2D", &Ogre::Overlay::add2D)
                .addFunction("show", &Ogre::Overlay::show)
            .endClass()
            .beginClass<Ogre::OverlayElement>("OverlayElement")
                .addFunction("setCaption", &Ogre::OverlayElement::setCaption)
                .addFunction("getParent", &Ogre::OverlayElement::getParent)
                .addFunction("getName", &Ogre::OverlayElement::getName)
                .addFunction("_getDerivedLeft", &Ogre::OverlayElement::_getDerivedLeft)
                .addFunction("_getDerivedTop", &Ogre::OverlayElement::_getDerivedTop)
                .addFunction("getWidth", &Ogre::OverlayElement::getWidth)
                .addFunction("getHeight", &Ogre::OverlayElement::getHeight)
                .addFunction("isVisible", &Ogre::OverlayElement::isVisible)
                .addFunction("show", &Ogre::OverlayElement::show)
                .addFunction("hide", &Ogre::OverlayElement::hide)
                .addFunction("setMetricsMode", &Ogre::OverlayElement::setMetricsMode)
                .addFunction("setPosition", &Ogre::OverlayElement::setPosition)
                .addFunction("setDimensions", &Ogre::OverlayElement::setDimensions)
                .addFunction("setMaterialName", &Ogre::OverlayElement::setMaterialName)
                .addFunction("setCaption", &Ogre::OverlayElement::setCaption)
            .endClass()
            .beginExtendClass<Ogre::TextAreaOverlayElement, Ogre::OverlayElement>("TextAreaOverlayElement")
                .addFunction("getFontName", &Ogre::TextAreaOverlayElement::getFontName)
                .addFunction("setFontName", &Ogre::TextAreaOverlayElement::setFontName)
                .addFunction("getSpaceWidth", &Ogre::TextAreaOverlayElement::getSpaceWidth)
                .addFunction("getCharHeight", &Ogre::TextAreaOverlayElement::getCharHeight)
                .addFunction("setCharHeight", &Ogre::TextAreaOverlayElement::setCharHeight)
                .addFunction("setColourBottom", &Ogre::TextAreaOverlayElement::setColourBottom)
                .addFunction("setColourTop", &Ogre::TextAreaOverlayElement::setColourTop)
            .endClass()
            .beginClass<Ogre::OverlayContainer::ChildIterator>("OverlayContainerChildIterator")
                .addFunction("hasMoreElements", &Ogre::OverlayContainer::ChildIterator::hasMoreElements)
                .addFunction("getNext", &Ogre::OverlayContainer::ChildIterator::getNext)
            .endClass()
            .beginExtendClass<Ogre::OverlayContainer, Ogre::OverlayElement>("OverlayContainer")
                .addFunction("getChildIterator", &Ogre::OverlayContainer::getChildIterator)
                .addFunction("addChild", &Ogre::OverlayContainer::addChild)
                .addFunction("removeChild", &Ogre::OverlayContainer::removeChild)
            .endClass()
            .beginExtendClass<Ogre::PanelOverlayElement, Ogre::OverlayContainer>("PanelOverlayElement")
            .endClass()
            .beginExtendClass<Ogre::BorderPanelOverlayElement, Ogre::PanelOverlayElement>("BorderPanelOverlayElement")
                .addFunction("getChild", &Ogre::BorderPanelOverlayElement::getChild)
            .endClass()
            .beginClass<Ogre::OverlayManager>("OverlayManager")
                .addStaticFunction("getSingleton", &Ogre::OverlayManager::getSingleton)
                .addStaticFunction("getSingletonPtr", &Ogre::OverlayManager::getSingletonPtr)
                .addFunction("getOverlayElement", &Ogre::OverlayManager::getOverlayElement)
                .addFunction("getByName", &Ogre::OverlayManager::getByName)
                .addFunction("destroyOverlayElement", (void(Ogre::OverlayManager::*)(Ogre::OverlayElement*, bool))&Ogre::OverlayManager::destroyOverlayElement)
                .addFunction("getViewportWidth", &Ogre::OverlayManager::getViewportWidth)
                .addFunction("createOverlayElementFromTemplate", &Ogre::OverlayManager::createOverlayElementFromTemplate)
                .addFunction("createOverlayElement", &Ogre::OverlayManager::createOverlayElement)
                .addFunction("create", &Ogre::OverlayManager::create)
            .endClass()
            .beginClass<Ogre::RenderQueueListener>("RenderQueueListener")
            .endClass()
            .beginExtendClass<Ogre::OverlaySystem,Ogre::RenderQueueListener>("OverlaySystem")
                .addConstructor(LUA_ARGS(void))
            .endClass();
}
