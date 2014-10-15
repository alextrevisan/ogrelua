extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}

#include "LuaBridge/LuaBridge.h"

#include <Ogre.h>
#include "FrameListener.h"

extern "C"
{
    LUALIB_API int luaopen_ogrelua(lua_State *L);
}
#define MAJOR "0"
#define MINOR "1"
#define PATCH "0"
#define MYNAME "ogrelua " MAJOR "." MINOR "." PATCH
#define MYVERSION MYNAME " library for " LUA_VERSION " / Oct 2014"


inline int* fromEnum(int value)
{
    int * tmp = new int;
    *tmp = value;
    return tmp;
}
// well... i tried...but can't register Ogre::ResourceGroupManager...
//so.. its an alternative
class ResourceGroupManager
{
public:
    ResourceGroupManager(){}
    void initialiseAllResourceGroups()
    {
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }
    void addResourceLocation(const Ogre::String& name, const Ogre::String& locType,
                const Ogre::String& resGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, bool recursive = false, bool readOnly = true)
    {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name,locType,resGroup,recursive,readOnly);
    }
};

class WindowEventUtilities
{
    public:
    WindowEventUtilities(){}
    void messagePump()
    {
        Ogre::WindowEventUtilities::messagePump();
    }
};

LUALIB_API int luaopen_ogrelua(lua_State *L)
{
    using namespace luabridge;
    getGlobalNamespace(L)
        .beginNamespace("Ogre")
            .addVariable("ST_GENERIC",fromEnum(Ogre::ST_GENERIC), false)
            .addVariable("ST_EXTERIOR_CLOSE",fromEnum(Ogre::ST_EXTERIOR_CLOSE), false)
            .addVariable("ST_EXTERIOR_FAR",fromEnum(Ogre::ST_EXTERIOR_FAR), false)
            .addVariable("ST_EXTERIOR_REAL_FAR",fromEnum(Ogre::ST_EXTERIOR_REAL_FAR), false)
            .addVariable("ST_INTERIOR",fromEnum(Ogre::ST_INTERIOR), false)

            .addVariable("TS_LOCAL",fromEnum(Ogre::SceneNode::TS_LOCAL), false)
            .addVariable("TS_PARENT",fromEnum(Ogre::SceneNode::TS_PARENT), false)
            .addVariable("TS_WORLD",fromEnum(Ogre::SceneNode::TS_WORLD), false)

            .beginClass<Ogre::FrameListener>("OgreFrameListener")
            .endClass()
            .deriveClass<FrameListener, Ogre::FrameListener>("FrameListener")
                .addConstructor<void(*)(void)>()
                .addFunction("setFrameStarted",&FrameListener::setFrameStarted)
                .addFunction("setFrameRenderingQueued",&FrameListener::setFrameRenderingQueued)
                .addFunction("setFrameRenderingQueued",&FrameListener::setFrameRenderingQueued)
            .endClass()

            .beginClass<Ogre::Degree>("Degree")
                .addConstructor<void(*)(Ogre::Real)>()
            .endClass()

            .beginClass<Ogre::Radian>("Radian")
                .addConstructor<void(*)(Ogre::Real)>()
                .addConstructor<void(*)(Ogre::Degree)>()
            .endClass()

            .beginClass<Ogre::Vector3>("Vector3")
                .addConstructor<void(*)(const Ogre::Real,const Ogre::Real,const Ogre::Real)>()
                .addData("x",&Ogre::Vector3::x)
                .addData("y",&Ogre::Vector3::y)
                .addData("z",&Ogre::Vector3::z)
            .endClass()

            .beginClass<Ogre::Quaternion>("Quaternion")
                .addConstructor<void(*)(Ogre::Real,Ogre::Real,Ogre::Real,Ogre::Real)>()
            .endClass()

            .beginClass<Ogre::MovableObject>("MovableObject")
            .endClass()

            .deriveClass<Ogre::Entity, Ogre::MovableObject>("Entity")
            .endClass()
            .beginClass<Ogre::Node>("Node")
            .endClass()

            .deriveClass<Ogre::SceneNode, Ogre::Node>("SceneNode")
                .addFunction("attachObject",&Ogre::SceneNode::attachObject)
                .addFunction("yaw",(void(Ogre::SceneNode::*)(const Ogre::Radian&,int))&Ogre::SceneNode::yaw)
                .addFunction("setPosition",(void(Ogre::SceneNode::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::SceneNode::setPosition)
                .addFunction("setScale",(void(Ogre::SceneNode::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::SceneNode::setScale)
                .addFunction("getPosition",(const Ogre::Vector3&(Ogre::SceneNode::*)(void))&Ogre::SceneNode::getPosition)
                .addFunction("lookAt",(void(Ogre::SceneNode::*)(const Ogre::Vector3&,Ogre::SceneNode::TransformSpace, const Ogre::Vector3&))&Ogre::SceneNode::lookAt)
                .addFunction("createChildSceneNode",(Ogre::SceneNode*(Ogre::SceneNode::*)(const Ogre::String&,const Ogre::Vector3&,const Ogre::Quaternion&))&Ogre::SceneNode::createChildSceneNode)
            .endClass()



            .deriveClass<Ogre::Camera, Ogre::MovableObject>("Camera")
                .addFunction("setPosition",(void(Ogre::Camera::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::Camera::setPosition)
                .addFunction("getPosition",(const Ogre::Vector3&(Ogre::Camera::*)(void))&Ogre::Camera::getPosition)
                .addFunction("lookAt",(void(Ogre::Camera::*)(const Ogre::Vector3&))&Ogre::Camera::lookAt)
                .addFunction("setNearClipDistance",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setNearClipDistance)
                .addFunction("setFarClipDistance",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setFarClipDistance)
                .addFunction("setAspectRatio",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setAspectRatio)
            .endClass()

            .beginClass<Ogre::ColourValue>("ColourValue")
                .addConstructor<void(*)(float,float,float,float)>()
            .endClass()

            .beginClass<Ogre::Light>("Light")
                .addFunction("setPosition",(void(Ogre::Light::*)(const Ogre::Vector3&))&Ogre::Light::setPosition)
                .addFunction("setDiffuseColour",(void(Ogre::Light::*)(const Ogre::ColourValue&))&Ogre::Light::setDiffuseColour)
                .addFunction("setSpecularColour",(void(Ogre::Light::*)(const Ogre::ColourValue&))&Ogre::Light::setSpecularColour)
                //.addFunction("setType",(void(Ogre::Light::*)(const Ogre::ColourValue&))&Ogre::Light::setType)
            .endClass()

            .beginClass<Ogre::SceneManager>("SceneManager")
                .addFunction("createCamera",&Ogre::SceneManager::createCamera)
                .addFunction("getRootSceneNode",&Ogre::SceneManager::getRootSceneNode)
                .addFunction("createEntity",(Ogre::Entity*(Ogre::SceneManager::*)(const Ogre::String&,const Ogre::String&,const Ogre::String&))&Ogre::SceneManager::createEntity)
                .addFunction("setAmbientLight",(void(Ogre::SceneManager::*)(Ogre::ColourValue*))&Ogre::SceneManager::setAmbientLight)
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

            .beginClass<Ogre::Root>("Root")
                .addConstructor<void(Ogre::Root::*)(const Ogre::String&, const Ogre::String&, const Ogre::String&)>()
                .addFunction("restoreConfig",&Ogre::Root::restoreConfig)
                .addFunction("showConfigDialog",&Ogre::Root::showConfigDialog)
                .addFunction("initialise",&Ogre::Root::initialise)
                .addFunction("createSceneManager",(Ogre::SceneManager*(Ogre::Root::*)(Ogre::SceneTypeMask, const Ogre::String&))&Ogre::Root::createSceneManager)
                .addFunction("renderOneFrame", (bool(Ogre::Root::*)(void))&Ogre::Root::renderOneFrame)
                .addFunction("addFrameListener", &Ogre::Root::addFrameListener)
                .addFunction("startRendering", &Ogre::Root::startRendering)
            .endClass()

            .beginClass<ResourceGroupManager>("ResourceGroupManager")
                .addConstructor<void(*)(void)>()
                .addFunction("addResourceLocation",&ResourceGroupManager::addResourceLocation)
                .addFunction("initialiseAllResourceGroups",&ResourceGroupManager::initialiseAllResourceGroups)
            .endClass()
            .beginClass<WindowEventUtilities>("WindowEventUtilities")
                .addConstructor<void(*)(void)>()
                .addFunction("messagePump",(void(WindowEventUtilities::*)())&WindowEventUtilities::messagePump)
            .endClass()

        .endNamespace();
    return 1;
}
