FROM osrf/ros:humble-desktop

RUN apt-get update && apt-get install -y \
    ros-humble-rclcpp-components \
    ros-humble-rclcpp-lifecycle \
    python3-colcon-common-extensions \
    && rm -rf /var/lib/apt/lists/*

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

WORKDIR /ros2_ws

ENTRYPOINT ["/entrypoint.sh"]
CMD ["bash"]
