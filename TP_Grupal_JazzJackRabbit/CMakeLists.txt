cmake_minimum_required(VERSION 3.10)
project(JJR2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall  -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/sources")
add_definitions(-DGENERAL_PATH="${PROJECT_SOURCE_DIR}")
add_definitions(-DDYAML_ARCHIVES="${PROJECT_SOURCE_DIR}/sources/yaml")

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
set(SDL2PP_WITH_MIXER YES)
add_subdirectory(deps/SDL2pp)
include_directories(${SDL2PP_INCLUDE_DIRS})

add_subdirectory(deps/yaml-cpp)
include_directories(${YAML_CPP_INCLUDE_DIR})


set(SOCKET_SOURCE_FILES   src/common/socket.cpp
                          src/common/liberror.cpp
                          src/common/resolver.cpp
                          src/common/resolvererror.cpp
)

set(CLIENT_SOURCE_FILES src/client/main.cpp
                        src/client/actions.cpp
                        src/client/client.cpp
                        src/client/client_protocol.cpp
                        src/client/graphics.cpp
                        src/client/scoring_table.cpp
                        src/client/choose/choose_characters.cpp
                        src/client/choose/choose_scenery.cpp
                        src/client/choose/choose.cpp
                        src/client/menu/join_menu.cpp
                        src/client/menu/menu_options_manager.cpp
                        src/client/menu/menu.cpp
                        src/client/menu/menu_level_editor.cpp
                        src/client/menu/maps_menu.cpp
                        src/client/menu/create_file_menu.cpp
                        src/client/menu/user_name.cpp
                        src/client/menu/cursor_manager.cpp
                        src/client/menu/input_events_manager.cpp
                        src/common/mapsParser/mapsParser.cpp
                        src/client/renderer_manager/renderer_manager.cpp
                        src/client/music_manager/music_manager.cpp
                        src/client/music_manager/sounds_map.cpp
                        src/client/level_editor/controller/level_edit.cpp
                        src/client/level_editor/controller/create_level.cpp
                        src/client/level_editor/controller/common_editor.cpp
                        src/client/level_editor/model/palette/palette.cpp
                        src/client/level_editor/model/palette/element_reader.cpp
                        src/client/level_editor/model/level_parser.cpp
                        src/client/level_editor/model/camera.cpp
                        src/client/level_editor/model/colission_checker.cpp
                        src/client/level_editor/model/events_manager.cpp
                        src/client/level_editor/view/graphics_level_editor.cpp
                        src/client/reciver_client.cpp
                        src/client/sender_client.cpp
                        src/common/clientaction.cpp
                        src/common/gamestate.cpp
                        ${SOCKET_SOURCE_FILES}
)

add_executable(Client ${CLIENT_SOURCE_FILES})
target_include_directories(Client PRIVATE src/client src/common)
target_link_libraries(Client PUBLIC SDL2pp)
target_link_libraries(Client PUBLIC yaml-cpp::yaml-cpp)


set(SERVER_SOURCE_FILES src/server/main.cpp
                        src/server/config.cpp
                        src/server/server.cpp
                        src/server/net/acceptor.cpp
                        src/server/net/clientiohandler.cpp
                        src/server/gamelogic/gameloop.cpp
                        src/server/gamelogic/entity.cpp
                        src/server/gamelogic/level.cpp
                        src/server/gamelogic/gamemap.cpp
                        src/server/gamelogic/playermap.cpp
                        src/server/gamelogic/gamemanager.cpp
                        src/server/gamelogic/entities/player.cpp
                        src/server/gamelogic/entities/gun.cpp
                        src/common/gamestate.cpp
                        src/common/clientaction.cpp
                        ${SOCKET_SOURCE_FILES}
)
add_executable(Server ${SERVER_SOURCE_FILES})
target_link_libraries(Server PUBLIC yaml-cpp::yaml-cpp SDL2pp)
target_include_directories(Server PRIVATE src/server src/common)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  serde_test
  tests/serde_test.cc
  src/common/gamestate.cpp
  src/common/clientaction.cpp
)
target_link_libraries(
  serde_test
  GTest::gtest_main
)

target_include_directories(serde_test PRIVATE src/common)

include(GoogleTest)
gtest_discover_tests(serde_test)
