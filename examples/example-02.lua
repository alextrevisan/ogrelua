require("ogrelua")

ship = require 'ship'
local mRoot
local mWindow
local mSceneMgr
local mCamera
local mRGM

local mInputManager = InputManager.getSingletonPtr()

local mainShip

function initOgre()
    mRoot = Ogre.Root("plugins.cfg", "video.cfg", "Graphicslog.txt")
    if mRoot:restoreConfig() == false then
        mRoot:showConfigDialog()
    end
    mWindow = mRoot:initialise(true,"Lua + Ogre Rocks!!!","")
    mSceneMgr = mRoot:createSceneManager(Ogre.ST_GENERIC,"")
    mInputManager:initialise(mWindow)
end
function createCamera()
    mCamera = mSceneMgr:createCamera("PlayerCam")
    mCamera:setPosition(0.0, 10.0, 500.0)
    mCamera:lookAt(Ogre.Vector3(0,0,0))
    mCamera:setNearClipDistance(5)
end
function createViewports()
    local vp = mWindow:addViewport(mCamera,0,0.0,0.0,1.0,1.0);
    vp:setBackgroundColour(Ogre.ColourValue(0.5,0.5,0.5,1.0))
    mCamera:setAspectRatio(vp:getActualWidth() / vp:getActualHeight());
end
function initResources()
    mRGM = Ogre.ResourceGroupManager:getSingleton()

    mRGM:addResourceLocation("media/packs/SdkTrays.zip",     "Zip",       "Essencial", false, true)
    mRGM:addResourceLocation("media/materials/scripts",      "FileSystem","Recursos" , false, true)
    mRGM:addResourceLocation("media/materials/textures",     "FileSystem","Recursos" , false, true)
    mRGM:addResourceLocation("media/models",                 "FileSystem","Recursos" , false, true)
    mRGM:addResourceLocation("media/RTShaderLib/GLSL",       "FileSystem","Recursos" , false, true)
    mRGM:addResourceLocation("media/materials/programs/GLSL","FileSystem","Recursos" , false, true)

    mRGM:initialiseAllResourceGroups()
end
function createScene()
    local ent
    local light
    mSceneMgr:setAmbientLight(Ogre.ColourValue(0.9, 0.9, 0.9, 1.0))

    --ent = mSceneMgr:createEntity("Ninja","ninja.mesh", "General")
    --local node = mSceneMgr:getRootSceneNode():createChildSceneNode("node", Ogre.Vector3(0,0,0),Ogre.Quaternion(1,0,0,0))
    --node:attachObject(ent)
    mCamera:lookAt(Ogre.Vector3(0,0,0))

    light = mSceneMgr:createLight("Light1")
    light:setPosition(Ogre.Vector3(0,150,250))
    light:setDiffuseColour(Ogre.ColourValue(1.0, 0.0, 0.0, 1.0));
    light:setSpecularColour(Ogre.ColourValue(1.0, 0.0, 0.0,1.0));

    light = mSceneMgr:createLight("Light2")
    light:setPosition(Ogre.Vector3(0,150,-250))
    light:setDiffuseColour(Ogre.ColourValue(0.25, 0.25, 0,1.0));
    light:setSpecularColour(Ogre.ColourValue(0.25, 0.25, 0,1.0));

    mainShip = ship.create(mSceneMgr)
end
initOgre()
createCamera()
createViewports()
initResources()
createScene()
local mTime = 0
local mFPS = 0

local WPressed, APressed, DPressed, SPressed
local function exampleFrameListener(evt)
    if mWindow:isClosed() then
        return false;
    end
    mInputManager:capture()
    mTime = mTime + evt.timeSinceLastFrame
    mFPS = mFPS + 1
    if mTime > 1 then
        print(mFPS)
        mFPS = 0
        mTime = 0
    end
    
    if WPressed then mainShip.moveForward() end
    if APressed then mainShip.turnLeft() end
    if DPressed then mainShip.turnRight() end
    if SPressed then mainShip.moveBackwars() end
    
    mainShip.update(evt.timeSinceLastFrame)
    
    return true;
end

listener = Ogre.FrameListener()
listener:setFrameStarted(exampleFrameListener)
mRoot:addFrameListener(listener)

local function exampleKeyPressed(evt)
    print("Pressed: "..evt.key)
    if evt.key == 17 then --W
        WPressed = true
    end
    if evt.key == 31 then --S
        SPressed = true
    end
    if evt.key == 30 then --A
        APressed = true
    end
    if evt.key == 32 then --D
        DPressed = true
    end
    return true
end
local function exampleKeyReleased(evt)
    if evt.key == 17 then --W
        WPressed = false
    end
    if evt.key == 31 then --S
        SPressed = false
    end
    if evt.key == 30 then --A
        APressed = false
    end
    if evt.key == 32 then --D
        DPressed = false
    end
    return true
end

KeyListener = OIS.KeyListener()
KeyListener:setKeyPressedListener(exampleKeyPressed)
KeyListener:setKeyReleasedListener(exampleKeyReleased)
mInputManager:addKeyListener(KeyListener, "shipMove")

mRoot:startRendering()