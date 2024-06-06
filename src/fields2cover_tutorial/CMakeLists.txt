cmake_minimum_required(VERSION 3.8)
project(fields2cover_tutorial)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(Fields2Cover REQUIRED)

file(GLOB_RECURSE SRC_FILE "src/*.cpp")
add_executable(${PROJECT_NAME}
  ${SRC_FILE}
)

include_directories(include/${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  Fields2Cover
)

install(TARGETS
  ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}/
)


ament_package()
