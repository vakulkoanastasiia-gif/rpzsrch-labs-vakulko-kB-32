#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace my_realtime_namespace {

class RealtimeComponent : public rclcpp::Node {
public:
    explicit RealtimeComponent(const rclcpp::NodeOptions & options)
    : Node("realtime_component_node", options) {
        RCLCPP_INFO(this->get_logger(), "Вузол-компонент успішно ініціалізовано в спільному просторі пам'яті!");
    }
};

}  // namespace my_realtime_namespace

RCLCPP_COMPONENTS_REGISTER_NODE(my_realtime_namespace::RealtimeComponent)
