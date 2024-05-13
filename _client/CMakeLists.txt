project(test_project)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)
find_package(Qt5 COMPONENTS Qml Quick REQUIRED)

set_source_files_properties(main.cpp PROPERTIES SKIP_AUTOMOC ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(test_project ${SRC})

target_link_libraries(test_project
    Qt5::Qml
    Qt5::Quick
    Qt6::Core 
    Qt6::Widgets
    Qt6::Network
)
