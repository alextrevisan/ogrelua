local this = {}
local math = math
local count = 1
function  this.create(mSceneMgr, resx, resy)
    local mInstance = {}
    mInstance.mFieldX = resx or 400
    mInstance.mFieldY = resy or 200
    
    mInstance.mShipEntity = mSceneMgr:createEntity("RZR-002","RZR-002.mesh", "General")
    mInstance.mShipNode = mSceneMgr:getRootSceneNode():createChildSceneNode("node"..count, Ogre.Vector3(0,0,-100),Ogre.Quaternion(1,0,0,0))
    mInstance.mShipNode:attachObject(mInstance.mShipEntity)
    count = count+1
    
    mInstance.mShipNode:setScale(3.0,3.0,3.0)
    mInstance.mShipNode:pitch(Ogre.Radian(Ogre.Degree(90)),Ogre.SceneNode.TS_WORLD)
    mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(180)),Ogre.SceneNode.TS_WORLD)
    
    mInstance.mShipMaxSpeed = 200.0
    mInstance.mShipRotateSpeed = Ogre.Degree(20)
    
    mInstance.mTimeSinceLastFrame = 0.0
    
    mInstance.mShipMovement = Ogre.Vector3(0,0,0)
    
    mInstance.die = function()
        mInstance.mShipNode:setVisible(false)
    end
    mInstance.reset = function()
        mInstance.mShipNode:setPosition(Ogre.Vector3(0,0,-100.0))
        mInstance.mShipNode:setVisible(true)
        mInstance.mShipSpeed = Ogre.Vector3(0,0,0)
    end
    mInstance.update = function(timeSinceLastFrame)
        local translate = Ogre.Vector3(mInstance.mShipMovement.x * timeSinceLastFrame,mInstance.mShipMovement.y * timeSinceLastFrame,mInstance.mShipMovement.z * timeSinceLastFrame)
        mInstance.mShipNode:translate(translate, Ogre.SceneNode.TS_WORLD)
        mInstance.mShipMovement = Ogre.Vector3(0,0,0)
    end
    mInstance.moveForward = function()
        mInstance.mShipMovement = Ogre.Vector3(mInstance.mShipMovement.x,mInstance.mShipMovement.y + mInstance.mShipMaxSpeed,mInstance.mShipMovement.z)
    end
    mInstance.moveBackwars = function()
        mInstance.mShipMovement = Ogre.Vector3(mInstance.mShipMovement.x,mInstance.mShipMovement.y -mInstance.mShipMaxSpeed ,mInstance.mShipMovement.z)
    end
    mInstance.turnLeft = function()
        mInstance.mShipMovement = Ogre.Vector3(-mInstance.mShipMaxSpeed + mInstance.mShipMovement.x,mInstance.mShipMovement.y ,mInstance.mShipMovement.z)
        mInstance.mIsTurningLeft = true
    end
    mInstance.turnRight = function()
        mInstance.mShipMovement = Ogre.Vector3(mInstance.mShipMaxSpeed + mInstance.mShipMovement.x,mInstance.mShipMovement.y ,mInstance.mShipMovement.z)
        mInstance.mIsTurningLeft = true
    end
    return mInstance
end

return this