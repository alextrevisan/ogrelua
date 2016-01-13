require("ogrelua")
--require('SDKTrays')
--EFL = dofile("ExampleFrameListener.lua")
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
    mOverlaySystem = Ogre.OverlaySystem()
    mSceneMgr:addRenderQueueListener(mOverlaySystem)
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

    mRGM:addResourceLocation("media/packs/SdkTrays.zip",     "Zip",       "Essential", false, true)
    mRGM:addResourceLocation("media/materials/scripts",      "FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/materials/textures",     "FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/models",                 "FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/RTShaderLib/GLSL",       "FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/fonts","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/materials/programs/GLSL","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/materials/textures/nvidia","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/DeferredShadingMedia","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/PCZAppMedia","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/RTShaderLib/materials","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/materials/scripts/SSAO","FileSystem","Popular" , false, true)
    mRGM:addResourceLocation("media/materials/textures/SSAO","FileSystem","Popular" , false, true)

    mRGM:initialiseAllResourceGroups()
end
function createScene()
    
end
initOgre()
createCamera()
createViewports()
initResources()
createScene()
local mTime = 0
local mFPS = 0

local function exampleFrameListener(evt)
    if mWindow:isClosed() then
        return false
    end
    mInputManager:capture()
    mTime = mTime + evt.timeSinceLastFrame
    mFPS = mFPS + 1
    if mTime > 1 then
        print(mFPS)
        mFPS = 0
        mTime = 0
    end
    
    return true;
end

listener = Ogre.FrameListener()
listener:setFrameStarted(exampleFrameListener)
mRoot:addFrameListener(listener)

--b = createButton(TL_TOPLEFT, "Button", "Caption", 20)

--EFL.new(mWindow, mCamera)
overlayManager = Ogre.OverlayManager:getSingletonPtr()

-- Create a panel
panel = overlayManager:createOverlayElement("Panel", "PanelName")
panel:setMetricsMode(Ogre.GMM_PIXELS);
panel:setPosition(10, 10);
panel:setDimensions(100, 100);
panel:setMaterialName("SdkTrays/MiniTextBox"); -- Optional background material

-- Create a text area
textArea = overlayManager:createOverlayElement("TextArea", "TextAreaName")
textArea:setMetricsMode(Ogre.GMM_PIXELS);
textArea:setPosition(0, 0);
textArea:setDimensions(100, 100);
textArea:setCaption(Ogre.DisplayString("Hello, World!"));
textArea:setCharHeight(16);
textArea:setFontName("SdkTrays/Caption");
cor1 = Ogre.ColourValue(0.3, 0.5, 0.3,1.0)
textArea:setColourBottom(cor1);
cor2 = Ogre.ColourValue(0.5, 0.7, 0.5,1.0)
textArea:setColourTop(cor2);

-- Create an overlay, and add the panel
overlay = overlayManager:create("OverlayName");
overlay:add2D(panel);

-- Add the text area to the panel
panel:addChild(textArea);

-- Show the overlay
overlay:show();

mRoot:startRendering()