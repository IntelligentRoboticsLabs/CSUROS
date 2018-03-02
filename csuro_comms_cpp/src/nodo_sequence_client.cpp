#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <csuro_comms_cpp/SequenceAction.h>

typedef actionlib::SimpleActionClient<csuro_comms_cpp::SequenceAction> Client;

class MyNode
{
public:
	MyNode()
	: ac("sequence", true)
	{
		//ROS_INFO("Waiting for action server to start.");
		ac.waitForServer();
		//ROS_INFO("Action server started, sending goal.");
	}

	void doWork(long int until)
	{
		csuro_comms_cpp::SequenceGoal goal;
		goal.end_limit = until;

		ac.sendGoal(goal,
				boost::bind(&MyNode::doneCb, this, _1, _2),
				Client::SimpleActiveCallback(),
				boost::bind(&MyNode::feedbackCb, this, _1));

	}

	void feedbackCb(const csuro_comms_cpp::SequenceFeedbackConstPtr& feedback)
	{
		ROS_INFO("Current count %ld", feedback->current);
	}

	void doneCb(const actionlib::SimpleClientGoalState& state,
			const csuro_comms_cpp::SequenceResultConstPtr& result)
	{
		ROS_INFO("Finished in state [%s]", state.toString().c_str());
		ROS_INFO("Answer: %ld", result->last);
		ros::shutdown();
	}

private:
	Client ac;
};

int main (int argc, char **argv)
{
	ros::init(argc, argv, "sequence_client");
	ros::NodeHandle n;

	MyNode my_node;
	my_node.doWork(200);

	ros::spin();

	return 0;
}
