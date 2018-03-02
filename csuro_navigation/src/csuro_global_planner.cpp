#include <pluginlib/class_list_macros.h>
#include <csuro_navigation/csuro_global_planner.h>

//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(csuro_global_planner::CSUROGlobalPlanner, nav_core::BaseGlobalPlanner)

using namespace std;

//Default Constructor
namespace csuro_global_planner {

CSUROGlobalPlanner::CSUROGlobalPlanner ()
: nh_(),
  gradient_(),
  original_costmap_(),
  gradient_pub_(&nh_, &gradient_, "/map", "/csuro_navigation_gradient", true)
{

}

CSUROGlobalPlanner::CSUROGlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros)
: nh_(),
  gradient_(),
  original_costmap_(),
  gradient_pub_(&nh_, &gradient_, "/map", "/csuro_navigation_gradient", true)
{
	initialize(name, costmap_ros);
}


void CSUROGlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros)
{
	ROS_INFO("CSURO Global Planner initializing...");

	original_costmap_ = *costmap_ros->getCostmap();
	gradient_ = original_costmap_;

	gradient_pub_.publishCostmap();
	ROS_INFO("CSURO Global Planner initilizazed");

}

bool CSUROGlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,  std::vector<geometry_msgs::PoseStamped>& plan )
{

	ROS_INFO("CSURO Global Planner making plan");

	float startX = start.pose.position.x;
	float startY = start.pose.position.y;
	float goalX = goal.pose.position.x;
	float goalY = goal.pose.position.y;

	ROS_INFO("New Goal coordinate (%lf, %lf) in %s", goalX, goalY, goal.header.frame_id.c_str());
	ROS_INFO("Coords vals in ([%lf, %lf], [%lf, %lf])",
			original_costmap_.getOriginX(), original_costmap_.getOriginY(),
			original_costmap_.getOriginX() + original_costmap_.getSizeInMetersX(),
			original_costmap_.getOriginY() + original_costmap_.getSizeInMetersY());

	if(!isCoordInMap(original_costmap_, goalX, goalY))
	{
		ROS_ERROR("Coordinate (%lf, %lf) is outside of the map", goalX, goalY);
		return false;
	}

	int startCellI, startCellJ;
	int goalCellI, goalCellJ;

	original_costmap_.worldToMapEnforceBounds(goalX, goalY, goalCellI, goalCellJ);
	original_costmap_.worldToMapEnforceBounds(startX, startY, startCellI, startCellJ);

	//Compute gradient
	ROS_INFO("SET (%d, %d) [%d]", goalCellI, goalCellJ, static_cast<int>(gradient_.getCost(goalCellI, goalCellJ)));
	gradient_.setCost (goalCellI, goalCellJ, 253);
	gradient_pub_.publishCostmap();

	//Compute path Todo :)

	plan.push_back(start);

	geometry_msgs::PoseStamped new_goal = goal;
	tf::Quaternion goal_quat = tf::createQuaternionFromYaw(
			atan2 (goal.pose.position.y - start.pose.position.y, goal.pose.position.x - start.pose.position.x ) / 2.0 );

	new_goal.pose.position.x = (goal.pose.position.x + start.pose.position.x) / 2.0;
	new_goal.pose.position.y = (goal.pose.position.y + start.pose.position.y) / 2.0;
	new_goal.pose.orientation.x = goal_quat.x();
	new_goal.pose.orientation.y = goal_quat.y();
	new_goal.pose.orientation.z = goal_quat.z();
	new_goal.pose.orientation.w = goal_quat.w();
	plan.push_back(new_goal);

	plan.push_back(goal);

	ROS_INFO("Plan ========================");
	std::vector<geometry_msgs::PoseStamped>::iterator it;
	for(it=plan.begin(); it<plan.end(); ++it)
	{
		ROS_INFO("%lf %lf", it->pose.position.x, it->pose.position.y);
	}
	ROS_INFO("=============================");

	ROS_INFO("CSURO Global Plann done");

	return true;
}

bool CSUROGlobalPlanner::isCoordInMap(const costmap_2d::Costmap2D &costmap, const float& x, const float& y)
{
	return true; //Todo :)
}


};
