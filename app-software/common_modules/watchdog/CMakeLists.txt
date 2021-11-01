find_package(Qt5Core)

add_library(
	watchdog
	watchdog.cpp
)

target_include_directories(watchdog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(watchdog PRIVATE Qt5::Core)
