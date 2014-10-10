ogrelua
=======

Lua bindings for Ogre3D


#### Simple Lua example ####

```Lua
require("ogrelua")
local mRoot = Ogre.Root("plugins.cfg", "video.cfg", "Graphicslog.txt")
if mRoot:restoreConfig() == false then
	mRoot:showConfigDialog()
end

local mWindow = mRoot:initialise(true,"Lua + Ogre Rocks!!!","")

local mSceneMgr = mRoot:createSceneManager(Ogre.ST_GENERIC,"")

local mCamera = mSceneMgr:createCamera("Camera")
local vp = mWindow:addViewport(mCamera,0,0.0,0.0,1.0,1.0);
vp:setBackgroundColour(Ogre.ColourValue(0.0,0.0,0.0,1.0))

mCamera:setPosition(2.0, 2.0, 27.5)
mCamera:lookAt(0.0,0.0,0.0)
mCamera:setNearClipDistance(1)
mCamera:setFarClipDistance(1000)

mRGM = Ogre.ResourceGroupManager()

mRGM:addResourceLocation("media/packs/SdkTrays.zip",	"Zip",			"Essencial", false, true)
mRGM:addResourceLocation("media/materials/scripts",	    "FileSystem",	"Recursos" , false, true)
mRGM:addResourceLocation("media/materials/textures",	"FileSystem",	"Recursos" , false, true)
mRGM:addResourceLocation("media/models",				"FileSystem",	"Recursos" , false, true)

mRGM:initialiseAllResourceGroups()

```
