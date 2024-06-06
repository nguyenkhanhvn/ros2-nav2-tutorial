#include "my_robot_behavior_tree/plugins/action/test_action.hpp"

namespace my_robot_behavior_tree
{

TestAction::TestAction(
  const std::string & xml_tag_name,
  const std::string & action_name,
  const BT::NodeConfiguration & conf)
: BtActionNode<CountUntil>(xml_tag_name, action_name, conf)
{
}

void TestAction::on_tick()
{
  getInput("target_number", goal_.target_number);
}


}  // namespace my_robot_behavior_tree

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  BT::NodeBuilder builder =
    [](const std::string & name, const BT::NodeConfiguration & config)
    {
      return std::make_unique<my_robot_behavior_tree::TestAction>(
        name, "test_behavior", config);
    };

  factory.registerBuilder<my_robot_behavior_tree::TestAction>(
    "TestBehavior", builder);
}
