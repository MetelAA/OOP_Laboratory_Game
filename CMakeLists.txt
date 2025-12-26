cmake_minimum_required(VERSION 3.24)
project(labaOOP2)

set(CMAKE_CXX_STANDARD 17)

add_executable(labaOOP2 main.cpp
        Entities/Creatures/Creature.cpp
        Entities/Creatures/Creature.h
        Entities/Creatures/Player.cpp
        Entities/Creatures/Player.h
        Entities/Creatures/CompControlledCreature.cpp
        Entities/Creatures/CompControlledCreature.h
        GameField/Field.cpp
        GameField/Field.h
        GameField/Cell.cpp
        GameField/Cell.h
        GameSetup/GameSetup.cpp
        GameSetup/GameSetup.h
        GameManagment/GameMaster.tpp
        GameManagment/GameMaster.h
        Entities/Entity.cpp
        Entities/Entity.h
        Entities/Buildings/Building.cpp
        Entities/Buildings/Building.h
        Entities/Buildings/EnemySpawnerBuilding.cpp
        Entities/Buildings/EnemySpawnerBuilding.h
        Exceptions/UniversalStringException.h
        Exceptions/CoordinateException.h
        Entities/Creatures/Attacks/Attack.cpp
        Entities/Creatures/Attacks/Attack.h
        GameManagment/EntityManagers/CreatureManagers/PlayerManager.cpp
        GameManagment/EntityManagers/CreatureManagers/PlayerManager.h
        GameManagment/EntityManagers/CreatureManagers/CreatureManager.h
        GameManagment/EntityManagers/CreatureManagers/CompControlledCreatureManager.cpp
        GameManagment/EntityManagers/CreatureManagers/CompControlledCreatureManager.h
        GameField/CellType.h Exceptions/Notifications/CellImpassableNotification.h
        Entities/EntityType.h
        Entities/Creatures/Attacks/AttackType.h
        Entities/Creatures/Attacks/LongRangeAttack.cpp
        Entities/Creatures/Attacks/LongRangeAttack.h
        Entities/Creatures/Attacks/CloseRangeAttack.cpp
        Entities/Creatures/Attacks/CloseRangeAttack.h
        Model/CompControlledCreatureModel.h
        Factories/EnemySpawner.cpp
        Factories/EnemySpawner.h
        Exceptions/SpawnEntityException.h
        GameManagment/EntityManagers/BuildingManagers/EnemySpawnerBuildingManager.cpp
        GameManagment/EntityManagers/BuildingManagers/EnemySpawnerBuildingManager.h
        Factories/EnemySpawnerBuildingSpawner.cpp
        Factories/EnemySpawnerBuildingSpawner.h
        GameManagment/EntityManagers/EntityManager.h
        Constants/Constants.h
        GameManagment/Controllers/EnemyController.cpp
        GameManagment/Controllers/EnemyController.h
        Exceptions/UnexpectedBehaviorException.h
        GameManagment/Controllers/Building/EnemySpawnerBuildingController.cpp
        GameManagment/Controllers/Building/EnemySpawnerBuildingController.h
        GameManagment/Controllers/PlayerController.cpp
        GameManagment/Controllers/PlayerController.h
        GameManagment/EntityManagers/CreatureManagers/CreatureManager.cpp
        Exceptions/Notifications/SlowingCellNotification.h Exceptions/Notifications/NoEntityInCellNotification.h Entities/Creatures/Attacks/Spels/SpellType.h Entities/Creatures/Attacks/Spels/Spell.cpp Entities/Creatures/Attacks/Spels/Spell.h GameManagment/Controllers/CompControlledCreatureController.cpp GameManagment/Controllers/CompControlledCreatureController.h GameManagment/Controllers/AllyController.cpp GameManagment/Controllers/AllyController.h Factories/AllySpawner.cpp Factories/AllySpawner.h Entities/Creatures/Attacks/Spels/Hand/SpellHand.cpp Entities/Creatures/Attacks/Spels/Hand/SpellHand.h Entities/Creatures/Attacks/Spels/DirectDamageSpell.cpp Entities/Creatures/Attacks/Spels/DirectDamageSpell.h Entities/Creatures/Attacks/Spels/AreaDamageSpell.cpp Entities/Creatures/Attacks/Spels/AreaDamageSpell.h Entities/Creatures/Attacks/Spels/CreateTrapSpell.cpp Entities/Creatures/Attacks/Spels/CreateTrapSpell.h Entities/Creatures/Attacks/Spels/BuffSpellSpell.cpp Entities/Creatures/Attacks/Spels/BuffSpellSpell.h GameField/CellEvents/CellEvent.cpp GameField/CellEvents/CellEvent.h GameField/CellEvents/CellEventType.h GameField/CellEvents/SlowingCellEvent.cpp GameField/CellEvents/SlowingCellEvent.h GameField/CellEvents/TrapCellEvent.cpp GameField/CellEvents/TrapCellEvent.h Factories/SpellFactory.cpp Factories/SpellFactory.h Model/SpellsModels.h Entities/Creatures/Attacks/Spels/SpellOnCoords.h Exceptions/Notifications/CantCastSpellOnCellNotification.h Entities/Creatures/Attacks/Spels/SummoningSpell.cpp Entities/Creatures/Attacks/Spels/SummoningSpell.h Entities/Buildings/EnemyDefenceTower.cpp Entities/Buildings/EnemyDefenceTower.h GameManagment/Controllers/Building/EnemyDefenceTowerController.cpp GameManagment/Controllers/Building/EnemyDefenceTowerController.h GameManagment/EntityManagers/BuildingManagers/EnemyDefenceTowerManager.cpp GameManagment/EntityManagers/BuildingManagers/EnemyDefenceTowerManager.h Factories/EnemyDefenceTowerSpawner.cpp Factories/EnemyDefenceTowerSpawner.h Model/EnemyDefenceTowerModel.h Model/EnemySpawnerBuildingModel.h GameSetup/Utils/JsonParser.cpp GameSetup/Utils/JsonParser.h GameSetup/Utils/ReadWrightJson.cpp GameSetup/Utils/ReadWrightJson.h GameRender/ConsoleRenderer.cpp GameRender/ConsoleRenderer.h GameManagment/Controllers/ExternalComandController/GamerConsoleInputSpotter.cpp GameManagment/Controllers/ExternalComandController/GamerConsoleInputSpotter.h GameManagment/Controllers/ExternalComandController/Actions/ActionType.h Entities/Creatures/PlayerView.cpp Entities/Creatures/PlayerView.h GameManagment/Controllers/ExternalComandController/Actions/PlayerAction.h GameManagment/Controllers/ExternalComandController/Actions/PlayerActionWithCoords.h GameManagment/Controllers/ExternalComandController/Actions/PlayerActionUseSpell.h GameManagment/Controllers/ExternalComandController/Actions/PlayerUpgradeAction.h GameManagment/Controllers/ExternalComandController/Actions/UpgradesType.h Exceptions/Notifications/CantAttackOnCoordsNotification.h Logger/Logger.cpp Logger/Logger.h Model/InputKeysModel.cpp Model/InputKeysModel.h GameManagment/Controllers/ExternalComandController/InputSpotter.h GameRender/GameVisualizer.h GameManagment/GameMasterBase.h)
