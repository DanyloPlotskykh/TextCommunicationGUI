project(server)

# find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)
# set(Qt_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt6)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)
find_package(Qt5 COMPONENTS Qml Quick REQUIRED)

message("QT_MAJOR_VERSION: ${QT_MAJOR_VERSION}")

set_source_files_properties(main.cpp PROPERTIES SKIP_AUTOMOC ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp)

add_executable(server ${SRC})

target_link_libraries(server
    Qt5::Core 
    Qt5::Widgets
    Qt5::Network
    Qt5::Qml
    Qt5::Quick)

