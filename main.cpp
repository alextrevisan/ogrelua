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

            .beginClass<FrameListener>("FrameListener")
                .addConstructor<void(*)(void)>()
                .addFunction("setFrameStarted",&FrameListener::setFrameStarted)
                .addFunction("setFrameStarted",&FrameListener::setFrameRenderingQueued)
                .addFunction("setFrameStarted",&FrameListener::setFrameEnded)
            .endClass()

            .beginClass<Ogre::FrameEvent>("FrameEvent")
                .addData("timeSinceLastFrame",&Ogre::FrameEvent::timeSinceLastFrame)
                .addData("timeSinceLastEvent",&Ogre::FrameEvent::timeSinceLastEvent)
            .endClass()

            .beginClass<Ogre::Radian>("Radian")
                .addConstructor<void(*)(Ogre::Real)>()
            .endClass()

            .beginClass<Ogre::Degree>("Degree")
                .addConstructor<void(*)(Ogre::Real)>()
                .addFunction("set",(Ogre::Degree&(Ogre::Degree::*)(const Ogre::Real&))&Ogre::Degree::operator=)
                .addFunction("set",(Ogre::Degree&(Ogre::Degree::*)(const Ogre::Degree&))&Ogre::Degree::operator=)
                .addFunction("set",(Ogre::Degree&(Ogre::Degree::*)(const Ogre::Radian&))&Ogre::Degree::operator=)
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

            .beginClass<Ogre::Entity>("Entity")
            .endClass()

            .beginClass<Ogre::SceneNode>("SceneNode")
                .addFunction("attachObject",&Ogre::SceneNode::attachObject)
                .addFunction("yaw",(void(Ogre::SceneNode::*)(const Ogre::Radian&,Ogre::SceneNode::TransformSpace))&Ogre::SceneNode::yaw)
                .addFunction("setPosition",(void(Ogre::SceneNode::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::SceneNode::setPosition)
                .addFunction("setScale",(void(Ogre::SceneNode::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::SceneNode::setScale)
                .addFunction("getPosition",(Ogre::Vector3&(Ogre::SceneNode::*)(void))&Ogre::SceneNode::getPosition)
                .addFunction("lookAt",(void(Ogre::SceneNode::*)(const Ogre::Vector3&,Ogre::SceneNode::TransformSpace, const Ogre::Vector3&))&Ogre::SceneNode::lookAt)
                .addFunction("createChildSceneNode",(Ogre::SceneNode*(Ogre::SceneNode::*)(const Ogre::String&,const Ogre::Vector3&,const Ogre::Quaternion&))&Ogre::SceneNode::createChildSceneNode)
            .endClass()

            .beginClass<Ogre::MovableObject>("MovableObject")
            .endClass()

            .beginClass<Ogre::Camera>("Camera")
                .addFunction("setPosition",(void(Ogre::Camera::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::Camera::setPosition)
                .addFunction("lookAt",(void(Ogre::Camera::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::Camera::lookAt)
                .addFunction("setNearClipDistance",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setNearClipDistance)
                .addFunction("setFarClipDistance",(void(Ogre::Camera::*)(Ogre::Real))&Ogre::Camera::setFarClipDistance)
            .endClass()

            .beginClass<Ogre::ColourValue>("ColourValue")
                .addConstructor<void(*)(float,float,float,float)>()
            .endClass()

            .beginClass<Ogre::Light>("Light")
                .addFunction("setPosition",(void(Ogre::Light::*)(Ogre::Real,Ogre::Real,Ogre::Real))&Ogre::Light::setPosition)
            .endClass()

            .beginClass<Ogre::SceneManager>("SceneManager")
                .addFunction("createCamera",&Ogre::SceneManager::createCamera)
                .addFunction("getRootSceneNode",&Ogre::SceneManager::getRootSceneNode)
                .addFunction("createEntity",(Ogre::Entity*(Ogre::SceneManager::*)(const Ogre::String&,const Ogre::String&,const Ogre::String&))&Ogre::SceneManager::createEntity)
                .addFunction("setAmbientLight",(void(Ogre::SceneManager::*)(Ogre::ColourValue*))&Ogre::SceneManager::setAmbientLight)
                .addFunction("createLight",(Ogre::Light*(Ogre::SceneManager::*)(void))&Ogre::SceneManager::createLight)
                .addFunction("createLight",(Ogre::Light*(Ogre::SceneManager::*)(const Ogre::String&))&Ogre::SceneManager::createLight)
            .endClass()

            .beginClass<Ogre::Viewport>("Viewport")
                .addFunction("setBackgroundColour",(void(Ogre::Viewport::*)(Ogre::ColourValue*))&Ogre::Viewport::setBackgroundColour)
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
            //.beginClass<Ogre::WindowEventUtilities>("WindowEventUtilities")
            //    .addFunction("messagePump",&Ogre::WindowEventUtilities::messagePump)
            //.endClass()

        .endNamespace();
    return 1;
}
