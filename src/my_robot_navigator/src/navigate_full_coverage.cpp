#include "my_robot_navigator/navigate_full_coverage.hpp"

namespace my_robot_navigator
{

bool
NavigateFullCoverage::configure(
  rclcpp_lifecycle::LifecycleNode::WeakPtr parent_node,
  std::shared_ptr<nav2_util::OdomSmoother> odom_smoother)
{
  start_time_ = rclcpp::Time(0);
  auto node = parent_node.lock();

  if (!node->has_parameter("path_blackboard_id")) {
    node->declare_parameter("path_blackboard_id", std::string("path"));
  }

  path_blackboard_id_ = node->get_parameter("path_blackboard_id").as_string();

  self_client_ = rclcpp_action::create_client<ActionT>(node, getName());
  
  start_full_coverage_sub_ = node->create_subscription<std_msgs::msg::Empty>(
    "start_navigate_full_coverage",
    rclcpp::SystemDefaultsQoS(),
    std::bind(&NavigateFullCoverage::onStartNavigateFullCoverageReceived, this, std::placeholders::_1));

  return true;
}

bool
NavigateFullCoverage::cleanup()
{
  self_client_.reset();
  return true;
}

std::string
NavigateFullCoverage::getDefaultBTFilepath(
  rclcpp_lifecycle::LifecycleNode::WeakPtr parent_node)
{
  std::string default_bt_xml_filename;
  auto node = parent_node.lock();

  if (!node->has_parameter("default_nav_full_coverage_bt_xml")) {
    std::string pkg_share_dir =
      ament_index_cpp::get_package_share_directory("my_robot_navigator");
    node->declare_parameter<std::string>(
      "default_nav_full_coverage_bt_xml",
      pkg_share_dir +
      "/behavior_trees/navigate_full_coverage.xml");
  }

  node->get_parameter("default_nav_full_coverage_bt_xml", default_bt_xml_filename);

  return default_bt_xml_filename;
}

void
NavigateFullCoverage::onStartNavigateFullCoverageReceived(const std_msgs::msg::Empty::SharedPtr msg)
{
  ActionT::Goal goal;
  self_client_->async_send_goal(goal);
}

bool
NavigateFullCoverage::goalReceived(ActionT::Goal::ConstSharedPtr goal)
{
  auto bt_xml_filename = goal->behavior_tree;

  if (!bt_action_server_->loadBehaviorTree(bt_xml_filename)) {
    RCLCPP_ERROR(
      logger_, "BT file not found: %s. Navigation canceled.",
      bt_xml_filename.c_str());
    return false;
  }

  return true;
}

void
NavigateFullCoverage::onLoop()
{
}

void
NavigateFullCoverage::onPreempt(ActionT::Goal::ConstSharedPtr goal)
{
  RCLCPP_INFO(logger_, "Received goal preemption request");

}

void
NavigateFullCoverage::goalCompleted(
  typename ActionT::Result::SharedPtr /*result*/,
  const nav2_behavior_tree::BtStatus /*final_bt_status*/)
{
}

} // namespace my_robot_navigator

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(my_robot_navigator::NavigateFullCoverage, nknav2_bt_navigator::Navigator)