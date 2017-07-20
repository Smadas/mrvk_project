//
// Created by matejko on 11.7.2017.
//

#include "reverse_movement_recovery/reverse_movement_recovery.h"
#include <pluginlib/class_list_macros.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_datatypes.h>

PLUGINLIB_DECLARE_CLASS(reverse_movement_recovery, ReverseMovementRecovery, reverse_movement_recovery::ReverseMovementRecovery, nav_core::RecoveryBehavior)

namespace reverse_movement_recovery{
    ReverseMovementRecovery::ReverseMovementRecovery() : initialized_(false), global_costmap_(NULL),
                                                         local_costmap_(NULL), tf_(NULL){

    }

    void ReverseMovementRecovery::initialize(std::string name, tf::TransformListener* tf,
            costmap_2d::Costmap2DROS* global_costmap, costmap_2d::Costmap2DROS* local_costmap){
        if(!initialized_){
            name_ = name;
            tf_ = tf;
            global_costmap_ = global_costmap;
            local_costmap_ = local_costmap;

            ros::NodeHandle private_nh("~/" + name_);
            private_nh.param("rmr/distance", distance_, 0.2);
            private_nh.param("rmr/escape_vel", escape_vel_, 0.2);

            vel_pub_ = private_nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

            initialized_ = true;
        }
        else{
            ROS_ERROR("You should not call initialize twice on this object, doing nothing");
        }
    }

    void ReverseMovementRecovery::runBehavior(){

        tf::StampedTransform transform;
        try{
            tf_->lookupTransform("/map","/base_link", ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("Transform exception: %s",ex.what());
            ros::Duration(1.0).sleep();
            return;
        }
        tf::Point start = transform.getOrigin();
        tf::Point goal = start - tf::Point(distance_,0,0);
        double tolerance = 0.05;    //[m]
        double yChangeTolerance = 0.1;   //[m]

        ros::Rate rate(20);
        while(ros::ok()){
            try{
                tf_->lookupTransform("/map","/base_link", ros::Time(0), transform);
            }
            catch (tf::TransformException ex){
                ROS_ERROR("Transform exception: %s",ex.what());
                ros::Duration(1.0).sleep();
                return;
            }
            tf::Point dif = goal - transform.getOrigin();
            if(fabs(dif.y()) >  yChangeTolerance ){
                ROS_WARN("Abborting reverse movement recovery. Y coordinate change too large");
                return;
            }
            if(fabs(dif.x()) < tolerance){
                pubVel(0);
                return;
            }
            tf::Stamped<tf::Pose> pose;
            std::vector<geometry_msgs::Point> footprint;
            if(!local_costmap_->getRobotPose(pose)) {
                ROS_WARN("Abborting reverse movement recovery. Failed to get robot pose");
                return;
            }
 /*
 *          TODO chck for obstacles behind robot
 *          local_costmap_->getOrientedFootprint(footprint);
 */
            pubVel(-escape_vel_);
            rate.sleep();
        }
    }

    void ReverseMovementRecovery::pubVel(double vel) {
        geometry_msgs::Twist cmd;
        cmd.linear.x = vel;
        vel_pub_.publish(cmd);
    }
};
