#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

/*
    1. subscreibe the frame message 
    2. input a new coordinate and use tf to realize the transformation

    step 1: include head file
    step 2: code, initialization, nodehandle
    step 3: create subscreiber
    step 4: organize a coordinate data
    step 5: use tf to tranform
*/

int main(int argc, char *argv[])
{   
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_sub");
    ros::NodeHandle nh;
    // use buffer to buff the data
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";
    ps.header.stamp = ros::Time::now();
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    // add sleep to wait until the message is received
    //ros::Duration(2).sleep();

    ros::Rate rate(10);
    while(ros::ok())
    {   
        geometry_msgs::PointStamped ps_out;
        /*
        use the transformation function from buffer, because now data is all in buffer, not listener 
        parameter1: the to be transformed coordinate
        parameter2: target frame
        return: output coordinate 

        PS: when the function is called, the head file tf2_geometry_msgs/tf2_geometry_msgs.h should be included
        PS2: When running, it can be found the the base_link does not exist at first
                reason: subscreibing the data costs time, it is possible that, when the transform function is called, the relationship
                between coordinates not yet received, 
                Solution1: sleep before transformation function
                Solution2: try and catch
        */
       try{
        ps_out = buffer.transform(ps, "base_link");
        // output
        ROS_INFO("transformed coordinate: (%.2f, %.2f, %.2f), refereńce coordinate: %s", 
        ps_out.point.x,
        ps_out.point.y,
        ps_out.point.z,
        ps_out.header.frame_id.c_str());
        rate.sleep();
        ros::spinOnce();
       }
       catch(const std::exception& e)
       {
        ROS_INFO("strange error %s", e.what());
       }
        
    }
    return 0;
}