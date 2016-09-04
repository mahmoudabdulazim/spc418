#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <ttyent.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

char getKey(fd_set*,termios*);


int main(int argc, char **argv)
{
    // Opening the terminal stdin and attaching it to a file descriptor
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO,&rfds);

    // Getting current terminal settings for resetting
    termios term_settings;
    tcgetattr(rfds,&term_settings);

    //Initializing ROS
    ros::init(argc, argv, "catbot_teleop");
    ros::Publisher teleop_pub = ros::advertise<geometry_msgs::Twist>("/cmd_vel",1);


    return 0;
}

char getKey(fd_set* rfds,termios* settings)
{
    char key;
    raw();
    struct timeval tv;
    tv.tv_sec  = 0.01;
    tv.tv_usec = 0;
    int rlist = select(rfds[0]+1,rfds,NULL,NULL,&tv);
    if (rlist > 0)
    {
        read(rfds,&key,1);
    }
    else
    {
        key = '';
    }
    tcsetattr(rfds,TCSADRAIN,settings);
    return key;
}
