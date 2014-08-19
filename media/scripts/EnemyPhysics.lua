EnemyPhysics =
{
	transform = 0,
	movement  = 0
}

function EnemyPhysics:update(dt)

	self:performGravity(dt)

end

function EnemyPhysics:start()

	print("start")


end

function EnemyPhysics:performGravity(dt)

	transform = self.owner:getTranformComponent()
	movement  = self.owner:getComponentMovement(Enums.COMPONENT_MOVEMENT)

	if transform.position.y >= 400 then
		transform.position.y = 400

		movement.velocity.y = 0
		movement.maxVelocity.y = 0
		movement.isOnTheGround = true
		movement.isJumping = false

	else
		movement.velocity.y = movement.velocity.y + (0.3 * dt)
	end

	transform.position.y = transform.position.y + movement.velocity.y * dt;
end

function EnemyPhysics:performMovement(dt)



end
