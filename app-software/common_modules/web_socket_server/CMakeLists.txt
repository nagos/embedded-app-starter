find_package(Qt5WebSockets)
include_directories(${Qt5WebSockets_INCLUDE_DIRS})

add_library(
	websocketserver
	websocketserver.cpp
)

target_link_libraries(websocketserver PRIVATE Qt5::WebSockets ${TUFAO_LIBRARIES})
target_include_directories(websocketserver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${TUFAO_INCLUDE_DIR})
