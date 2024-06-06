cmake_minimum_required(VERSION 3.8)
project(nknav2_bt_navigator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(dependencies
  pluginlib
  nav2_bt_navigator
  nav2_util
  rclcpp_action
  tf2_ros
)

# find dependencies
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${dependencies})
  find_package(${Dependency} REQUIRED)
endforeach()

file(GLOB_RECURSE SRC_FILE "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILE})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  ${PROJECT_NAME}
  ${dependencies}
)


file(GLOB_RECURSE PLUGIN_FILE "plugins/*.cpp")
add_library(${PROJECT_NAME}_plugins SHARED ${PLUGIN_FILE})
target_compile_features(${PROJECT_NAME}_plugins PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(${PROJECT_NAME}_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  ${PROJECT_NAME}_plugins
  ${dependencies}
)
pluginlib_export_plugin_description_file(${PROJECT_NAME} nknav2_bt_navigator_plugins.xml)

install(FILES nknav2_bt_navigator_plugins.xml
  DESTINATION share/${PROJECT_NAME}
)


install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}_plugins
  EXPORT export_${PROJECT_NAME}_plugins
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(
  include
)

ament_export_libraries(
  ${PROJECT_NAME}_plugins
)

ament_export_targets(
  export_${PROJECT_NAME}_plugins
)

ament_export_dependencies(${dependencies})

ament_package()
