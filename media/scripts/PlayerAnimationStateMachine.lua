function update(direction, currentAnimation, isOnTheGround)

	if currentAnimation == Enums.ANIMATION_STAND_LEFT then

		if direction == Enums.DIRECTION_LEFT then
			currentAnimation = Enums.ANIMATION_WALK_LEFT

		elseif 	direction == Enums.DIRECTION_RIGHT then
			currentAnimation = Enums.ANIMATION_WALK_RIGHT

		elseif 	direction == Enums.DIRECTION_UP then
			currentAnimation = Enums.ANIMATION_JUMP_LEFT
		end

	elseif currentAnimation == Enums.ANIMATION_STAND_RIGHT then

		if direction == Enums.DIRECTION_LEFT then
			currentAnimation = Enums.ANIMATION_WALK_LEFT

		elseif 	direction == Enums.DIRECTION_RIGHT then
			currentAnimation = Enums.ANIMATION_WALK_RIGHT

		elseif 	direction == Enums.DIRECTION_UP then
			currentAnimation = Enums.ANIMATION_JUMP_RIGHT
		end

	elseif currentAnimation == Enums.ANIMATION_WALK_LEFT then

		if direction == Enums.DIRECTION_NONE then
			currentAnimation = Enums.ANIMATION_STAND_LEFT

		elseif 	direction == Enums.DIRECTION_RIGHT then
			currentAnimation = Enums.ANIMATION_WALK_RIGHT

		elseif 	direction == Enums.DIRECTION_UP then
			currentAnimation = Enums.ANIMATION_JUMP_LEFT
		end

	elseif currentAnimation == Enums.ANIMATION_WALK_RIGHT then

		if direction == Enums.DIRECTION_NONE then
			currentAnimation = Enums.ANIMATION_STAND_RIGHT

		elseif 	direction == Enums.DIRECTION_LEFT then
			currentAnimation = Enums.ANIMATION_WALK_LEFT

		elseif 	direction == Enums.DIRECTION_UP then
			currentAnimation = Enums.ANIMATION_JUMP_RIGHT
		end

	elseif currentAnimation == Enums.ANIMATION_JUMP_LEFT then

		if direction == Enums.DIRECTION_RIGHT then
			currentAnimation = Enums.ANIMATION_JUMP_RIGHT

		elseif 	isOnTheGround == true then

			if currentAnimation == Enums.ANIMATION_JUMP_LEFT then
				currentAnimation = Enums.ANIMATION_STAND_LEFT

			elseif currentAnimation == Enums.ANIMATION_JUMP_RIGHT then
				currentAnimation = Enums.ANIMATION_STAND_RIGHT
			end

		end

	elseif currentAnimation == Enums.ANIMATION_JUMP_RIGHT then

		if direction == Enums.DIRECTION_LEFT then
			currentAnimation = Enums.ANIMATION_JUMP_LEFT

		elseif 	isOnTheGround == true then

			if currentAnimation == Enums.ANIMATION_JUMP_LEFT then
				currentAnimation = Enums.ANIMATION_STAND_LEFT

			elseif currentAnimation == Enums.ANIMATION_JUMP_RIGHT then
				currentAnimation = Enums.ANIMATION_STAND_RIGHT
			end

		end
	end
end
