project(Minesweeper)
cmake_minimum_required(VERSION 3.6)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} WIN32 App.cpp App.h Main.cpp Main.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})