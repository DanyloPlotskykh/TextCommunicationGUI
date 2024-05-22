project(server)

set_source_files_properties(main.cpp PROPERTIES SKIP_AUTOMOC ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp)

add_executable(server ${SRC})

target_link_libraries(server
    Qt5::Core 
    Qt5::Widgets
    Qt5::Network
    Qt5::Qml
    Qt5::Quick)

