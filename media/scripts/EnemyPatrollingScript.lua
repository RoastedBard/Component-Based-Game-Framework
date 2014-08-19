EnemyPatrollingScript =
{
	transform = 0,
	movement  = 0,
	patrolRange = 100,
	startPos = 0,
	maxVel = 0
}

function EnemyPatrollingScript:update(dt)

	self:patrol(dt)

end

function EnemyPatrollingScript:start()

	print("start")
	self.startPos = self.owner:getTranformComponent().position.x
	maxVel = self.owner:getComponentMovement(Enums.COMPONENT_MOVEMENT).maxVelocity.x;
end

function EnemyPatrollingScript:lerp(maximum, current, acceleration)

	difference = maximum - current

	if difference > acceleration then
		return current + acceleration
	end

	if difference < (-acceleration) then
		return current - acceleration
	end

	return maximum

end

function EnemyPatrollingScript:patrol(dt)

	--print("patrolling")
	transform = self.owner:getTranformComponent()
	movement  = self.owner:getComponentMovement(Enums.COMPONENT_MOVEMENT)


	--Shoud be like this(but not that ugly!):

	if (transform.position.x >= self.startPos + self.patrolRange) then
		movement.direction = Enums.DIRECTION_LEFT
		movement.maxVelocity.x = -maxVel
	end

	if (transform.position.x <= self.startPos) then

		if (movement.maxVelocity.x < 0) then
			movement.direction = Enums.DIRECTION_RIGHT
			movement.maxVelocity.x = maxVel
		end
	end

--~ 	if movement.velocity.x == movement.maxVelocity.x then
--~ 		movement.maxVelocity.x = -movement.maxVelocity.x
--~ 	end

	movement.velocity.x = self:lerp(movement.maxVelocity.x, movement.velocity.x, movement.acceleration.x)

	transform.position.x = transform.position.x + (movement.velocity.x * dt);
end
