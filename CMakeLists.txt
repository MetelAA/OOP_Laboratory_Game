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
        GameManagment/GameSetup.cpp
        GameManagment/GameSetup.h
        GameManagment/GameMaster.cpp
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
        Model/PlayerModel.h Model/CompControlledCreatureModel.h
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
        GameManagment/Controllers/EnemySpawnerBuildingController.cpp
        GameManagment/Controllers/EnemySpawnerBuildingController.h
        GameManagment/Controllers/PlayerController.cpp
        GameManagment/Controllers/PlayerController.h
        GameManagment/EntityManagers/CreatureManagers/CreatureManager.cpp
        Exceptions/Notifications/SlowingCellNotification.h Exceptions/Notifications/NoEntityInCellNotification.h Entities/Creatures/Attacks/Spels/SpellType.h Entities/Creatures/Attacks/Spels/Spell.cpp Entities/Creatures/Attacks/Spels/Spell.h GameManagment/Controllers/CompControlledCreatureController.cpp GameManagment/Controllers/CompControlledCreatureController.h GameManagment/Controllers/AllyController.cpp GameManagment/Controllers/AllyController.h Factories/AllySpawner.cpp Factories/AllySpawner.h Entities/Creatures/Attacks/Spels/Hand/SpellHand.cpp Entities/Creatures/Attacks/Spels/Hand/SpellHand.h Entities/Creatures/Attacks/Spels/DirectDamageSpell.cpp Entities/Creatures/Attacks/Spels/DirectDamageSpell.h Entities/Creatures/Attacks/Spels/AreaDamageSpell.cpp Entities/Creatures/Attacks/Spels/AreaDamageSpell.h Entities/Creatures/Attacks/Spels/CreateTrapSpell.cpp Entities/Creatures/Attacks/Spels/CreateTrapSpell.h Entities/Creatures/Attacks/Spels/BuffSpellSpell.cpp Entities/Creatures/Attacks/Spels/BuffSpellSpell.h GameField/CellEvents/CellEvent.cpp GameField/CellEvents/CellEvent.h GameField/CellEvents/CellEventType.h GameField/CellEvents/SlowingCellEvent.cpp GameField/CellEvents/SlowingCellEvent.h GameField/CellEvents/TrapCellEvent.cpp GameField/CellEvents/TrapCellEvent.h Factories/SpellFactory.cpp Factories/SpellFactory.h Model/SpellsModels.h)
