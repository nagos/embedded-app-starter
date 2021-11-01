find_package(Qt5Core)

add_library(
	snmp_agent
	snmp_agent.cpp
)

target_link_libraries(snmp_agent PRIVATE Qt5::Core)
target_include_directories(snmp_agent INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
