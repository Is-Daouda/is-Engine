# game source file
set(
    app_src
	
	# game system extended
	app_src/gamesystem_ext/GameSystemExtended.cpp

	# game scene
	app_src/scenes/GameEndScreen/GameEndScreen.cpp
	app_src/scenes/GameIntro/GameIntro.cpp
	app_src/scenes/GameLevel/GameLevelConstructor.cpp
	app_src/scenes/GameLevel/GameLevelLoadResource.cpp
	app_src/scenes/GameLevel/GameLevelStep.cpp
	app_src/scenes/GameLevel/GameLevelStepGamePlay.cpp
	app_src/scenes/GameLevel/GameLevelStepSubFunction.cpp
	app_src/scenes/GameMenu/GameMenu.cpp
	app_src/scenes/GameMenu/GameMenuDraw.cpp
	app_src/scenes/GameMenu/GameMenuLoadResource.cpp
	app_src/scenes/GameOver/GameOver.cpp

	# game level objects
	app_src/objects/gamelevel/Block.cpp
	app_src/objects/gamelevel/BlockPhysic.cpp
	app_src/objects/gamelevel/Bonus.cpp
	app_src/objects/gamelevel/ElectroShock.cpp
	app_src/objects/gamelevel/Enemy.cpp
	app_src/objects/gamelevel/FinishObject.cpp
	app_src/objects/gamelevel/HUD.cpp
	app_src/objects/gamelevel/LevelTile.cpp
	app_src/objects/gamelevel/LevelTitle.cpp
	app_src/objects/gamelevel/Limiter.cpp
	app_src/objects/gamelevel/Player.cpp

	# widgets
	app_src/objects/widgets/CancelButton.cpp
	app_src/objects/widgets/GameDialog.cpp
	app_src/objects/widgets/PauseOption.cpp
)