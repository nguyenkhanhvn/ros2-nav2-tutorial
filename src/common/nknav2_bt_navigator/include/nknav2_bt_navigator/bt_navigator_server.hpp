#ifndef NKNAV2_BT_NAVIGATOR__BT_NAVIGATOR_SERVER_HPP_
#define NKNAV2_BT_NAVIGATOR__BT_NAVIGATOR_SERVER_HPP_

#include <chrono>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "pluginlib/class_loader.hpp"
#include "nknav2_bt_navigator/navigator.hpp"
#include "nav2_util/lifecycle_node.hpp"
#include "nav2_util/odometry_utils.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/create_timer_ros.h"

namespace nknav2_bt_navigator
{

// Reference from nav2_bt_navigator::BtNavigator, implement according to load plugin Navigator approach
/**
 * @class nav2_bt_navigator::BtNavigator
 * @brief An action server that uses behavior tree for navigating a robot to its
 * goal position.
 */
class BtNavigatorServer : public nav2_util::LifecycleNode
{
public:
  using NavigatorMap = std::unordered_map<std::string, nknav2_bt_navigator::Navigator::Ptr>;

  /**
   * @brief A constructor for nav2_bt_navigator::BtNavigator class
   * @param options Additional options to control creation of the node.
   */
  explicit BtNavigatorServer(rclcpp::NodeOptions options = rclcpp::NodeOptions());
  /**
   * @brief A destructor for nav2_bt_navigator::BtNavigator class
   */
  ~BtNavigatorServer();

protected:
  /**
   * @brief Configures member variables
   *
   * Initializes action server for "NavigationToPose"; subscription to
   * "goal_sub"; and builds behavior tree from xml file.
   * @param state Reference to LifeCycle node state
   * @return SUCCESS or FAILURE
   */
  nav2_util::CallbackReturn on_configure(const rclcpp_lifecycle::State & state) override;
  /**
   * @brief Activates action server
   * @param state Reference to LifeCycle node state
   * @return SUCCESS or FAILURE
   */
  nav2_util::CallbackReturn on_activate(const rclcpp_lifecycle::State & state) override;
  /**
   * @brief Deactivates action server
   * @param state Reference to LifeCycle node state
   * @return SUCCESS or FAILURE
   */
  nav2_util::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & state) override;
  /**
   * @brief Resets member variables
   * @param state Reference to LifeCycle node state
   * @return SUCCESS or FAILURE
   */
  nav2_util::CallbackReturn on_cleanup(const rclcpp_lifecycle::State & state) override;
  /**
   * @brief Called when in shutdown state
   * @param state Reference to LifeCycle node state
   * @return SUCCESS or FAILURE
   */
  nav2_util::CallbackReturn on_shutdown(const rclcpp_lifecycle::State & state) override;

  // To handle all the BT related execution
  
  // Controller Plugins
  pluginlib::ClassLoader<nknav2_bt_navigator::Navigator> n_loader_;
  NavigatorMap navigators_;
  std::vector<std::string> default_ids_;
  std::vector<std::string> default_types_;
  std::vector<std::string> navigator_ids_;
  std::vector<std::string> navigator_types_;
  std::string controller_ids_concat_, current_controller_;

  nav2_bt_navigator::NavigatorMuxer plugin_muxer_;

  // Odometry smoother object
  std::shared_ptr<nav2_util::OdomSmoother> odom_smoother_;

  // Metrics for feedback
  std::string robot_frame_;
  std::string global_frame_;
  double transform_tolerance_;
  std::string odom_topic_;

  // Spinning transform that can be used by the BT nodes
  std::shared_ptr<tf2_ros::Buffer> tf_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

};

} // namespace nknav2_bt_navigator

#endif // NKNAV2_BT_NAVIGATOR__BT_NAVIGATOR_SERVER_HPP_