--Container of script sets for each Game Object
GameObjectScriptTables =
{

}

--Add new table for 'gameObject' in GameObjectScriptTables
function addGameObjectScriptSet(gameObject)

	if GameObjectScriptTables[gameObject] == nil then
		print("adding game object set: "..gameObject)
		GameObjectScriptTables[gameObject] = {}
	else
		print("Script set for game object ", gameObject, "is already exist!\n")
	end

end

--Add 'script' in 'gameObject' set in GameObjectScriptTables
function addScript(script, gameObject, owner)

	if GameObjectScriptTables[gameObject] == nil then
		print("You can't add any scripts! Game object script table for game object ", gameObject, " is empty!\n")
		return
	end

	if #GameObjectScriptTables[gameObject] == 0 then
		j = 1
	else
		j = #GameObjectScriptTables[gameObject] + 1
	end

	print("adding script "..script.." for: "..gameObject)
	GameObjectScriptTables[gameObject][j] = _G[script]
	addOwnerGameObject(gameObject, j, owner)
	--table.insert(GameObjectScriptTables[gameObject][script], _G[script])
end

--Add owner game object
function addOwnerGameObject(gameObject, script, owner)

	print("adding OWNER")
	GameObjectScriptTables[gameObject][script]["owner"] = owner

end

--Run 'start()' for all scripts
function startScripts()

	if #GameObjectScriptTables == 0 then
		print("#GameObjectScriptTables = 0")
		return
	end

	for i = 1, #GameObjectScriptTables do

		print("GO script set N-",i)

		for j = 1, #GameObjectScriptTables[i] do
			--if type(GameObjectScriptTables[i][j]) == "table" then

				GameObjectScriptTables[i][j]:start()
			--end
		end

	end

end

--Run 'update()' for all scripts
function updateScripts(dt)

	for i = 1, #GameObjectScriptTables do

		--print("GO script set N-",i)

		for j = 1, #GameObjectScriptTables[i] do
			--if type(GameObjectScriptTables[i][j]) == "table" then
				GameObjectScriptTables[i][j]:update(dt)
			--end
		end

	end

end

--Run 'start()' for scripts in 'gameObject' set
function startScriptsGameObject(gameObject)

	print("GO script set N-",gameObject)

	for j = 1, #GameObjectScriptTables[gameObject] do
		if type(GameObjectScriptTables[gameObject][j]) == "table" then
			GameObjectScriptTables[gameObject][j]:start()
		end
	end

end

--Run 'update()' for scripts in 'gameObject' set
function updateScriptsGameObject(gameObject)

	print("GO script set N-",gameObject)

	for j = 1, #GameObjectScriptTables[gameObject] do
		if type(GameObjectScriptTables[gameObject][j]) == "table" then
			GameObjectScriptTables[gameObject][j]:update()
		end
	end

end
