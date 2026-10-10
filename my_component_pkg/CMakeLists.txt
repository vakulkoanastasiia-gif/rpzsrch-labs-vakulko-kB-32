cmake_minimum_required(VERSION 3.8)
project(my_component_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

# --- 1. Компонент (Завдання 1.2) ---
add_library(realtime_component SHARED
  src/my_component.cpp
)
target_include_directories(realtime_component PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(realtime_component
  rclcpp
  rclcpp_components
)
rclcpp_components_register_nodes(realtime_component "my_realtime_namespace::RealtimeComponent")

# --- 2. Керовані вузли (Завдання 1.3) ---
add_executable(lifecycle_nodes_app
  src/lifecycle_nodes.cpp
)
ament_target_dependencies(lifecycle_nodes_app
  rclcpp
  rclcpp_lifecycle
)

# --- Інсталяція цілей ---
install(TARGETS
  realtime_component
  lifecycle_nodes_app
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_package()
