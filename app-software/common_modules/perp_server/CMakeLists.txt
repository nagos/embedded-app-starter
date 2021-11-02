find_package(Qt5Core)

add_library(
	perp_server
	vgpi_api.cpp
	vgpi_server.cpp
	perp_server.cpp
)

target_link_libraries(perp_server PRIVATE Qt5::Core)
target_include_directories(perp_server INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
