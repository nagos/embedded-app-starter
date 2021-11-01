cmake_minimum_required(VERSION 3.2)
include(common_modules/cmake_modules/common.cmake)
project(app)

add_executable(app-test
        app-main.cpp
        app.cpp
        web_app/web_app.cpp
)
target_link_libraries(app-test common_modules)

INSTALL(TARGETS app-test RUNTIME DESTINATION bin)
