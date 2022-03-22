#include "ros/ros.h"
#include "service_practice/Rotation.h"

#define ROTATION_CNT 10

class turtleSim{
public:
    turtleSim();
    ~turtleSim();

private:
    ros::NodeHandle nh;
    service_practice::Rotation::Request req;
    service_practice::Rotation::Response res;
    ros::ServiceClient client;
};

turtleSim::turtleSim(){
    client = nh.serviceClient<service_practice::Rotation>("turtlesim_rotation", this);

    req.rotation_cnt = ROTATION_CNT;
    if(client.call(req, res)){
        ROS_INFO("Success.");
    }else{
        ROS_INFO("Fail.");
    }
}

turtleSim::~turtleSim(){

}

int main(int argc, char **argv){

    ros::init(argc, argv, "turtlesim_rotation_client"); 
    
    turtleSim turtlesim;

    return 0;
}