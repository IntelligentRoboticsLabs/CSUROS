#include <ros/ros.h>


#include "csuro_rqt/TwistCmd.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace twist_cmd {

TwistCmd::TwistCmd()
: rqt_gui_cpp::Plugin()
, widget_(0)
, ros_t_(&TwistCmd::loop, this)
, finished_(false)
{
	setObjectName("TwistCmd");
}

void TwistCmd::initPlugin(qt_gui_cpp::PluginContext& context)
{
	QStringList argv = context.argv();

	widget_ = new QWidget();

	ui_.setupUi(widget_);


    connect(ui_.fwButton, &QPushButton::clicked, this, &TwistCmd::increaseV);
    connect(ui_.bkwButton, &QPushButton::clicked, this, &TwistCmd::decreaseV);
    connect(ui_.leftButton, &QPushButton::clicked, this, &TwistCmd::increaseW);
    connect(ui_.rightButton, &QPushButton::clicked, this, &TwistCmd::decreaseW);
    connect(ui_.stopButton, &QPushButton::clicked, this, &TwistCmd::stop);

	context.addWidget(widget_);

}

void TwistCmd::increaseV()
{
    vel_.linear.x += 0.5;
}


void TwistCmd::decreaseV()
{
    vel_.linear.x -= 0.5;
}

void TwistCmd::increaseW()
{
    vel_.angular.z += 0.5;
}

void TwistCmd::decreaseW()
{
    vel_.angular.z -= 0.5;
}

void TwistCmd::stop()
{
    vel_.angular.z = vel_.linear.x = 0.0;
}

void TwistCmd::saveSettings(qt_gui_cpp::Settings& plugin_settings,
    qt_gui_cpp::Settings& instance_settings) const
{
  // instance_settings.setValue(k, v)
}

void TwistCmd::restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
    const qt_gui_cpp::Settings& instance_settings)
{
  // v = instance_settings.value(k)
}

void TwistCmd::shutdownPlugin()
{
    finished_ = true;
	// TODO unregister all publishers here
}

void TwistCmd::loop()
{
    ros::NodeHandle n;

    ros::Rate loop_rate(10);

    vel_pub_ = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 10);

    while (ros::ok() && !finished_)
    {
      vel_pub_.publish(vel_);

      ros::spinOnce();
      loop_rate.sleep();
    }
}


} // namespace
PLUGINLIB_EXPORT_CLASS(twist_cmd::TwistCmd, rqt_gui_cpp::Plugin)
