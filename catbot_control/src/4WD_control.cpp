#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

class _4WD_controller
{
  public:
    _4WD_controller()
    {
      br_controller = WD.advertise<std_msgs::Float64>("/catbot/back_right_wheel_effort_controller/command",5);
      bl_controller = WD.advertise<std_msgs::Float64>("/catbot/back_left_wheel_effort_controller/command",5);
      fr_controller = WD.advertise<std_msgs::Float64>("/catbot/front_right_wheel_effort_controller/command",5);
      fl_controller = WD.advertise<std_msgs::Float64>("/catbot/front_left_wheel_effort_controller/command",5);

      cmd_subscriber= WD.subscribe("/catbot/cmd_vel", 5, &_4WD_controller::cmd_callback, this);
      ros::spin();
    }

    void publish_controls()
    {
      std_msgs::Float64 br_control_signal;  br_control_signal.data = br_motor;
      std_msgs::Float64 bl_control_signal;  bl_control_signal.data = fr_motor;
      std_msgs::Float64 fr_control_signal;  fr_control_signal.data = bl_motor;
      std_msgs::Float64 fl_control_signal;  fl_control_signal.data = fl_motor;

      br_controller.publish(br_control_signal);
      bl_controller.publish(bl_control_signal);
      fr_controller.publish(fr_control_signal);
      fl_controller.publish(fl_control_signal);
    }

    void calculate_controls()
    {
      br_motor = v;
      fr_motor = v;
      bl_motor = v;
      bl_motor = v;
      br_motor -= w;
      fr_motor -= w;
      bl_motor += w;
      fl_motor += w;
    }

    void cmd_callback(const geometry_msgs::Twist::ConstPtr& msg)
    {
      v = msg->linear.x;
      w = msg->angular.z;
      calculate_controls();
      publish_controls();
    }

  private:
    double v=0,w=0;
    double br_motor,bl_motor,fr_motor,fl_motor;
    ros::Publisher br_controller, bl_controller, fr_controller, fl_controller;
    ros::Subscriber cmd_subscriber;
    ros::NodeHandle WD;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "four_WD_control");
  _4WD_controller controller;
  return 0;
}
