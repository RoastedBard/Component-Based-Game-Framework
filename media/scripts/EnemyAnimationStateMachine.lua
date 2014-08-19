EnemyAnimationStateMachine =
{

}

function EnemyAnimationStateMachine:start()

end

function EnemyAnimationStateMachine:update(dt)

	currentAnimation = self.owner:getComponentAnimation(Enums.COMPONENT_ANIMATION):getCurrentAnimation()
	direction = self.owner:getComponentMovement(Enums.COMPONENT_MOVEMENT).direction
	isOnTheGround = self.owner:getComponentMovement(Enums.COMPONENT_MOVEMENT).isOnTheGround

	if currentAnimation == Enums.ANIMATION_WALK_LEFT then

		if direction == Enums.DIRECTION_RIGHT then
			currentAnimation = Enums.ANIMATION_WALK_RIGHT
		end

	elseif currentAnimation == Enums.ANIMATION_WALK_RIGHT then

		if 	direction == Enums.DIRECTION_LEFT then
			currentAnimation = Enums.ANIMATION_WALK_LEFT
		end
	end

	self.owner:getComponentAnimation(Enums.COMPONENT_ANIMATION):setCurrentAnimation(currentAnimation)
end
