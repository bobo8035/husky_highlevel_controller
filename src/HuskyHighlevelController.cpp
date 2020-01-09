#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
	if (!readParameters()) 
        {
            ROS_ERROR("Could not read parameters.");
            ros::requestShutdown();
        }

	// subscribers
	scan_sub_ = nodeHandle_.subscribe(subscriberTopic_, queue_size , &HuskyHighlevelController::scanCallback, this);

	ROS_INFO("Successfully launched node.");
}

bool HuskyHighlevelController::readParameters()
    {
        if (!nodeHandle_.getParam("scan_sub_topic", subscriberTopic_)) return false;

        if (!nodeHandle_.getParam("scan_sub_queue_size", queue_size))return false;

        return true;
    }

HuskyHighlevelController::~HuskyHighlevelController()
{
}

void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan &scan_msg)
{
    float smallest_distance = 100;
    // the angle corresponding to the minimum distance


    //number of the elements in ranges array
    int arr_size = floor((scan_msg.angle_max-scan_msg.angle_min)/scan_msg.angle_increment);
    for (int i=0 ; i< arr_size ;i++)
    {
        if (scan_msg.ranges[i] < smallest_distance)
        {
             smallest_distance = scan_msg.ranges[i];
        }
    }
    ROS_INFO_STREAM("ROS_INFO_STREAM Minimum laser distance(m): "<<smallest_distance);
}

} /* namespace */
