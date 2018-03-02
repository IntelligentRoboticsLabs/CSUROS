#!/usr/bin/env python

import rospy
from std_msgs.msg import Int64

def callback(data):
	rospy.loginfo(rospy.get_caller_id() + " %d received", data.data)

if __name__ == '__main__':
    try:
       rospy.init_node('num_subscriber', anonymous=False)
        
       rospy.Subscriber('/message', Int64, callback)
       
       rospy.spin()     	
        
    except rospy.ROSInterruptException:
        pass