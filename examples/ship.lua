local this = {}
local math = math
local count = 1
function  this.create(mSceneMgr)
    local mInstance = {}
    mInstance.mFieldX = 400
    mInstance.mFieldY = 200
    
    mInstance.mShipEntity = mSceneMgr:createEntity("RZR-002","RZR-002.mesh", "General")
    mInstance.mShipNode = mSceneMgr:getRootSceneNode():createChildSceneNode("node"..count, Ogre.Vector3(0,0,-100),Ogre.Quaternion(1,0,0,0))
    mInstance.mShipNode:attachObject(mInstance.mShipEntity)
    count = count+1
    
    mInstance.mShipNode:setScale(3.0,3.0,3.0)
    mInstance.mShipNode:pitch(Ogre.Radian(Ogre.Degree(90)),Ogre.SceneNode.TS_LOCAL)
    mInstance.mShipNode:yaw(Ogre.Radian(Ogre.Degree(180)),Ogre.SceneNode.TS_LOCAL)
    
    mInstance.mShipOrientation = 0.0
    mInstance.mShipAccelerate = false
    mInstance.mShipAcceleration = 100.0
    mInstance.mShipMaxSpeed = 200.0
    mInstance.mShipSpeed = Ogre.Vector3(0,0,0)
    mInstance.mShipRotateSpeed = Ogre.Degree(20)
    mInstance.mShipRotation = Ogre.Degree(0.0)
    
    mInstance.mIsTurningLeft = false
    mInstance.mIsTurningRight = false
    mInstance.mIsStillInTurnLeft = false
    mInstance.mIsStillInTurnRight = false
    mInstance.mTimeSinceLastFrame = 0.0
    
    
    mInstance.die = function()
        mInstance.mShipNode:setVisible(false)
    end
    mInstance.reset = function()
        mInstance.mShipNode:setPosition(Ogre.Vector3(0,0,-100.0))
        mInstance.mShipNode:setVisible(true)
        mInstance.mShipSpeed = Ogre.Vector3(0,0,0)
    end
    mInstance.update = function(timeSinceLastFrame)
        if mInstance.mShipAccelerate then
            local xAcc = 0
            local yAcc = 0
            local angle = mInstance.mShipNode:getOrientation():getRoll():valueRadians()
            local angleDegree = mInstance.mShipNode:getOrientation():getRoll():valueDegrees()
            if angleDegree <= 90.0 and angleDegree > 0 then
                xAcc = math.cos(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
                yAcc = math.sin(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
            elseif angleDegree <= 180.0 and angleDegree > 90.0 then
                xAcc = -math.cos(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
                yAcc = math.sin(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
            elseif angleDegree <= 270.0 and angleDegree > 180.0 then
                xAcc = -math.cos(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
                yAcc = -math.sin(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
            elseif angleDegree > 270.0 and angleDegree < 360.0 then
                xAcc = math.cos(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
                yAcc = -math.sin(angle) * mInstance.mShipAcceleration * timeSinceLastFrame
            end
            
            
            
            if (math.abs(mInstance.mShipSpeed.x) + math.abs(mInstance.mShipSpeed.y) + xAcc) < mInstance.mShipMaxSpeed then 
                mInstance.mShipSpeed.x = mInstance.mShipSpeed.x + xAcc
            end
            if (math.abs(mInstance.mShipSpeed.x) + math.abs(mInstance.mShipSpeed.y) + yAcc) < mInstance.mShipMaxSpeed then 
                mInstance.mShipSpeed.y = mInstance.mShipSpeed.y + yAcc
            end
        end
        local shipMovement = Ogre.Vector3(mInstance.mShipSpeed.x * timeSinceLastFrame,mInstance.mShipSpeed.y * timeSinceLastFrame,0)
        mInstance.mShipNode:translate(shipMovement, Ogre.SceneNode.TS_WORLD)
        
        local position = mInstance.mShipNode:getPosition()
 
        if position.x > mInstance.mFieldX then position.x = -mInstance.mFieldX end
        if position.x < -mInstance.mFieldX then position.x = mInstance.mFieldX end
        if position.y > mInstance.mFieldY then position.y = -mInstance.mFieldY end
        if position.y < -mInstance.mFieldY then position.y = mInstance.mFieldY end
        
        if position ~= mInstance.mShipNode:getPosition() then
            mInstance.mShipNode:setPosition(position.x,position.y, position.z)
        end
        
        if mInstance.mIsTurningLeft then
            if not mInstance.mIsStillInTurnLeft then
                mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(-20)),Ogre.SceneNode.TS_WORLD)
                mInstance.mIsStillInTurnLeft = true
            end
            mInstance.mIsTurningLeft = false;
        elseif mInstance.mIsStillInTurnLeft then
            mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(20)),Ogre.SceneNode.TS_WORLD)
            mInstance.mIsStillInTurnLeft = false
        end
        if mInstance.mIsTurningRight then
            if not mIsStillInTurnRight then
                mInstance.mShipNode:roll(Ogre.Degree(20),Ogre.SceneNode.TS_WORLD)
                mInstance.mIsStillInTurnRight = true
            end
            mInstance.mIsTurningRight = false
        elseif mInstance.mIsStillInTurnRight then
            mInstance.mShipNode:roll(Ogre.Degree(-20))
            mInstance.mIsStillInTurnRight = false
        end
     
        mInstance.mShipNode:roll(Ogre.Radian(mInstance.mShipRotation), Ogre.SceneNode.TS_WORLD);
        mInstance.mShipRotation = Ogre.Degree(0.0);
        mInstance.mTimeSinceLastFrame = timeSinceLastFrame or 0.0
        print(mInstance.mShipNode:getOrientation():getRoll():valueDegrees())
    end
    mInstance.turnLeft = function()
        mInstance.mShipOrientation = mInstance.mShipNode:getOrientation():getRoll():valueDegrees()
        mInstance.mShipRotation = Ogre.Degree(mInstance.mShipRotateSpeed:valueDegrees() * mInstance.mTimeSinceLastFrame)
        if mInstance.mShipOrientation > 360.0 then
            mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(-360.0)), Ogre.SceneNode.TS_WORLD)
        end
        if mInstance.mShipOrientation < 0.0 then
            mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(360.0)), Ogre.SceneNode.TS_WORLD)
        end
        mInstance.mIsTurningLeft = true
    end
    mInstance.turnRight = function()
        mInstance.mShipOrientation = Ogre.Degree(mInstance.mShipOrientation - mInstance.mShipRotateSpeed:valueDegrees() * mInstance.mTimeSinceLastFrame)
        mInstance.mShipRotation = Ogre.Degree(mInstance.mShipRotateSpeed:valueDegrees() * -mInstance.mTimeSinceLastFrame)
        if mInstance.mShipOrientation > 360.0 then
            mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(-360.0)), Ogre.SceneNode.TS_WORLD)
        end
        if mInstance.mShipOrientation < 0.0 then
            mInstance.mShipNode:roll(Ogre.Radian(Ogre.Degree(360.0)), Ogre.SceneNode.TS_WORLD)
        end
        
        mInstance.mIsTurningRight= true
    end
    mInstance.accelerate = function(todo) 
        mInstance.mShipAccelerate = todo
    end
    return mInstance
end

return this