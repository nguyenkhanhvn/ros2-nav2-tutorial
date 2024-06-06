cmake_minimum_required(VERSION 3.8)
project(my_robot_navigator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(dependencies
  pluginlib
  my_robot_interfaces
  nav2_bt_navigator
  nknav2_bt_navigator
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
foreach(Dependency IN ITEMS ${dependencies})
  find_package(${Dependency} REQUIRED)
endforeach()

include_directories(include)

file(GLOB_RECURSE SRC_FILE "src/*.cpp")
add_library(${PROJECT_NAME} ${SRC_FILE})
target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  ${PROJECT_NAME}
  ${dependencies}
)
pluginlib_export_plugin_description_file(nknav2_bt_navigator my_robot_navigator_plugins.xml)

install(FILES my_robot_navigator_plugins.xml
  DESTINATION share/${PROJECT_NAME}
)


install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY
  behavior_trees
  DESTINATION share/${PROJECT_NAME}
)

ament_export_include_directories(
  include
)
ament_export_libraries(${PROJECT_NAME})

ament_export_targets(
  export_${PROJECT_NAME}
)

ament_export_dependencies(${dependencies})

ament_package()
