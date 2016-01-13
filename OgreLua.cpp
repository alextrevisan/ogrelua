extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}

#include "LuaIntf/LuaIntf.h"

#include <Ogre.h>
#include <OIS.h>
#include "FrameListener.h"

#include "InputManager.h"
#include "KeyListener.h"

#include "OgreLuaOverlay.h"

extern "C"
{
    LUALIB_API int luaopen_ogrelua(lua_State *L);
}
#define MAJOR "0"
#define MINOR "1"
#define PATCH "1"
#define MYNAME "ogrelua " MAJOR "." MINOR "." PATCH
#define MYVERSION MYNAME " library for " LUA_VERSION " / Jan 2016"

LUALIB_API int luaopen_ogrelua(lua_State *L)
{
    using namespace LuaIntf;

    LuaBinding(L)
        .beginModule("Ogre")
            .addConstant("ST_GENERIC",Ogre::ST_GENERIC)
            .addConstant("ST_EXTERIOR_CLOSE",Ogre::ST_EXTERIOR_CLOSE)
            .addConstant("ST_EXTERIOR_FAR",Ogre::ST_EXTERIOR_FAR)
            .addConstant("ST_EXTERIOR_REAL_FAR",Ogre::ST_EXTERIOR_REAL_FAR)
            .addConstant("ST_INTERIOR",Ogre::ST_INTERIOR)

            .addConstant("RSC_VERTEX_PROGRAM",Ogre::RSC_VERTEX_PROGRAM)

            .beginClass<Ogre::FrameListener>("OgreFrameListener")
            .endClass()
            .beginExtendClass<FrameListener, Ogre::FrameListener>("FrameListener")
                .addConstructor(LUA_ARGS())
                .addFunction("setFrameStarted",&FrameListener::setFrameStarted)
                .addFunction("setFrameRenderingQueued",&FrameListener::setFrameRenderingQueued)
                .addFunction("setFrameRenderingQueued",&FrameListener::setFrameRenderingQueued)
            .endClass()

            .beginClass<Ogre::Degree>("Degree")
                .addConstructor(LUA_ARGS(Ogre::Real))
                .addFunction("valueAngleUnits", Ogre::Degree::valueAngleUnits)
                .addFunction("valueDegrees", Ogre::Degree::valueDegrees)
                .addFunction("valueRadians", Ogre::Degree::valueRadians)
            .endClass()

            .beginClass<Ogre::Radian>("Radian")
                .addConstructor(LUA_ARGS(Ogre::Real))
                .addConstructor(LUA_ARGS(Ogre::Degree))
                .addFunction("valueDegrees", Ogre::Radian::valueDegrees)
                .addFunction("valueRadians", Ogre::Radian::valueRadians)
            .endClass()

            .beginClass<Ogre::Vector3>("Vector3")
                .addConstructor(LUA_ARGS(const Ogre::Real,const Ogre::Real,const Ogre::Real))
                .addVariable("x",&Ogre::Vector3::x)
                .addVariable("y",&Ogre::Vector3::y)
                .addVariable("z",&Ogre::Vector3::z)
            .endClass()

            .beginClass<Ogre::Quaternion>("Quaternion")
                .addConstructor(LUA_ARGS(Ogre::Real,Ogre::Real,Ogre::Real,Ogre::Real))
                .addConstant("IDENTITY", Ogre::Quaternion::IDENTITY)
                .addFunction("getRoll",Ogre::Quaternion::getRoll)
                .addFunction("getYaw",Ogre::Quaternion::getYaw)
                .addFunction("getPitch",Ogre::Quaternion::getPitch)
            .endClass()

            .beginClass<Ogre::MovableObject>("MovableObject")
            .endClass()

            .beginExtendClass<Ogre::Entity, Ogre::MovableObject>("Entity")
            .endClass()

            .beginClass<Ogre::Node>("Node")
            .endClass()

            .beginClass<Ogre::VisibleObjectsBoundsInfo>("VisibleObjectsBoundsInfo")
                .addConstructor(LUA_ARGS(void))
            .endClass()

            .beginExtendClass<Ogre::SceneNode, Ogre::Node>("SceneNode")
                .addConstant("TS_LOCAL",Ogre::SceneNode::TS_LOCAL)
                .addConstant("TS_PARENT",Ogre::SceneNode::TS_PARENT)
                .addConstant("TS_WORLD",Ogre::SceneNode::TS_WORLD)
                .addFunction("attachObject",&Ogre::SceneNode::attachObject)
                .addFunction("numAttachedObjects",&Ogre::SceneNode::numAttachedObjects)
                .addFunction("getAttachedObject",(Ogre::MovableObject*(Ogre::SceneNode::*)(unsigned short))&Ogre::SceneNode::getAttachedObject)
                .addFunction("detachObject",(Ogre::MovableObject*(Ogre::SceneNode::*)(unsigned short))&Ogre::SceneNode::detachObject)
                .addFunction("detachAllObjects",&Ogre::SceneNode::detachAllObjects)
                .addFunction("isInSceneGraph",&Ogre::SceneNode::isInSceneGraph)
                .addFunction("_notifyRootNode",&Ogre::SceneNode::_notifyRootNode)
                .addFunction("_update",&Ogre::SceneNode::_update)
                .addFunction("_updateBounds",&Ogre::SceneNode::_updateBounds)
                .addFunction("_findVisibleObjects",&Ogre::SceneNode::_findVisibleObjects)
                .addFunction("_getWorldAABB",&Ogre::SceneNode::_getWorldAABB)
                .addFunction("getAttachedObjectIterator",(Ogre::SceneNode::ObjectIterator(Ogre::SceneNode::*)(void))&Ogre::SceneNode::getAttachedObjectIterator)
                .addFunction("getCreator",&Ogre::SceneNode::getCreator)
                .addFunction("removeAndDestroyChild",(void(Ogre::SceneNode::*)(unsigned short))&Ogre::SceneNode::removeAndDestroyChild)
                .addFunction("removeAndDestroyAllChildren",&Ogre::SceneNode::removeAndDestroyAllChildren)
                .addFunction("showBoundingBox",&Ogre::SceneNode::showBoundingBox)
                .addFunction("hideBoundingBox",&Ogre::SceneNode::hideBoundingBox)
                .addFunction("_addBoundingBoxToQueue",&Ogre::SceneNode::_addBoundingBoxToQueue)
                .addFunction("getShowBoundingBox",&Ogre::SceneNode::getShowBoundingBox)
                .addFunction("createChildSceneNode",(Ogre::SceneNode*(Ogre::SceneNode::*)(const Ogre::String&,const Ogre::Vector3&,const Ogre::Quaternion&))&Ogre::SceneNode::createChildSceneNode)
                .addFunction("findLights",&Ogre::SceneNode::findLights)
                .addFunction("setFixedYawAxis",&Ogre::SceneNode::setFixedYawAxis)
                .addFunction("yaw",(void(Ogre::SceneNode::*)(const Ogre::Radian&,int))&Ogre::SceneNode::yaw)
                .addFunction("pitch",(void(Ogre::SceneNode::*)(const Ogre::Radian&,int))&Ogre::SceneNode::pitch)
                .addFunction("roll",(void(Ogre::SceneNode::*)(const Ogre::Radian&,int))&Ogre::SceneNode::roll)
                .addFunction("setDirection",(void(Ogre::SceneNode::*)(const Ogre::Vector3&, Ogre::SceneNode::TransformSpace, const Ogre::Vector3&))&Ogre::SceneNode::setDirection)
                .addFunction("lookAt",(void(Ogre::SceneNode::*)(const Ogre::Vector3&,Ogre::SceneNode::TransformSpace, const Ogre::Vector3&))&Ogre::SceneNode::lookAt)
                .addFunction("setAutoTracking",&Ogre::SceneNode::setAutoTracking)
                .addFunction("getAutoTrackTarget",&Ogre::SceneNode::getAutoTrackTarget)
                .addFunction("getAutoTrackOffset",&Ogre::SceneNode::getAutoTrackOffset)
                .addFunction("getAutoTrackLocalDirection",&Ogre::SceneNode::getAutoTrackLocalDirection)
                .addFunction("getParentSceneNode",&Ogre::SceneNode::getParentSceneNode)
                .addFunction("setVisible",&Ogre::SceneNode::setVisible)
                .addFunction("flipVisibility",&Ogre::SceneNode::flipVisibility)
                .addFunction("setDebugDisplayEnabled",&Ogre::SceneNode::setDebugDisplayEnabled)
                .addFunction("setPosition",(void(Ogre::SceneNode::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::SceneNode::setPosition)
                .addFunction("setScale",(void(Ogre::SceneNode::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::SceneNode::setScale)
                .addFunction("getPosition",(const Ogre::Vector3&(Ogre::SceneNode::*)(void))&Ogre::SceneNode::getPosition)
                .addFunction("translate",(void(Ogre::SceneNode::*)(const Ogre::Vector3&,Ogre::SceneNode::TransformSpace))&Ogre::SceneNode::translate)
                .addFunction("getOrientation",Ogre::SceneNode::getOrientation)
                .addFunction("setOrientation",(void(Ogre::SceneNode::*)(const Ogre::Quaternion&))Ogre::SceneNode::setOrientation)
            .endClass()

            .beginExtendClass<Ogre::Camera, Ogre::MovableObject>("Camera")
                .addFunction("setPosition",(void(Ogre::Camera::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::Camera::setPosition)
                .addFunction("getPosition",(const Ogre::Vector3&(Ogre::Camera::*)(void))&Ogre::Camera::getPosition)
                .addFunction("lookAt",(void(Ogre::Camera::*)(const Ogre::Vector3&))&Ogre::Camera::lookAt)
                .addFunction("setNearClipDistance",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setNearClipDistance)
                .addFunction("setFarClipDistance",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setFarClipDistance)
                .addFunction("setAspectRatio",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setAspectRatio)
            .endClass()

            .beginClass<Ogre::ColourValue>("ColourValue")
                .addConstructor(LUA_ARGS(float,float,float,float))
            .endClass()

            .beginClass<Ogre::Light>("Light")
                .addFunction("setPosition",(void(Ogre::Light::*)(const Ogre::Vector3&))&Ogre::Light::setPosition)
                .addFunction("setDiffuseColour",(void(Ogre::Light::*)(const Ogre::ColourValue&))&Ogre::Light::setDiffuseColour)
                .addFunction("setSpecularColour",(void(Ogre::Light::*)(const Ogre::ColourValue&))&Ogre::Light::setSpecularColour)
                .addFunction("getDerivedDirection",&Ogre::Light::getDerivedDirection)
                .addFunction("getDiffuseColour",&Ogre::Light::getDiffuseColour)
                //.addFunction("setType",(void(Ogre::Light::*)(const Ogre::ColourValue&))&Ogre::Light::setType)
            .endClass()

            .beginClass<Ogre::SceneManager>("SceneManager")
                .addFunction("createCamera",&Ogre::SceneManager::createCamera)
                .addFunction("getRootSceneNode",&Ogre::SceneManager::getRootSceneNode)
                .addFunction("addRenderQueueListener",&Ogre::SceneManager::addRenderQueueListener)
                .addFunction("removeRenderQueueListener",&Ogre::SceneManager::removeRenderQueueListener)
                .addFunction("createEntity",(Ogre::Entity*(Ogre::SceneManager::*)(const Ogre::String&,const Ogre::String&,const Ogre::String&))&Ogre::SceneManager::createEntity)
                .addFunction("setAmbientLight",(void(Ogre::SceneManager::*)(Ogre::ColourValue*))&Ogre::SceneManager::setAmbientLight)
                .addFunction("getAmbientLight",&Ogre::SceneManager::getAmbientLight)
                .addFunction("createLight",(Ogre::Light*(Ogre::SceneManager::*)(const Ogre::String&))&Ogre::SceneManager::createLight)
            .endClass()

            .beginClass<Ogre::Viewport>("Viewport")
                .addFunction("setBackgroundColour",(void(Ogre::Viewport::*)(Ogre::ColourValue*))&Ogre::Viewport::setBackgroundColour)
                .addFunction("getActualWidth",(int(Ogre::Viewport::*)(void))&Ogre::Viewport::getActualWidth)
                .addFunction("getActualHeight",(int(Ogre::Viewport::*)(void))&Ogre::Viewport::getActualHeight)
            .endClass()

            .beginClass<Ogre::RenderTarget>("RenderTarget")
            .endClass()

            .beginClass<Ogre::RenderWindow>("RenderWindow")
                .addFunction("addViewport",(Ogre::Viewport*(Ogre::RenderWindow::*)(Ogre::Camera*,int,float,float,float,float))&Ogre::RenderWindow::addViewport)
                .addFunction("isClosed",&Ogre::RenderWindow::isClosed)
            .endClass()
            .beginClass<Ogre::FrameEvent>("FrameEvent")
                .addVariable("timeSinceLastEvent", &Ogre::FrameEvent::timeSinceLastEvent, false)
                .addVariable("timeSinceLastFrame", &Ogre::FrameEvent::timeSinceLastFrame, false)
            .endClass()
            .beginClass<Ogre::Root>("Root")
                .addConstructor(LUA_ARGS(_opt<const Ogre::String&>, _opt<const Ogre::String&>, _opt<const Ogre::String&>))
                .addFunction("restoreConfig",&Ogre::Root::restoreConfig)
                .addFunction("showConfigDialog",&Ogre::Root::showConfigDialog)
                .addFunction("initialise",&Ogre::Root::initialise)
                .addFunction("createSceneManager",(Ogre::SceneManager*(Ogre::Root::*)(Ogre::SceneTypeMask, const Ogre::String&))&Ogre::Root::createSceneManager)
                .addFunction("renderOneFrame", (bool(Ogre::Root::*)(void))&Ogre::Root::renderOneFrame)
                .addFunction("addFrameListener", &Ogre::Root::addFrameListener)
                .addFunction("removeFrameListener", &Ogre::Root::removeFrameListener)
                .addFunction("startRendering", &Ogre::Root::startRendering)
            .endClass()

            .beginClass<Ogre::ResourceGroupManager>("ResourceGroupManager")
                .addStaticFunction("getSingleton",&Ogre::ResourceGroupManager::getSingleton)
                .addFunction("addResourceLocation",&Ogre::ResourceGroupManager::addResourceLocation)
                .addFunction("initialiseAllResourceGroups",&Ogre::ResourceGroupManager::initialiseAllResourceGroups)
            .endClass()
            .beginClass<Ogre::WindowEventUtilities>("WindowEventUtilities")
                .addStaticFunction("messagePump",&Ogre::WindowEventUtilities::messagePump)
            .endClass()
/*
            .beginClass<Ogre::Terrain>("Terrain")
                //.addFunction("getTerrainPosition",(void(Ogre::Terrain::*)(const Ogre::Vector3&, Ogre::Vector3*))&Ogre::Terrain::getTerrainPosition)
                .addConstant("ALIGN_X_Z", Ogre::Terrain::ALIGN_X_Z)
                .addConstant("ALIGN_X_Y", Ogre::Terrain::ALIGN_X_Y)
                .addConstant("ALIGN_Y_Z", Ogre::Terrain::ALIGN_Y_Z)
            .endClass()
            //.addConstant("ALIGN_X_Z",&fromEnum(Ogre::Terrain::ALIGN_X_Z), false)
            //.addConstant("ALIGN_X_Y",&fromEnum(Ogre::Terrain::ALIGN_X_Y), false)
            //.addConstant("ALIGN_Y_Z",&fromEnum(Ogre::Terrain::ALIGN_Y_Z), false)

            .beginClass<Ogre::TerrainGlobalOptions>("TerrainGlobalOptions")
                .addConstructor(LUA_ARGS(void))
                .addFunction("setMaxPixelError", &Ogre::TerrainGlobalOptions::setMaxPixelError)
                .addFunction("setCompositeMapDistance", &Ogre::TerrainGlobalOptions::setCompositeMapDistance)
                .addFunction("setLightMapDirection", &Ogre::TerrainGlobalOptions::setLightMapDirection)
                .addFunction("setCompositeMapAmbient", &Ogre::TerrainGlobalOptions::setCompositeMapAmbient)
                .addFunction("setCompositeMapDiffuse", &Ogre::TerrainGlobalOptions::setCompositeMapDiffuse)
            .endClass()

            .beginClass<Ogre::TerrainGroup::TerrainIterator>("TerrainIterator")
                .addFunction("hasMoreElements", &Ogre::TerrainGroup::TerrainIterator::hasMoreElements)
                .addFunction("getNext", &Ogre::TerrainGroup::TerrainIterator::getNext)
            .endClass()

            .beginClass<Ogre::TerrainGroup>("TerrainGroup")
                .addConstructor(LUA_ARGS(Ogre::SceneManager*, Ogre::Terrain::Alignment, unsigned int, Ogre::Real))
                .addFunction("setFilenameConvention", &Ogre::TerrainGroup::setFilenameConvention)
                .addFunction("setOrigin", &Ogre::TerrainGroup::setOrigin)
                .addFunction("loadAllTerrains", &Ogre::TerrainGroup::loadAllTerrains)
                .addFunction("getTerrainIterator", (Ogre::TerrainGroup::TerrainIterator(Ogre::TerrainGroup::*)(void))&Ogre::TerrainGroup::getTerrainIterator)
                .addFunction("freeTemporaryResources",&Ogre::TerrainGroup::freeTemporaryResources)
                .addFunction("getHeightAtWorldPosition",(float(Ogre::TerrainGroup::*)(const Ogre::Vector3&,Ogre::Terrain**))&Ogre::TerrainGroup::getHeightAtWorldPosition)
            .endClass()*/

        .endModule()
        .beginModule("OIS")
            .beginClass<OIS::KeyEvent>("KeyEvent")
                .addVariable("key", &OIS::KeyEvent::key)
            .endClass()
            .beginClass<OIS::KeyListener>("OISKeyListener")
            .endClass()
            .beginExtendClass<KeyListener, OIS::KeyListener>("KeyListener")
                .addConstructor(LUA_ARGS())
                .addFunction("setKeyPressedListener",&KeyListener::setKeyPressedListener)
                .addFunction("setKeyReleasedListener",&KeyListener::setKeyReleasedListener)
            .endClass()
        .endModule()
        .beginClass<InputManager>("InputManager")
            .addStaticFunction("getSingletonPtr", &InputManager::getSingletonPtr)
            .addFunction("initialise", &InputManager::initialise)
            .addFunction("capture", &InputManager::capture)
            .addFunction("addKeyListener", &InputManager::addKeyListener)
            .addFunction("addMouseListener", &InputManager::addMouseListener)
            .addFunction("addJoystickListener", &InputManager::addJoystickListener)
            .addFunction("removeKeyListener", &InputManager::removeKeyListener)
            .addFunction("removeMouseListener", &InputManager::removeMouseListener)
            .addFunction("removeJoystickListener", &InputManager::removeJoystickListener)
            .addFunction("removeAllListeners", &InputManager::removeAllListeners)
            .addFunction("removeAllKeyListeners", &InputManager::removeAllKeyListeners)
            .addFunction("removeAllMouseListeners", &InputManager::removeAllMouseListeners)
            .addFunction("removeAllJoystickListeners", &InputManager::removeAllJoystickListeners)
        .endClass()
        .beginClass<Ogre::GpuProgramManager>("GpuProgramManager")
            .addStaticFunction("getSingleton", &Ogre::GpuProgramManager::getSingleton)
            .addStaticFunction("getSingletonPtr", &Ogre::GpuProgramManager::getSingletonPtr)
            .addFunction("isSyntaxSupported", &Ogre::GpuProgramManager::isSyntaxSupported)
        .endClass()
        .beginClass<Ogre::RenderSystemCapabilities>("RenderSystemCapabilities")
            .addFunction("hasCapability", &Ogre::RenderSystemCapabilities::hasCapability)
        .endClass();

    register_overlay(L);
    return 1;
}
