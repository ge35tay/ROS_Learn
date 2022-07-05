#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
/*
    public relativ relationship between 2 frames
    step1: include 
    step2: node intialization
    step3 create publisher
    step4: edit the message
    step5: publish the message
    step6 spin()
*/

int main(int argc, char* argv[])
{   
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_pub");
    ros::NodeHandle nh;

    // initialize publisher
    tf2_ros::StaticTransformBroadcaster pub;

    // edit the message
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = "base_link";    // reference frame
    tfs.child_frame_id = "laser";
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;

    tf2::Quaternion qtn;   // quaternion obejct
    qtn.setRPY(0, 0, 0);  // unit: rad in pi

    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();

    // publish
    pub.sendTransform(tfs);
    ros::spin();

    // Euler angle to quaternion
    return 0;
}