#ifndef NKNAV2_BT_NAVIGATOR__NAVIGATOR_HPP_
#define NKNAV2_BT_NAVIGATOR__NAVIGATOR_HPP_

#include <memory>
#include <string>
#include <vector>

#include "nav2_bt_navigator/navigator.hpp"

namespace nknav2_bt_navigator
{

// This class should be containner of nav2_bt_navigator::Navigator<ActionT>
class Navigator
{
public:
    using Ptr = std::shared_ptr<Navigator>;
    Navigator() {}

    /**
     * @brief Virtual destructor
     */
    virtual ~Navigator() = default;
    
  /**
   * @brief Reference to nav2_bt_navigator::Navigator<ActionT>::on_configure
   */
  virtual bool on_configure(
    rclcpp_lifecycle::LifecycleNode::WeakPtr parent_node,
    const std::vector<std::string> & plugin_lib_names,
    const nav2_bt_navigator::FeedbackUtils & feedback_utils,
    nav2_bt_navigator::NavigatorMuxer * plugin_muxer,
    std::shared_ptr<nav2_util::OdomSmoother> odom_smoother) = 0;
    
  virtual bool on_activate() = 0;
    
  virtual bool on_deactivate() = 0;
    
  virtual bool on_cleanup() = 0;
};

} // namespace nknav2_bt_navigator

#endif // NKNAV2_BT_NAVIGATOR__NAVIGATOR_HPP_