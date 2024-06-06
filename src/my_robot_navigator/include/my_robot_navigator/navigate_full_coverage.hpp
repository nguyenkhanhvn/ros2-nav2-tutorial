#ifndef MY_ROBOT_NAVIGATOR__FULL_COVERAGE_HPP_
#define MY_ROBOT_NAVIGATOR__FULL_COVERAGE_HPP_

#include "nknav2_bt_navigator/navigator.hpp"
#include "nav2_bt_navigator/bt_navigator.hpp"
#include "my_robot_interfaces/action/full_coverage.hpp"

namespace my_robot_navigator
{

class NavigateFullCoverage : public nknav2_bt_navigator::Navigator, private nav2_bt_navigator::Navigator<my_robot_interfaces::action::FullCoverage>
{
public:
  using ActionT = my_robot_interfaces::action::FullCoverage;
  using Nav2Navigator = nav2_bt_navigator::Navigator<ActionT>;

  NavigateFullCoverage() {}

  virtual bool on_configure(
    rclcpp_lifecycle::LifecycleNode::WeakPtr parent_node,
    const std::vector<std::string> & plugin_lib_names,
    const nav2_bt_navigator::FeedbackUtils & feedback_utils,
    nav2_bt_navigator::NavigatorMuxer * plugin_muxer,
    std::shared_ptr<nav2_util::OdomSmoother> odom_smoother) override
    { return Nav2Navigator::on_configure(parent_node, plugin_lib_names, feedback_utils, plugin_muxer, odom_smoother); }
    
  virtual bool on_activate() override
  { return Nav2Navigator::on_activate(); }
    
  virtual bool on_deactivate() override
  { return Nav2Navigator::on_deactivate(); }
    
  virtual bool on_cleanup() override
  { return Nav2Navigator::on_cleanup(); }

  
  /**
   * @brief A configure state transition to configure navigator's state
   * @param node Weakptr to the lifecycle node
   * @param odom_smoother Object to get current smoothed robot's speed
   */
  bool configure(
    rclcpp_lifecycle::LifecycleNode::WeakPtr node,
    std::shared_ptr<nav2_util::OdomSmoother> odom_smoother) override;

  /**
   * @brief A cleanup state transition to remove memory allocated
   */
  bool cleanup() override;

  /**
   * @brief Get action name for this navigator
   * @return string Name of action server
   */
  std::string getName() override {return std::string("full_coverage");}

  /**
   * @brief Get navigator's default BT
   * @param node WeakPtr to the lifecycle node
   * @return string Filepath to default XML
   */
  std::string getDefaultBTFilepath(rclcpp_lifecycle::LifecycleNode::WeakPtr node) override;

  /**
   * @brief A subscription and callback to handle the topic start_full_coverage published
   * @param msg Message received via topic
   */
  void onStartNavigateFullCoverageReceived(const std_msgs::msg::Empty::SharedPtr msg);

protected:
/**
   * @brief A callback to be called when a new goal is received by the BT action server
   * Can be used to check if goal is valid and put values on
   * the blackboard which depend on the received goal
   * @param goal Action template's goal message
   * @return bool if goal was received successfully to be processed
   */
  bool goalReceived(ActionT::Goal::ConstSharedPtr goal) override;

  /**
   * @brief A callback that defines execution that happens on one iteration through the BT
   * Can be used to publish action feedback
   */
  void onLoop() override;

  /**
   * @brief A callback that is called when a preempt is requested
   */
  void onPreempt(ActionT::Goal::ConstSharedPtr goal) override;

  /**
   * @brief A callback that is called when a the action is completed, can fill in
   * action result message or indicate that this action is done.
   * @param result Action template result message to populate
   * @param final_bt_status Resulting status of the behavior tree execution that may be
   * referenced while populating the result.
   */
  void goalCompleted(
    typename ActionT::Result::SharedPtr result,
    const nav2_behavior_tree::BtStatus final_bt_status) override;



  
  rclcpp::Time start_time_;

  rclcpp_action::Client<ActionT>::SharedPtr self_client_;

  std::string path_blackboard_id_;
  
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr start_full_coverage_sub_;

};

} // namespace my_robot_navigator

#endif // MY_ROBOT_NAVIGATOR__FULL_COVERAGE_HPP_