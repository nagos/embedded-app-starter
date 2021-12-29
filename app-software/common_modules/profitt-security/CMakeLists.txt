find_package(Qt5Core)

add_library(
	profitt-security
	profitt-security.c
)

target_link_libraries(profitt-security PRIVATE Qt5::Core)
target_include_directories(profitt-security INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
