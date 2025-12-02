cmake_minimum_required(VERSION 3.10)
project(sfml)

set(CMAKE_CXX_STANDARD 17)
set(SFML_MODULES network graphics window system)

foreach(i ${SFML_MODULES})
    list(APPEND SFML_LIBRARIES "sfml-${i}")
endforeach(i)

set(SOURCE_FILES game.cc)
add_executable(sfml ${SOURCE_FILES})

target_link_libraries(sfml ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}})
