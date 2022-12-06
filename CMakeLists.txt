cmake_minimum_required(VERSION 3.0.0)
project(TimerTest VERSION 0.1.0)

include(CTest)
enable_testing()

set(BOOST_COMPONENTS  chrono filesystem iostreams
        program_options regex system thread unit_test_framework)
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

add_executable(TimerTest sample.cpp)

target_link_libraries(TimerTest  ${Boost_LIBRARIES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
