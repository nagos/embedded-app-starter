find_package(Qt5Core)

add_library(
	exec_lock
	exec-lock.cpp
)

target_link_libraries(exec_lock PRIVATE Qt5::Core)
