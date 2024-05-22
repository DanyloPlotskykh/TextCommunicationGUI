project(client)

set_source_files_properties(main.cpp PROPERTIES SKIP_AUTOMOC ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Network.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    Qt5::Qml
    Qt5::Quick
    Qt5::Core 
    Qt5::Widgets
    Qt5::Network
)
