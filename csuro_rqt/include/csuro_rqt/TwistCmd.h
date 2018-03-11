#ifndef twist_cmd_H
#define twist_cmd_H

#include <rqt_gui_cpp/plugin.h>
#include <csuro_rqt/ui_TwistCmd.h>
#include <QWidget>
#include <QPoint>
#include <QMenu>
#include <QInputDialog>

#include <QMessageBox>
#include <QString>

#include <thread>
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

namespace twist_cmd {

class TwistCmd
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  TwistCmd();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();

  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
     qt_gui_cpp::Settings& instance_settings) const;

  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
     const qt_gui_cpp::Settings& instance_settings);

  void loop();

  public slots:

    void increaseV();
    void decreaseV();
    void increaseW();
    void decreaseW();
    void stop();

private:
  Ui::TwistCmd ui_;
  QWidget* widget_;
  std::thread ros_t_;
  bool finished_;

  ros::Publisher vel_pub_;
  geometry_msgs::Twist vel_;

};
}  // namespace twist_cmd
#endif  // twist_cmd_H
