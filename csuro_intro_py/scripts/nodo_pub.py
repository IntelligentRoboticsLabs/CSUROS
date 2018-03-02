#!/usr/bin/env python

import rospy
from std_msgs.msg import Int64

if __name__ == '__main__':
    try:
        rospy.init_node('num_publisher', anonymous=False)
        
        pub = rospy.Publisher('/message', Int64, queue_size=1)
        
        rate = rospy.Rate(10)
        count = 0;
        
        while not rospy.is_shutdown():
        	
        	count = count + 1
        	pub.publish(count)
        
        	rate.sleep()
        	
        
    except rospy.ROSInterruptException:
        pass