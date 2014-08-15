EnemyPatrollingScript =
{
}

function EnemyPatrollingScript:update(dt)

	self:patrol(dt)

end

function EnemyPatrollingScript:start()

	print("start")

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

	if movement.velocity.x == movement.maxVelocity.x then
		movement.maxVelocity.x = -movement.maxVelocity.x
	end

	movement.velocity.x = self:lerp(movement.maxVelocity.x, movement.velocity.x, movement.acceleration.x)

	transform.position.x = transform.position.x + movement.velocity.x * dt;
end
