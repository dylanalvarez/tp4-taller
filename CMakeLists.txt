cmake_minimum_required(VERSION 3.5.1)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 11)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
set(CMAKE_CXX_FLAGS  "-std=c++11 -Werror -Wno-error=unused-command-line-argument  -Wno-c++14-extensions -Wall -pthread")
else()
set(CMAKE_CXX_FLAGS  "-std=c++11 -Werror -Wall -pthread")
endif()
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
SET(GCC_COVERAGE_LINK_FLAGS "-Wl -lcppunit -I./libraries/yaml-cpp/include -lyaml-cpp -lSDL2 -lSDL2_mixer")
else()
SET(GCC_COVERAGE_LINK_FLAGS "-Wl,--no-as-needed -lcppunit -I./libraries/yaml-cpp/include -L./libraries/yaml-cpp -lyaml-cpp -lSDL2 -lSDL2_mixer")
endif()
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

set(SOURCE_FILES src/server/main.cpp src/common/CommunicationUtils.h src/common/GameServerSocket.h src/common/GameServerReceiver.h src/common/BlockingQueue.h src/common/BlockingQueue.cpp src/common/Exception.h src/common/Exception.cpp src/common/AcceptFailedException.h src/common/ServerSocket.h src/common/ServerSocket.cpp src/common/Socket.h src/common/Socket.cpp src/common/Thread.h src/common/Thread.cpp src/model/Vector.cpp src/model/Vector.h src/model/Towers/Tower.cpp src/model/Towers/Tower.h src/model/Towers/FireTower.cpp src/model/Towers/FireTower.h src/model/Enemy.cpp src/model/Enemy.h src/model/Path.cpp src/model/Path.h src/model/Scenario.cpp src/model/Scenario.h src/model/Range.cpp src/model/Range.h src/model/Exceptions/EnemyError.cpp src/model/Exceptions/EnemyError.h src/model/TowerDefenseGame.cpp src/model/TowerDefenseGame.h src/model/Exceptions/TowerError.cpp src/model/Exceptions/TowerError.h src/model/Player.cpp src/model/Player.h src/model/Exceptions/MatchError.cpp src/model/Exceptions/MatchError.h src/model/Factory/TowerFactory.h src/model/Factory/FireTowerFactory.cpp src/model/Factory/FireTowerFactory.h src/model/Towers/WaterTower.cpp src/model/Towers/WaterTower.h src/model/Factory/WaterTowerFactory.cpp src/model/Factory/WaterTowerFactory.h src/model/Towers/EarthTower.cpp src/model/Towers/EarthTower.h src/model/Factory/EarthTowerFactory.cpp src/model/Factory/EarthTowerFactory.h src/model/Towers/AirTower.cpp src/model/Towers/AirTower.h src/model/Factory/AirTowerFactory.cpp src/model/Factory/AirTowerFactory.h src/model/Upgrades/RangeLevelup.cpp src/model/Upgrades/RangeLevelup.h src/model/Upgrades/LevelupType.cpp src/model/Upgrades/LevelupType.h src/model/Upgrades/DamageLevelup.cpp src/model/Upgrades/DamageLevelup.h src/model/Upgrades/ReachLevelup.cpp src/model/Upgrades/ReachLevelup.h src/model/Upgrades/SlowdownLevelup.cpp src/model/Upgrades/SlowdownLevelup.h src/model/Spells/Spell.h src/model/Spells/Spell.h src/model/Spells/Terraforming.cpp src/model/Spells/Terraforming.h src/model/Spells/Fissure.cpp src/model/Spells/Fissure.h src/model/Spells/Meteorite.cpp src/model/Spells/Meteorite.h src/model/Spells/FireWall.cpp src/model/Spells/FireWall.h src/model/Spells/Freezing.cpp src/model/Spells/Freezing.h src/model/Spells/Blizzard.cpp src/model/Spells/Blizzard.h src/model/Spells/Tornato.cpp src/model/Spells/Tornato.h src/model/Spells/Ray.cpp src/model/Spells/Ray.h src/model/Spells/Spell.cpp src/server/Server.cpp src/server/Server.h src/server/Match.cpp src/server/Match.h src/server/Client.cpp src/server/Client.h src/common/GameServerSocket.cpp src/common/GameServerReceiver.cpp src/server/Actions/ThrowPositionalSpellAction.cpp src/server/Actions/ThrowPositionalSpellAction.h src/server/Actions/Action.h src/server/Actions/ThrowTargetSpellAction.cpp src/server/Actions/ThrowTargetSpellAction.h src/server/Actions/BuildTowerAction.cpp src/server/Actions/BuildTowerAction.h src/server/Actions/AddEnemyAction.cpp src/server/Actions/AddEnemyAction.h src/server/Actions/SendMessageAction.cpp src/server/Actions/SendMessageAction.h src/server/QueueProtected.cpp src/server/QueueProtected.h src/server/HordeCreator.cpp src/server/HordeCreator.h src/server/Horde.cpp src/server/Horde.h src/server/ClientSender.cpp src/server/ClientSender.h src/server/Context.cpp src/server/Context.h src/server/Actions/SendGameStateAction.cpp src/server/Actions/SendGameStateAction.h src/server/Actions/DistributeMessageAction.cpp src/server/Actions/DistributeMessageAction.h src/common/CommunicationUtils.cpp src/server/Actions/DisconnectAction.h src/server/Actions/UpgradeAction.cpp src/server/Actions/UpgradeAction.h src/server/Actions/PingAction.cpp src/server/Actions/PingAction.h src/server/Actions/DistributePingAction.cpp src/server/Actions/DistributePingAction.h src/common/Sound.cpp src/common/Sound.h)

file(GLOB CLIENT_SOURCE_FILES
        "src/client/*.h"
        "src/client/*.cpp"
        )

add_custom_target(Makefile)
add_executable(Client src/client/Aplicacion.h src/client/Aplicacion.cpp src/client/main.cpp src/editor/Map.h src/editor/Map.cpp src/common/Exception.h src/common/Exception.cpp  src/common/CommunicationUtils.h src/common/CommunicationUtils.cpp src/common/GameClientReceiver.cpp src/common/GameClientReceiver.h src/common/GameClientSocket.h src/common/GameClientSocket.cpp src/common/Socket.h src/common/Socket.cpp src/common/Thread.h src/common/Thread.cpp ${CLIENT_SOURCE_FILES} src/client/PantallaResultado.cpp src/client/PantallaResultado.h src/common/Sound.cpp src/common/Sound.h src/client/GestionadorDeSonidos.cpp src/client/GestionadorDeSonidos.h)
add_executable(Server ${SOURCE_FILES})
add_executable(Test src/model/test_main.cpp src/common/Exception.h src/common/Exception.cpp  src/common/CommunicationUtils.h src/common/CommunicationUtils.cpp test/VectorTest.cpp test/VectorTest.h src/model/Vector.cpp src/model/Vector.h src/model/Towers/Tower.cpp src/model/Towers/Tower.h src/model/Towers/FireTower.cpp src/model/Towers/FireTower.h test/EnemyTest.cpp test/EnemyTest.h src/model/Enemy.cpp src/model/Enemy.h src/model/Path.cpp src/model/Path.h src/model/Scenario.cpp src/model/Scenario.h test/ScenarioTest.cpp test/ScenarioTest.h src/model/Range.cpp src/model/Range.h test/RangeTest.cpp test/RangeTest.h src/model/Exceptions/EnemyError.cpp src/model/Exceptions/EnemyError.h test/TowerDefenseGameTest.cpp test/TowerDefenseGameTest.h src/model/TowerDefenseGame.cpp src/model/TowerDefenseGame.h src/model/Exceptions/TowerError.cpp src/model/Exceptions/TowerError.h src/model/Player.cpp src/model/Player.h src/model/Exceptions/MatchError.cpp src/model/Exceptions/MatchError.h src/model/Towers/EarthTower.cpp src/model/Towers/EarthTower.h src/model/Factory/TowerFactory.h src/model/Factory/FireTowerFactory.cpp src/model/Factory/FireTowerFactory.h src/model/Towers/AirTower.cpp src/model/Towers/AirTower.h src/model/Towers/WaterTower.cpp src/model/Towers/WaterTower.h src/model/Factory/WaterTowerFactory.cpp src/model/Factory/WaterTowerFactory.h src/model/Factory/EarthTowerFactory.cpp src/model/Factory/EarthTowerFactory.h src/model/Factory/AirTowerFactory.cpp src/model/Factory/AirTowerFactory.h src/model/Upgrades/RangeLevelup.cpp src/model/Upgrades/RangeLevelup.h src/model/Upgrades/LevelupType.cpp src/model/Upgrades/LevelupType.h src/model/Upgrades/SlowdownLevelup.cpp src/model/Upgrades/SlowdownLevelup.h src/model/Upgrades/DamageLevelup.cpp src/model/Upgrades/DamageLevelup.h src/model/Upgrades/ReachLevelup.cpp src/model/Upgrades/ReachLevelup.h src/model/Spells/Spell.h src/model/Spells/Spell.h src/model/Spells/Terraforming.cpp src/model/Spells/Terraforming.h src/model/Spells/Fissure.cpp src/model/Spells/Fissure.h src/model/Spells/Meteorite.cpp src/model/Spells/Meteorite.h src/model/Spells/FireWall.cpp src/model/Spells/FireWall.h src/model/Spells/Freezing.cpp src/model/Spells/Freezing.h src/model/Spells/Blizzard.cpp src/model/Spells/Blizzard.h src/model/Spells/Tornato.cpp src/model/Spells/Tornato.h src/model/Spells/Ray.cpp src/model/Spells/Ray.h src/model/Spells/Spell.cpp)
add_executable(Editor src/editor/AddHordeGrid.cpp src/editor/AddHordeGrid.h src/editor/AmbianceGrid.cpp src/editor/AmbianceGrid.h src/editor/Builder.h src/editor/ChooseSizeGrid.cpp src/editor/ChooseSizeGrid.h src/editor/main.cpp src/editor/Map.h src/editor/Map.cpp src/editor/MapButton.cpp src/editor/MapButton.h src/editor/MapGrid.cpp src/editor/MapGrid.h src/editor/NameEntry.cpp src/editor/NameEntry.h src/editor/SaveButton.cpp src/editor/SaveButton.h src/editor/FileChooser.cpp src/editor/FileChooser.h src/editor/MainWindow.cpp src/editor/MainWindow.h src/editor/InvalidSizeException.h)
add_executable(SoundTest src/sound_test/main.cpp src/common/Sound.h src/common/Sound.cpp src/common/Exception.h src/common/Exception.cpp src/common/Thread.cpp src/common/Thread.h)
target_link_libraries(Server ${GTKMM_LIBRARIES})
target_link_libraries(Editor ${GTKMM_LIBRARIES})
target_link_libraries(Client ${GTKMM_LIBRARIES})

install (TARGETS Server Editor Client DESTINATION bin)
install (DIRECTORY cmake-build-debug/Sprites DESTINATION resources)
install (DIRECTORY cmake-build-debug/assets DESTINATION resources)
install(DIRECTORY cmake-build-debug/maps DESTINATION resources)

SET(CPACK_PACKAGE_FILE_NAME "TowerDefense")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Tower Defense")
SET(CPACK_PACKAGE_NAME "Tower Defense-1.0")
SET(CPACK_PACKAGE_VERSION "1.0")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "Tower Defense-1.0")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtkmm-3.0, libyaml-cpp, libsdl2, libsdl2-mixer libcppunit")

include(CPack)
