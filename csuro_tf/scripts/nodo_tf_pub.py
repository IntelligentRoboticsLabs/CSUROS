#!/usr/bin/env python

import rospy
import tf
import random
import math

OBJ_PUB_RATE = 10.0

def publishObj(br):
	x = 20.0 * random.random() - 10.0;
	y = 20.0 * random.random() - 10.0;
	z = 0.0;
	ax = 0.0;
	ay = 0.0;
	az = 2.0 * math.pi * random.random() - math.pi;

	br.sendTransform((x, y, z),
                     tf.transformations.quaternion_from_euler(ax, ay, az),
                     rospy.Time.now(),
                     "object",
                     "base_footprint")

def tf_pub():
	rospy.init_node('tf_pub', anonymous=False)
	rate = rospy.Rate(20)
	br = tf.TransformBroadcaster()

	obj_ts = rospy.get_time()
	while not rospy.is_shutdown():
		if (rospy.get_time() - obj_ts) >  OBJ_PUB_RATE:
			obj_ts = rospy.get_time()
			publishObj(br);

if __name__ == '__main__':
    try:
        tf_pub()
    except rospy.ROSInterruptException:
        pass
