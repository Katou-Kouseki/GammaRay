cmake_minimum_required(VERSION 3.26)

find_package(GTest CONFIG REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Core Core5Compat WebSockets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Core Core5Compat WebSockets Network)

#add_executable(test_db
#        test_db.cpp
#        ../db/db_game.cpp
#        ../db/db_game_manager.cpp
#        ../gr_context.cpp
#        ../network/ip_util.cpp
#)
#target_link_libraries(test_db PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main sqlite_orm tc_common_new tc_steam_manager_new tc_encoder_new)
#target_link_libraries(test_db PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Core5Compat Qt6::WebSockets Qt6::Network)
#
#add_executable(test_process
#        test_process.cpp
#)
#target_link_libraries(test_process PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main tc_common_new tc_steam_manager_new tc_encoder_new)

add_executable(test_resolutions test_resolutions.cpp)

add_executable(test_http_client test_http_client.cpp)
target_link_libraries(test_http_client tc_common_new)
