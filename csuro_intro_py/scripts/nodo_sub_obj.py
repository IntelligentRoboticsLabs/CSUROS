#!/usr/bin/env python

import rospy
from std_msgs.msg import Int64

class Listener:
	def __init__(self):
		rospy.Subscriber('/message', Int64, self.callback)

	def callback(self, data):
		rospy.loginfo(rospy.get_caller_id() + " %d received", data.data)

if __name__ == '__main__':
	
	rospy.init_node('num_subscriber', anonymous=False)
	l = Listener()
    
	try:
		rospy.spin()     	          
	except rospy.ROSInterruptException:
		pass