#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "service_practice/Rotation.h"

class turtleSim{
public:
    turtleSim();
    ~turtleSim();
    bool rotation(service_practice::Rotation::Request  &req,
        service_practice::Rotation::Response &res);

private:
    ros::Publisher twist_pub;
    ros::NodeHandle nh;
    ros::ServiceServer service;
};

turtleSim::turtleSim(){
    service = nh.advertiseService("turtlesim_rotation", &turtleSim::rotation, this);
    twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    
    geometry_msgs::Twist twist;
    twist.linear.x = 0.0;
    twist.linear.y = 0.0;
    twist.linear.z = 0.0;
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = 0.0;
    twist_pub.publish(twist);
}
    
turtleSim::~turtleSim(){
    
}

bool turtleSim::rotation(service_practice::Rotation::Request  &req,
        service_practice::Rotation::Response &res){

    geometry_msgs::Twist twist;
    int i;
    ros::Rate loop_rate(10);

    for(i = 0;i < req.rotation_cnt; i++){
        twist.angular.z = 1.0;
        twist_pub.publish(twist);
        loop_rate.sleep();
    }

    return true;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "turtlesim_rotation_server"); 
    
    turtleSim turtlesim;
    ROS_INFO("Ready.");
    ros::spin();    

    return 0;
}