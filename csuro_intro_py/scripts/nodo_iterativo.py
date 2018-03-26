#!/usr/bin/env python

import rospy

if __name__ == '__main__':
    try:
        rospy.init_node('iterativo', anonymous=False)
        
        rate = rospy.Rate(20)
        count = 0;
        
        while not rospy.is_shutdown():
        	count = count + 1
        	rospy.loginfo("iteration %d" % count)
        	rate.sleep()
        	
        
    except rospy.ROSInterruptException:
        pass