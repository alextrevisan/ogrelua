require("ogrelua")

local mRoot = Ogre.Root("plugins.cfg", "video.cfg", "Graphicslog.txt")
if mRoot:restoreConfig() == false then
    mRoot:showConfigDialog()
end