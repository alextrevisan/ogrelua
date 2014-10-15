ogrelua
=======

Lua bindings for Ogre3D


#### Simple Lua example ####

Load the ninja mesh and show on screen

```Lua

require("ogrelua")
local mRoot
local mWindow
local mSceneMgr

local mCamera
local mRGM
function initOgre()
	mRoot = Ogre.Root("plugins.cfg", "video.cfg", "Graphicslog.txt")
	if mRoot:restoreConfig() == false then
		mRoot:showConfigDialog()
	end
	mWindow = mRoot:initialise(true,"Lua + Ogre Rocks!!!","")
	mSceneMgr = mRoot:createSceneManager(Ogre.ST_GENERIC,"")
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
	mRGM = Ogre.ResourceGroupManager()

	mRGM:addResourceLocation("media/packs/SdkTrays.zip",	"Zip",			"Essencial", false, true)
	mRGM:addResourceLocation("media/materials/scripts",	    "FileSystem",	"Recursos" , false, true)
	mRGM:addResourceLocation("media/materials/textures",	"FileSystem",	"Recursos" , false, true)
	mRGM:addResourceLocation("media/models",				"FileSystem",	"Recursos" , false, true)
	mRGM:addResourceLocation("media/RTShaderLib/GLSL",				"FileSystem",	"Recursos" , false, true)
	mRGM:addResourceLocation("media/materials/programs/GLSL",				"FileSystem",	"Recursos" , false, true)

	mRGM:initialiseAllResourceGroups()
end
function createScene()
	local ent
	local light
	mSceneMgr:setAmbientLight(Ogre.ColourValue(0.9, 0.9, 0.9, 1.0))
	
	ent = mSceneMgr:createEntity("Ninja","ninja.mesh", "General")
	local node = mSceneMgr:getRootSceneNode():createChildSceneNode("node", Ogre.Vector3(0,0,0),Ogre.Quaternion(1,0,0,0))
	node:attachObject(ent)
	mCamera:lookAt(node:getPosition())
	
	light = mSceneMgr:createLight("Light1")
	light:setPosition(Ogre.Vector3(0,150,250))
	light:setDiffuseColour(Ogre.ColourValue(1.0, 0.0, 0.0, 1.0));
	light:setSpecularColour(Ogre.ColourValue(1.0, 0.0, 0.0,1.0));
	
	light = mSceneMgr:createLight("Light2")
	light:setPosition(Ogre.Vector3(0,150,-250))
	light:setDiffuseColour(Ogre.ColourValue(0.25, 0.25, 0,1.0));
	light:setSpecularColour(Ogre.ColourValue(0.25, 0.25, 0,1.0));
	
	
end
initOgre()
createCamera()
createViewports()
initResources()
createScene()
local mTime = 0
local mFPS = 0
function exampleFrameListener(evt)
	if mWindow:isClosed() then
		return false;
	end
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

mRoot:startRendering()

```
