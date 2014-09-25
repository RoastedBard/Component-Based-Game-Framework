ReactOnCollision =
{

}

function ReactOnCollision:update(dt)

	self:onCollision()

end

function ReactOnCollision:start()

	print("start")

end

function ReactOnCollision:onCollision()

	collider = self.owner:getComponentCollider(Enums.COMPONENT_COLLIDER)
	movement  = self.owner:getComponentMovement(Enums.COMPONENT_MOVEMENT)

	if collider:isCollided() == true then
		print(">Collision occured lua")
		movement.maxVelocity.x = 0
		movement.maxVelocity.y = 0
	end

end
