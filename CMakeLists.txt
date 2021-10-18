cmake_minimum_required(VERSION 3.0)

project(json_object)
set(LIB_SOURCES src/json_primitive.cpp src/json_object.cpp src/json_array.cpp) 
set(LIB_HEADERS include/json.h iinclude/json_value.h nclude/json_primitive.h include/json_object.h include/json_array.h)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_library(json_object STATIC ${LIB_SOURCES})
target_include_directories(json_object PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main json_object)

# enable_testing()
# add_executable(wordcounter_test src/word_counter_test.cpp)
# target_link_libraries(wordcounter_test gtest_main)
# target_link_libraries(wordcounter_test wordcounter)

# include(GoogleTest)
# gtest_discover_tests(wordcounter_test)
