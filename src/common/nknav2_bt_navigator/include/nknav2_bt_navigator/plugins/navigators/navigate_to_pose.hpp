#ifndef NKNAV2_BT_NAVIGATOR__NAVIGATORS__NAVIGATE_TO_POSE_HPP_
#define NKNAV2_BT_NAVIGATOR__NAVIGATORS__NAVIGATE_TO_POSE_HPP_


#include "nknav2_bt_navigator/navigator.hpp"
#include "nav2_bt_navigator/navigators/navigate_to_pose.hpp"

namespace nknav2_bt_navigator
{

class NavigateToPose : public nknav2_bt_navigator::Navigator, private nav2_bt_navigator::NavigateToPoseNavigator
{
public:
  NavigateToPose() {}

  virtual bool on_configure(
    rclcpp_lifecycle::LifecycleNode::WeakPtr parent_node,
    const std::vector<std::string> & plugin_lib_names,
    const nav2_bt_navigator::FeedbackUtils & feedback_utils,
    nav2_bt_navigator::NavigatorMuxer * plugin_muxer,
    std::shared_ptr<nav2_util::OdomSmoother> odom_smoother) override
    { return nav2_bt_navigator::NavigateToPoseNavigator::on_configure(parent_node, plugin_lib_names, feedback_utils, plugin_muxer, odom_smoother); }
    
  virtual bool on_activate() override
  { return nav2_bt_navigator::NavigateToPoseNavigator::on_activate(); }
    
  virtual bool on_deactivate() override
  { return nav2_bt_navigator::NavigateToPoseNavigator::on_deactivate(); }
    
  virtual bool on_cleanup() override
  { return nav2_bt_navigator::NavigateToPoseNavigator::on_cleanup(); }

};

} // namespace nknav2_bt_navigator

#endif // NKNAV2_BT_NAVIGATOR__NAVIGATORS__NAVIGATE_TO_POSE_HPP_