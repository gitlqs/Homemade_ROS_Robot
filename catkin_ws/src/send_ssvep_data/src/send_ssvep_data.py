#!/usr/bin/env python
# license removed for brevity
import rospy
from geometry_msgs.msg import Twist

def talker(linearX, angularZ):
    pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)
    rospy.init_node('ssvep_data_sender', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        msg = Twist()
        msg.linear.x = linearX
        msg.linear.y = 0
        msg.linear.z = 0
        msg.angular.x = 0
        msg.angular.y = 0
        msg.angular.z = angularZ
        pub.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker(0, 0)
    except rospy.ROSInterruptException:
        pass
