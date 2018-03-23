#!/usr/bin/env python

import rospy

if __name__ == '__main__':
    try:
        rospy.init_node('simple', anonymous=False)
        rospy.spin()
        
    except rospy.ROSInterruptException:
        pass