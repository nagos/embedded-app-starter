find_package(Qt5Core)
find_package(Qt5Test)
find_package(Qt5Network)

include_directories(${Qt5Test_INCLUDE_DIRS})

add_library(
	snmp_agent
	snmp_agent.cpp
	snmp_parser.cpp
	snmp_process.cpp
)

target_link_libraries(snmp_agent PRIVATE Qt5::Core Qt5::Network)
target_include_directories(snmp_agent INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_snmp_parser
	test_snmp_parser.cpp
)

add_test(NAME test_snmp_parser COMMAND test_snmp_parser)
target_link_libraries(test_snmp_parser PRIVATE Qt5::Test snmp_agent)

add_executable(test_snmp_process
	test_snmp_process.cpp
	
)

add_test(NAME test_snmp_process COMMAND test_snmp_process)
target_link_libraries(test_snmp_process PRIVATE Qt5::Test snmp_agent)

