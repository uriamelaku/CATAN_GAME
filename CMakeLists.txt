cmake_minimum_required(VERSION 3.10)

project(CatanGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(CatanGame Main.cpp Board.cpp HexTile.cpp Corner.cpp Edge.cpp Player.cpp DevelopmentCard.cpp DevelopmentCardDeck.cpp ResourceType.cpp)
add_executable(test_catan test_catan.cpp Board.cpp HexTile.cpp Corner.cpp Edge.cpp Player.cpp DevelopmentCard.cpp DevelopmentCardDeck.cpp ResourceType.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(test_catan ${GTEST_LIBRARIES} pthread)
