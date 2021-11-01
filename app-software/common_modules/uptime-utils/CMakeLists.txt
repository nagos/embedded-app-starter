find_package(Qt5Core)

add_library(
	uptime_utils
	uptime_utils.cpp
)

target_link_libraries(uptime_utils PRIVATE Qt5::Core)
target_include_directories(uptime_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
