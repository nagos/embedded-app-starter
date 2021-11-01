find_package(Qt5Core)

add_library(
	eventlog
	eventlog.cpp
)

target_link_libraries(eventlog PRIVATE Qt5::Core)
target_include_directories(eventlog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
