#!/usr/bin/env python

import rospy
import tf
import random
import math

def tf_sub():
	rospy.init_node('tf_sub', anonymous=False)
	rate = rospy.Rate(1)
	listener = tf.TransformListener()

	while not rospy.is_shutdown():
		try:
			(bf2odom_trans,bf2odom_rot) = listener.lookupTransform('/base_footprint',
				'/object', rospy.Time(0))

			rospy.loginfo("/base_footprint -> /odom [%lf, %lf, %lf]",
				bf2odom_trans[0], bf2odom_trans[1], bf2odom_rot[2])

		except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
			continue


if __name__ == '__main__':
    try:
        tf_sub()
    except rospy.ROSInterruptException:
        pass
