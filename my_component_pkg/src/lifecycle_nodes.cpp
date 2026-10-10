#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class ManagedNode : public rclcpp_lifecycle::LifecycleNode {
public:
    explicit ManagedNode(const std::string & node_name)
    : rclcpp_lifecycle::LifecycleNode(node_name) {
        RCLCPP_INFO(get_logger(), "Створено екземпляр вузла (Стан: Unconfigured)");
    }

    CallbackReturn on_configure(const rclcpp_lifecycle::State &) override {
        RCLCPP_INFO(get_logger(), "Виконується перехід: configure -> Вузол переходить у стан [Inactive]");
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_activate(const rclcpp_lifecycle::State &) override {
        RCLCPP_INFO(get_logger(), "Виконується перехід: activate -> Вузол переходить у стан [Active]");
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_deactivate(const rclcpp_lifecycle::State &) override {
        RCLCPP_INFO(get_logger(), "Виконується перехід: deactivate -> Вузол повертається в [Inactive]");
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_cleanup(const rclcpp_lifecycle::State &) override {
        RCLCPP_INFO(get_logger(), "Виконується перехід: cleanup -> Очищення ресурсів, перехід в [Unconfigured]");
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_shutdown(const rclcpp_lifecycle::State &) override {
        RCLCPP_INFO(get_logger(), "Виконується перехід: shutdown -> Завершення роботи вузла");
        return CallbackReturn::SUCCESS;
    }
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);

    auto node1 = std::make_shared<ManagedNode>("managed_node_1");
    auto node2 = std::make_shared<ManagedNode>("managed_node_2");

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node1->get_node_base_interface());
    executor.add_node(node2->get_node_base_interface());

    executor.spin();

    rclcpp::shutdown();
    return 0;
}
