add_subdirectory("data_storage")
add_subdirectory("uptime-utils")
add_subdirectory("web_socket_server")
add_subdirectory("watchdog")
add_subdirectory("spi-altera")
add_subdirectory("linux-input")
add_subdirectory("eventlog-api")
add_subdirectory("snmp_agent")
add_subdirectory("perp_server")
add_subdirectory("profitt-security")
add_subdirectory("exec_lock")

add_library(common_modules INTERFACE)
target_link_libraries(common_modules INTERFACE Qt5::Core 
    websocketserver 
    watchdog 
    data_storage 
    uptime_utils 
    spi_altera 
    linux_input 
    eventlog 
    snmp_agent 
    perp_server 
    profitt-security
    exec_lock
)
target_include_directories(common_modules INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
