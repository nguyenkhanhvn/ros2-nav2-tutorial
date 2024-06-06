#include "nknav2_bt_navigator/bt_navigator_server.hpp"

namespace nknav2_bt_navigator
{

BtNavigatorServer::BtNavigatorServer(rclcpp::NodeOptions options)
: nav2_util::LifecycleNode("bt_navigator", "",
    options.automatically_declare_parameters_from_overrides(true)),
  n_loader_("nknav2_bt_navigator", "nknav2_bt_navigator::Navigator"),
  default_ids_{"NavigateToPose", "NavigateThroughPoses"},
  default_types_{"nknav2_bt_navigator/NavigateToPose", "nknav2_bt_navigator/NavigateThroughPoses"}
{
  RCLCPP_INFO(get_logger(), "Creating");
  
  const std::vector<std::string> plugin_libs = {
    "nav2_compute_path_to_pose_action_bt_node",
    "nav2_compute_path_through_poses_action_bt_node",
    "nav2_smooth_path_action_bt_node",
    "nav2_follow_path_action_bt_node",
    "nav2_spin_action_bt_node",
    "nav2_wait_action_bt_node",
    "nav2_assisted_teleop_action_bt_node",
    "nav2_back_up_action_bt_node",
    "nav2_drive_on_heading_bt_node",
    "nav2_clear_costmap_service_bt_node",
    "nav2_is_stuck_condition_bt_node",
    "nav2_goal_reached_condition_bt_node",
    "nav2_initial_pose_received_condition_bt_node",
    "nav2_goal_updated_condition_bt_node",
    "nav2_globally_updated_goal_condition_bt_node",
    "nav2_is_path_valid_condition_bt_node",
    "nav2_reinitialize_global_localization_service_bt_node",
    "nav2_rate_controller_bt_node",
    "nav2_distance_controller_bt_node",
    "nav2_speed_controller_bt_node",
    "nav2_truncate_path_action_bt_node",
    "nav2_truncate_path_local_action_bt_node",
    "nav2_goal_updater_node_bt_node",
    "nav2_recovery_node_bt_node",
    "nav2_pipeline_sequence_bt_node",
    "nav2_round_robin_node_bt_node",
    "nav2_transform_available_condition_bt_node",
    "nav2_time_expired_condition_bt_node",
    "nav2_path_expiring_timer_condition",
    "nav2_distance_traveled_condition_bt_node",
    "nav2_single_trigger_bt_node",
    "nav2_goal_updated_controller_bt_node",
    "nav2_is_battery_low_condition_bt_node",
    "nav2_navigate_through_poses_action_bt_node",
    "nav2_navigate_to_pose_action_bt_node",
    "nav2_remove_passed_goals_action_bt_node",
    "nav2_planner_selector_bt_node",
    "nav2_controller_selector_bt_node",
    "nav2_goal_checker_selector_bt_node",
    "nav2_controller_cancel_bt_node",
    "nav2_path_longer_on_approach_bt_node",
    "nav2_wait_cancel_bt_node",
    "nav2_spin_cancel_bt_node",
    "nav2_assisted_teleop_cancel_bt_node",
    "nav2_back_up_cancel_bt_node",
    "nav2_drive_on_heading_cancel_bt_node",
    "nav2_is_battery_charging_condition_bt_node"
  };

  declare_parameter_if_not_declared(
    this, "plugin_lib_names", rclcpp::ParameterValue(plugin_libs));
  declare_parameter_if_not_declared(
    this, "transform_tolerance", rclcpp::ParameterValue(0.1));
  declare_parameter_if_not_declared(
    this, "global_frame", rclcpp::ParameterValue(std::string("map")));
  declare_parameter_if_not_declared(
    this, "robot_base_frame", rclcpp::ParameterValue(std::string("base_link")));
  declare_parameter_if_not_declared(
    this, "odom_topic", rclcpp::ParameterValue(std::string("odom")));
  
  declare_parameter_if_not_declared(
    this, "navigator_plugins", rclcpp::ParameterValue(default_ids_));
  
  get_parameter("navigator_plugins", navigator_ids_);
  if (navigator_ids_ == default_ids_) {
    for (size_t i = 0; i < default_ids_.size(); ++i) {
      declare_parameter(default_ids_[i] + ".plugin", default_types_[i]);
    }
  }
}

BtNavigatorServer::~BtNavigatorServer()
{
  navigators_.clear();
}

nav2_util::CallbackReturn
BtNavigatorServer::on_configure(const rclcpp_lifecycle::State & /*state*/)
{
  
  tf_ = std::make_shared<tf2_ros::Buffer>(get_clock());
  auto timer_interface = std::make_shared<tf2_ros::CreateTimerROS>(
    get_node_base_interface(), get_node_timers_interface());
  tf_->setCreateTimerInterface(timer_interface);
  tf_->setUsingDedicatedThread(true);
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_, this, false);

  global_frame_ = get_parameter("global_frame").as_string();
  robot_frame_ = get_parameter("robot_base_frame").as_string();
  transform_tolerance_ = get_parameter("transform_tolerance").as_double();
  odom_topic_ = get_parameter("odom_topic").as_string();

  // Libraries to pull plugins (BT Nodes) from
  auto plugin_lib_names = get_parameter("plugin_lib_names").as_string_array();

  nav2_bt_navigator::FeedbackUtils feedback_utils;
  feedback_utils.tf = tf_;
  feedback_utils.global_frame = global_frame_;
  feedback_utils.robot_frame = robot_frame_;
  feedback_utils.transform_tolerance = transform_tolerance_;

  // Odometry smoother object for getting current speed
  odom_smoother_ = std::make_shared<nav2_util::OdomSmoother>(shared_from_this(), 0.3, odom_topic_);

  navigator_types_.resize(navigator_ids_.size());

  auto node = shared_from_this();

  for (size_t i = 0; i != navigator_ids_.size(); i++)
  {
    try
    {
      navigator_types_[i] = nav2_util::get_plugin_type_param(node, navigator_ids_[i]);
      nknav2_bt_navigator::Navigator::Ptr navigator = n_loader_.createUniqueInstance(navigator_types_[i]);
      RCLCPP_INFO(get_logger(), "Created Navigator plugin %s of type %s", navigator_ids_[i].c_str(), navigator_types_[i].c_str());
      if(!navigator->on_configure(shared_from_this(), plugin_lib_names, feedback_utils, &plugin_muxer_, odom_smoother_))
      {
        RCLCPP_FATAL(get_logger(), "Failed to config Navigator plugin %s of type %s", navigator_ids_[i].c_str(), navigator_types_[i].c_str());
        return nav2_util::CallbackReturn::FAILURE;
      }
      navigators_.insert({navigator_ids_[i], navigator});
    }
    catch (const pluginlib::PluginlibException & ex)
    {
      RCLCPP_FATAL(
        get_logger(), "Failed to create Navigator. Exception: %s",
        ex.what());
      return nav2_util::CallbackReturn::FAILURE;
    }
  }

  std::string planner_ids_concat;
  for (size_t i = 0; i != navigator_ids_.size(); i++) {
    planner_ids_concat += navigator_ids_[i] + std::string(" ");
  }

  RCLCPP_INFO(
    get_logger(),
    "BtNavigatorServer has %s available.", planner_ids_concat.c_str());

  return nav2_util::CallbackReturn::SUCCESS;
}

nav2_util::CallbackReturn
BtNavigatorServer::on_activate(const rclcpp_lifecycle::State & /*state*/)
{
  RCLCPP_INFO(get_logger(), "Activating");

  NavigatorMap::iterator it;
  int i = 0;
  for (it = navigators_.begin(); it != navigators_.end(); ++it) {
    if(!it->second->on_activate())
    {
      RCLCPP_FATAL(get_logger(), "Failed to active Navigator plugin %s of type %s", navigator_ids_[i].c_str(), navigator_types_[i].c_str());
      return nav2_util::CallbackReturn::FAILURE;
    }
    i++;
  }

  // create bond connection
  createBond();

  return nav2_util::CallbackReturn::SUCCESS;
}

nav2_util::CallbackReturn
BtNavigatorServer::on_deactivate(const rclcpp_lifecycle::State & /*state*/)
{
  RCLCPP_INFO(get_logger(), "Deactivating");

  NavigatorMap::iterator it;
  int i = 0;
  for (it = navigators_.begin(); it != navigators_.end(); ++it) {
    if(!it->second->on_deactivate())
    {
      RCLCPP_FATAL(get_logger(), "Failed to deactive Navigator plugin %s of type %s", navigator_ids_[i].c_str(), navigator_types_[i].c_str());
      return nav2_util::CallbackReturn::FAILURE;
    }
    i++;
  }

  // destroy bond connection
  destroyBond();

  return nav2_util::CallbackReturn::SUCCESS;
}

nav2_util::CallbackReturn
BtNavigatorServer::on_cleanup(const rclcpp_lifecycle::State & /*state*/)
{
  RCLCPP_INFO(get_logger(), "Cleaning up");

  // Reset the listener before the buffer
  tf_listener_.reset();
  tf_.reset();

  NavigatorMap::iterator it;
  int i = 0;
  for (it = navigators_.begin(); it != navigators_.end(); ++it) {
    if(!it->second->on_cleanup())
    {
      RCLCPP_FATAL(get_logger(), "Failed to cleanup Navigator plugin %s of type %s", navigator_ids_[i].c_str(), navigator_types_[i].c_str());
      return nav2_util::CallbackReturn::FAILURE;
    }
    it->second.reset();
    i++;
  }

  RCLCPP_INFO(get_logger(), "Completed Cleaning up");
  return nav2_util::CallbackReturn::SUCCESS;
}

nav2_util::CallbackReturn
BtNavigatorServer::on_shutdown(const rclcpp_lifecycle::State & /*state*/)
{
  RCLCPP_INFO(get_logger(), "Shutting down");
  return nav2_util::CallbackReturn::SUCCESS;
}

} // namespace nknav2_bt_navigator