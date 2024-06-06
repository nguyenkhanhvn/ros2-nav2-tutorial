cmake_minimum_required(VERSION 3.8)
project(my_robot_behavior_tree)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(dependencies
  pluginlib
  rclcpp
  rclcpp_action
  rclcpp_lifecycle
  nav2_msgs
  nav_msgs
  behaviortree_cpp_v3
  my_robot_interfaces
  nav2_behavior_tree
)

# find dependencies
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${dependencies})
  find_package(${Dependency} REQUIRED)
endforeach()


add_library(nav2_test_action_bt_node SHARED plugins/action/test_action.cpp)
list(APPEND plugin_libs nav2_test_action_bt_node)


include_directories(
  include
)

foreach(bt_plugin ${plugin_libs})
  ament_target_dependencies(${bt_plugin} ${dependencies})
  target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
  pluginlib_export_plugin_description_file(${bt_plugin} my_robot_behavior_tree_plugin.xml)
endforeach()


install(TARGETS ${plugin_libs}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include/
)

install(FILES nav2_tree_nodes.xml DESTINATION share/${PROJECT_NAME})

ament_export_include_directories(
  include
)

ament_export_libraries(
  ${plugin_libs}
)
ament_export_dependencies(${dependencies})

ament_package()
