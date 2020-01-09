#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string.h>

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();

private:
    // Read ros param, return true if successful
	bool readParameters();

	// Callback methods
	void scanCallback(const sensor_msgs::LaserScan &scan_msg);

	// node handle
	ros::NodeHandle nodeHandle_;
	
	// subscriber to /scan topic
	ros::Subscriber  scan_sub_;

	std::string subscriberTopic_;
	int queue_size;
};

} /* namespace */
