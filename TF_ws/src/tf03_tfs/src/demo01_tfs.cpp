#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"
/*
    step1: calculate the relationship between son1 and son2
    step2: calculate the coordinate in son2 of a point in son1 
*/
int main(int argc, char* argv[])

{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "tfs_sub");
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener sub(buffer);

    // create a coordinate
    geometry_msgs::PointStamped psAtSon1;

    psAtSon1.header.stamp = ros::Time::now();
    psAtSon1.header.frame_id = "son1";
    psAtSon1.point.x = 1.0;
    psAtSon1.point.y = 2.0;
    psAtSon1.point.z = 3.0;


    ros::Rate rate(10);
    while(ros::ok())
    {   
        try
        {
            geometry_msgs::TransformStamped son1toson2 = buffer.lookupTransform("son2", "son1", ros::Time(0));
            ROS_INFO("son 1 refers to son2: father %s, son %s, size(%.2f, %.2f, %.2f)", son1toson2.header.frame_id.c_str(), 
            son1toson2.child_frame_id.c_str(), son1toson2.transform.translation.x, son1toson2.transform.translation.y, son1toson2.transform.translation.z);

            geometry_msgs::PointStamped psAtSon2 = buffer.transform(psAtSon1, "son2");
            ROS_INFO("Coodinate in son2 (%.2f, %.2f, %.2f)", psAtSon2.point.x, psAtSon2.point.y, psAtSon2.point.z);
        }
        catch(const std::exception& e)
        {
            ROS_INFO("Error massage: %s", e.what());
        }
        
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}