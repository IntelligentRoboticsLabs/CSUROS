#include <ros/ros.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <costmap_2d/costmap_2d_publisher.h>
#include <nav_core/base_global_planner.h>
#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>

using std::string;

#ifndef CSURO_GLOBAL_PLANNER_CPP
#define CSURO_GLOBAL_PLANNER_CPP

namespace csuro_global_planner {

class CSUROGlobalPlanner : public nav_core::BaseGlobalPlanner {
public:

	CSUROGlobalPlanner();
	CSUROGlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);


	void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
	bool makePlan(const geometry_msgs::PoseStamped& start,
			const geometry_msgs::PoseStamped& goal,
			std::vector<geometry_msgs::PoseStamped>& plan
	);

private:
	ros::NodeHandle nh_;

	costmap_2d::Costmap2D original_costmap_;
	costmap_2d::Costmap2D gradient_;

	costmap_2d::Costmap2DPublisher gradient_pub_;

	bool isCoordInMap(const costmap_2d::Costmap2D &costmap, const float& x, const float& y);


};
}; //namespace csuro_global_planner
#endif
