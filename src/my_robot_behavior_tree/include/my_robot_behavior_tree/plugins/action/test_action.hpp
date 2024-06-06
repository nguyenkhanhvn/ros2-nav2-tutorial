#pragma once

#include "my_robot_interfaces/action/count_until.hpp"
#include "nav2_behavior_tree/bt_action_node.hpp"

namespace my_robot_behavior_tree
{
    
using CountUntil = my_robot_interfaces::action::CountUntil;

class TestAction : public nav2_behavior_tree::BtActionNode<CountUntil>
{
public:
  /**
   * @brief A constructor for nav2_behavior_tree::FollowPathAction
   * @param xml_tag_name Name for the XML tag for this node
   * @param action_name Action name this node creates a client for
   * @param conf BT node configuration
   */
  TestAction(
    const std::string & xml_tag_name,
    const std::string & action_name,
    const BT::NodeConfiguration & conf);

  /**
   * @brief Function to perform some user-defined operation on tick
   */
  void on_tick() override;

  /**
   * @brief Creates list of BT ports
   * @return BT::PortsList Containing basic ports along with node-specific ports
   */
  static BT::PortsList providedPorts()
  {
    return providedBasicPorts(
      {
        BT::InputPort<int>("target_number", "Number id for action"),
      });
  }
};

}  // namespace my_robot_behavior_tree