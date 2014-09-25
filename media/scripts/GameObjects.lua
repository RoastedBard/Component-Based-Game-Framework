GameObjects =
{
	--Player
	{
		posX = 200,
		posY = 10,

		components =
		{
			Enums.COMPONENT_ANIMATION,
		    Enums.COMPONENT_PLATFORMER_CONTROLLER,
			Enums.COMPONENT_MOVEMENT,
	        Enums.COMPONENT_PLATFORMER_PHYSICS,
			Enums.COMPONENT_SCRIPT,
			Enums.COMPONENT_COLLIDER
		},

		movement =
		{
			velocityX = 0,
			velocityY = 0,
			accelerationX = 0.03,
			accelerationy = 4.75,
			maxVelocityX = 0,
			maxVelocityY = 0,
			direction = Enums.DIRECTION_NONE,
			isJumping = 0,
			isOnTheGround = 0
		},

		collider =
		{
			bodyType = Enums.BODY_DYNAMIC,
			minX = 200,
			minY = 10,
			width = 17,
			height = 32,
			footSensor = 1 --Player have foot sensor
		},

		textures =
		{
			textureId = "TexturePlayer",
			texture = "media/sprites/marioRunning.png"
		},

		animations =
		{
			--int animationId, int startframeX, int startframeY, int frameWidth, int frameHeight, int framesCount,
			--int animationSpeed, bool horizontal, bool horizontalFlip, bool verticalFlip
			{
				Enums.ANIMATION_WALK_LEFT,
				0, 0, 17, 32, 3, 70, 1, 1, 0
			},
			{
				Enums.ANIMATION_STAND_RIGHT,
				51, 0, 17, 32, 1, 0, 1, 0, 0
			},
			{
				Enums.ANIMATION_STAND_LEFT,
				51, 0, 17, 32, 1, 0, 1, 1, 0
			},
			{
				Enums.ANIMATION_WALK_RIGHT,
				0, 0, 17, 32, 3, 70, 1, 0, 0
			},
			{
				Enums.ANIMATION_JUMP_LEFT,
				68, 0, 17, 32, 1, 0, 1, 0, 0
			},
			{
				Enums.ANIMATION_JUMP_RIGHT,
				68, 0, 17, 32, 1, 0, 1, 1, 0
			}
		},

		scripts =
		{
			"media/scripts/PlayerAnimationStateMachine.lua"
			--"media/scripts/ReactOnCollision.lua"
		}
	},

	--Running guy
--~ 	{
--~ 		posX = 300,
--~ 		posY = 100,

--~ 		components =
--~ 		{
--~ 			Enums.COMPONENT_ANIMATION,
--~ 			Enums.COMPONENT_MOVEMENT,
--~ 	        --Enums.COMPONENT_PLATFORMER_PHYSICS,
--~ 			Enums.COMPONENT_SCRIPT
--~ 		},

--~ 		movement =
--~ 		{
--~ 			velocityX = 0,
--~ 			velocityY = 0,
--~ 			accelerationX = 0.05,
--~ 			accelerationy = 4.75,
--~ 			maxVelocityX = 0.1,
--~ 			maxVelocityY = 0,
--~ 			direction = Enums.DIRECTION_NONE,
--~ 			isJumping = 0,
--~ 			isOnTheGround = 0
--~ 		},

--~ 		textures =
--~ 		{
--~ 			textureId = Enums.TEXTURE_PLAYER
--~ 		},

--~ 		animations =
--~ 		{
--~ 		    --int animationId, int startframeX, int startframeY, int frameWidth, int frameHeight, int framesCount,
--~ 			--int animationSpeed, bool horizontal, bool horizontalFlip, bool verticalFlip
--~ 			{
--~ 				Enums.ANIMATION_WALK_LEFT,
--~ 				0, 32, 17, 32, 3, 70, 1, 1, 0
--~ 			},
--~ 			{
--~ 				Enums.ANIMATION_WALK_RIGHT,
--~ 				0, 32, 17, 32, 3, 70, 1, 0, 0
--~ 			}
--~ 		},

--~ 		scripts =
--~ 		{
--~ 			"media/scripts/EnemyAnimationStateMachine.lua",
--~ 			"media/scripts/EnemyPatrollingScript.lua",
--~ 			"media/scripts/EnemyPhysics.lua"
--~ 		}
--~ 	},

--~ 		--Running guy 1
--~ 	{
--~ 		posX = 500,
--~ 		posY = 100,

--~ 		components =
--~ 		{
--~ 			Enums.COMPONENT_ANIMATION,
--~ 			Enums.COMPONENT_MOVEMENT,
--~ 	        --Enums.COMPONENT_PLATFORMER_PHYSICS,
--~ 			Enums.COMPONENT_SCRIPT
--~ 		},

--~ 		movement =
--~ 		{
--~ 			velocityX = 0,
--~ 			velocityY = 0,
--~ 			accelerationX = 0.03,
--~ 			accelerationy = 4.75,
--~ 			maxVelocityX = 0.2,
--~ 			maxVelocityY = 0,
--~ 			direction = Enums.DIRECTION_NONE,
--~ 			isJumping = 0,
--~ 			isOnTheGround = 0
--~ 		},

--~ 		textures =
--~ 		{
--~ 			textureId = Enums.TEXTURE_PLAYER
--~ 		},

--~ 		animations =
--~ 		{
--~ 			{
--~ 				Enums.ANIMATION_WALK_LEFT,
--~ 				0, 32, 17, 32, 3, 70, 1, 1, 0
--~ 			},
--~ 			{
--~ 				Enums.ANIMATION_WALK_RIGHT,
--~ 				0, 32, 17, 32, 3, 70, 1, 0, 0
--~ 			}
--~ 		},

--~ 		scripts =
--~ 		{
--~ 			"media/scripts/EnemyAnimationStateMachine.lua",
--~ 			"media/scripts/EnemyPatrollingScript.lua",
--~ 			"media/scripts/EnemyPhysics.lua"
--~ 		}
--~ 	},

--~ 		--Running guy 2
--~ 	{
--~ 		posX = 200,
--~ 		posY = 100,

--~ 		components =
--~ 		{
--~ 			Enums.COMPONENT_ANIMATION,
--~ 			Enums.COMPONENT_MOVEMENT,
--~ 	        --Enums.COMPONENT_PLATFORMER_PHYSICS,
--~ 			Enums.COMPONENT_SCRIPT
--~ 		},

--~ 		movement =
--~ 		{
--~ 			velocityX = 0,
--~ 			velocityY = 0,
--~ 			accelerationX = 0.076,
--~ 			accelerationy = 4.75,
--~ 			maxVelocityX = 0.3,
--~ 			maxVelocityY = 0,
--~ 			direction = Enums.DIRECTION_NONE,
--~ 			isJumping = 0,
--~ 			isOnTheGround = 0
--~ 		},

--~ 		textures =
--~ 		{
--~ 			textureId = Enums.TEXTURE_PLAYER
--~ 		},

--~ 		animations =
--~ 		{
--~ 			{
--~ 				Enums.ANIMATION_WALK_LEFT,
--~ 				0, 32, 17, 32, 3, 70, 1, 1, 0
--~ 			},
--~ 			{
--~ 				Enums.ANIMATION_WALK_RIGHT,
--~ 				0, 32, 17, 32, 3, 70, 1, 0, 0
--~ 			}
--~ 		},

--~ 		scripts =
--~ 		{
--~ 			"media/scripts/EnemyAnimationStateMachine.lua",
--~ 			"media/scripts/EnemyPatrollingScript.lua",
--~ 			"media/scripts/EnemyPhysics.lua"
--~ 		}
--~ 	},

--~ 		--Running guy 3
--~ 	{
--~ 		posX = 100,
--~ 		posY = 100,

--~ 		components =
--~ 		{
--~ 			Enums.COMPONENT_ANIMATION,
--~ 			Enums.COMPONENT_MOVEMENT,
--~ 	        --Enums.COMPONENT_PLATFORMER_PHYSICS,
--~ 			Enums.COMPONENT_SCRIPT
--~ 		},

--~ 		movement =
--~ 		{
--~ 			velocityX = 0,
--~ 			velocityY = 0,
--~ 			accelerationX = 0.027,
--~ 			accelerationy = 4.75,
--~ 			maxVelocityX = 0.27,
--~ 			maxVelocityY = 0,
--~ 			direction = Enums.DIRECTION_NONE,
--~ 			isJumping = 0,
--~ 			isOnTheGround = 0
--~ 		},

--~ 		textures =
--~ 		{
--~ 			textureId = Enums.TEXTURE_PLAYER
--~ 		},

--~ 		animations =
--~ 		{
--~ 			{
--~ 				Enums.ANIMATION_WALK_LEFT,
--~ 				0, 32, 17, 32, 3, 70, 1, 1, 0
--~ 			},
--~ 			{
--~ 				Enums.ANIMATION_WALK_RIGHT,
--~ 				0, 32, 17, 32, 3, 70, 1, 0, 0
--~ 			}
--~ 		},

--~ 		scripts =
--~ 		{
--~ 			"media/scripts/EnemyAnimationStateMachine.lua",
--~ 			"media/scripts/EnemyPatrollingScript.lua",
--~ 			"media/scripts/EnemyPhysics.lua"
--~ 		}
--~ 	},

--~ 		--Running guy 4
--~ 	{
--~ 		posX = 250,
--~ 		posY = 100,

--~ 		components =
--~ 		{
--~ 			Enums.COMPONENT_ANIMATION,
--~ 			Enums.COMPONENT_MOVEMENT,
--~ 	        --Enums.COMPONENT_PLATFORMER_PHYSICS,
--~ 			Enums.COMPONENT_SCRIPT
--~ 		},

--~ 		movement =
--~ 		{
--~ 			velocityX = 0,
--~ 			velocityY = 0,
--~ 			accelerationX = 0.03,
--~ 			accelerationy = 4.75,
--~ 			maxVelocityX = 0.167,
--~ 			maxVelocityY = 0,
--~ 			direction = Enums.DIRECTION_NONE,
--~ 			isJumping = 0,
--~ 			isOnTheGround = 0
--~ 		},

--~ 		textures =
--~ 		{
--~ 			textureId = Enums.TEXTURE_PLAYER
--~ 		},

--~ 		animations =
--~ 		{
--~ 			{
--~ 				Enums.ANIMATION_WALK_LEFT,
--~ 				0, 32, 17, 32, 3, 70, 1, 1, 0
--~ 			},
--~ 			{
--~ 				Enums.ANIMATION_WALK_RIGHT,
--~ 				0, 32, 17, 32, 3, 70, 1, 0, 0
--~ 			}
--~ 		},

--~ 		scripts =
--~ 		{
--~ 			"media/scripts/EnemyAnimationStateMachine.lua",
--~ 			"media/scripts/EnemyPatrollingScript.lua",
--~ 			"media/scripts/EnemyPhysics.lua"
--~ 		}
--~ 	},

	--platform
	{
		posX = 300,
		posY = 100,

		components =
		{
			Enums.COMPONENT_SPRITE,
			Enums.COMPONENT_MOVEMENT,
			Enums.COMPONENT_SCRIPT,
			Enums.COMPONENT_COLLIDER
		},

		movement =
		{
			velocityX = 0,
			velocityY = 0,
			accelerationX = 0.003,
			accelerationy = 4.75,
			maxVelocityX = 0.3,
			maxVelocityY = 0,
			direction = Enums.DIRECTION_NONE,
			isJumping = 0,
			isOnTheGround = 0
		},

		collider =
		{
			bodyType = Enums.BODY_KINEMATIC,
			minX = 300,
			minY = 100,
			width = 100,
			height = 20,
			footSensor = 0
		},

		textures =
		{
			textureId = "TexturePlatform",
			texture = "media/sprites/platform.png"
		},

		sprite =
		{
			0, 0, 100, 20, 0, 0
		},

		scripts =
		{
			"media/scripts/EnemyPatrollingScript.lua"
		}
	},

	--platform 2
	{
		posX = 300,
		posY = 200,

		components =
		{
			Enums.COMPONENT_SPRITE,
			Enums.COMPONENT_MOVEMENT,
			Enums.COMPONENT_SCRIPT,
			Enums.COMPONENT_COLLIDER
		},

		movement =
		{
			velocityX = 0,
			velocityY = 0,
			accelerationX = 0.004,
			accelerationy = 4.75,
			maxVelocityX = 0.3,
			maxVelocityY = 0,
			direction = Enums.DIRECTION_NONE,
			isJumping = 0,
			isOnTheGround = 0
		},

		collider =
		{
			bodyType = Enums.BODY_KINEMATIC,
			minX = 300,
			minY = 200,
			width = 100,
			height = 20,
			footSensor = 0
		},

		textures =
		{
			textureId = "TexturePlatform",
		    texture = "media/sprites/platform.png"
		},

		sprite =
		{
			0, 0, 100, 20, 0, 0
		},

		scripts =
		{
			"media/scripts/EnemyPatrollingScript.lua"
		}
	},

	--platform 3
	{
		posX = 300,
		posY = 350,

		components =
		{
			Enums.COMPONENT_SPRITE,
			Enums.COMPONENT_MOVEMENT,
			Enums.COMPONENT_SCRIPT,
			Enums.COMPONENT_COLLIDER
		},

		movement =
		{
			velocityX = 0,
			velocityY = 0,
			accelerationX = 0.002,
			accelerationy = 4.75,
			maxVelocityX = 0.3,
			maxVelocityY = 0,
			direction = Enums.DIRECTION_NONE,
			isJumping = 0,
			isOnTheGround = 0
		},

		collider =
		{
			bodyType = Enums.BODY_KINEMATIC,
			minX = 300,
			minY = 350,
			width = 100,
			height = 20,
			footSensor = 0
		},

		textures =
		{
			textureId = "TexturePlatform",
			texture = "media/sprites/platform.png"
		},

		sprite =
		{
			0, 0, 100, 20, 0, 0
		},

		scripts =
		{
			--"media/scripts/EnemyPatrollingScript.lua"
		}
	},

	--Floor
	{
		posX = 0,
		posY = 450,

		components =
		{
			Enums.COMPONENT_SPRITE,
			Enums.COMPONENT_COLLIDER
		},

		collider =
		{
			bodyType = Enums.BODY_STATIC,
			minX = 0,
			minY = 450,
			width = 1024,
			height = 20,
			footSensor = 0
		},

		textures =
		{
			textureId = "TexturePlatform",
		    texture = "media/sprites/platform.png"
		},

		sprite =
		{
			0, 0, 1024, 20, 0, 0
		}
	}
}
