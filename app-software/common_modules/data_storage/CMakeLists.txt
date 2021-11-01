find_package(Qt5Test)

include_directories(${Qt5Test_INCLUDE_DIRS})

add_library(
	data_storage
	data_storage.cpp
)

add_executable(test_data_storage 
	test_data_storage.cpp
)

add_test(NAME test_data_storage COMMAND test_data_storage)
target_link_libraries(test_data_storage PRIVATE Qt5::Test data_storage)
target_include_directories(data_storage INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
