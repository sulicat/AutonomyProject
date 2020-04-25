/// Vehicle Controller
#include "cmath"
#include "math.h"
#include "ros/ros.h"
#include "ros_to_system.h"
#include "BaseVehicle.h"
#include "vehicle_controller/VehicleState.h"
#include "vehicle_controller/VehicleMoveCommand.h"
#include "vehicle_controller/Waypoint.h"
#include "vehicle_controller/Trajectory.h"
#include "vehicle_controller/PID_Gains.h"

#define PI 3.141592653589793
#define RAD_TO_DEG (180.0/PI)
#define DEG_TO_RAD (PI/180.0)

#define RATE (100)

float x_error = 0.0;
float y_error = 0.0;

float velocity_error = 0.0;
float velocity_error_prev = 0.0;

float angle_error = 0.0;
float angle_error_prev = 0.0;
float heading_error = 0.0;

float Kp_ang_vel_direction = 0.0;
float Kp_ang_vel_heading = 0.0;
float Kp_lin_vel = 1.0;
float Kp_ang_vel = 0.0;

float Ki_lin_vel = 0.7;
float Ki_ang_vel = 0.0;

float Kd_lin_vel = 0.5;
float Kd_ang_vel = 10000.0;

float prev_angle = 0.0;

int i = 0;
bool got_global_plan = false;
BaseVehicle vehicle;
//BaseVehicle* vehicle_state;
vehicle_controller::Waypoint wpt_tracking_goal;
vehicle_controller::Trajectory global_plan;
vehicle_controller::PID_Gains pid_gains;

BaseVehicle wpt_tracking_goal_state;
BaseVehicle* wpt_tracking_vehicle;
//float wpt_tracking_goal = 0.0;

void move_command_callback( vehicle_controller::VehicleMoveCommand move_command){
    std::cout << "Got move command\n";

    //vehicle.linear_vel = move_command.linear_vel;
    //vehicle.steering_angle_vel = move_command.steering_angle_vel;
}

void veh_state_callback( vehicle_controller::VehicleState veh_state ){
    simple_car::state_to_model( vehicle, veh_state );
    //vehicle_state = veh_state;
}

void tracked_goal_callback( vehicle_controller::Waypoint wpnt ){
    std::cout << "Got tracked goal\n ATT the Vehicle Controller\n";
    wpt_tracking_goal = wpnt;
    //simple_car::state_to_model( *wpt_tracking_vehicle, wpt_tracking_goal->state );
}

void global_plan_callback( vehicle_controller::Trajectory plan_in ){
    std::cout << "Got global_plan\n ATT the Vehicle Controller\n";
    global_plan = plan_in;
    got_global_plan = true;
}

void pid_gains_callback( vehicle_controller::PID_Gains _gains ){
pid_gains = _gains;
 std::cout << "Got the gains!\n";
}

int main( int argc, char** argv){

    ros::init(argc, argv, "vehicle_controller");
    ros::NodeHandle node_handle;
    ros::Subscriber sub_command = node_handle.subscribe("vehicle_move_command", 1000, move_command_callback);
    ros::Publisher move_command_pub = node_handle.advertise<vehicle_controller::VehicleMoveCommand>( "vehicle_move_command", 1 );
    ros::Subscriber sub = node_handle.subscribe("vehicle_state", 1, veh_state_callback);
    ros::Subscriber sub_tracked = node_handle.subscribe("tracked_goal", 1, tracked_goal_callback);
    ros::Subscriber sub_global_plan = node_handle.subscribe("global_plan", 1, global_plan_callback);
    ros::Subscriber sub_pid_gains = node_handle.subscribe("pid_gains", 1, pid_gains_callback);

    ros::Rate rate(RATE);

    while(ros::ok() ){
        //if( !wpt_tracking_goal ){
            //simple_car::state_to_model( *wpt_tracking_vehicle, wpt_tracking_goal->state );
            if (wpt_tracking_goal.state.pos.x != NULL){
                vehicle_controller::VehicleMoveCommand move_command;
                velocity_error_prev = velocity_error;
                angle_error_prev = angle_error;

                x_error = wpt_tracking_goal.state.pos.x - vehicle.pos.x;
                y_error = wpt_tracking_goal.state.pos.y - vehicle.pos.y;
                velocity_error = sqrt( pow( x_error , 2.0 ) + pow( y_error , 2.0 ) );

                move_command.linear_vel = pid_gains.kp_lin_vel * velocity_error - pid_gains.kd_lin_vel * vehicle.linear_vel + pid_gains.ki_lin_vel *  velocity_error_prev;
                angle_error = atan2( y_error , x_error ) * RAD_TO_DEG - vehicle.vehicle_angle;
                heading_error = wpt_tracking_goal.state.vehicle_angle - vehicle.vehicle_angle;
                //move_command.steering_angle_vel = Kp_ang_vel * angle_error - Kd_ang_vel * vehicle.steering_angle_vel + Ki_ang_vel *  angle_error_prev;
                move_command.steering_angle_vel = pid_gains.kp_ang_vel_direction * angle_error + pid_gains.kp_ang_vel_heading * heading_error - pid_gains.kd_ang_vel * vehicle.steering_angle_vel + pid_gains.ki_ang_vel *  angle_error_prev;

                if (velocity_error <= 0.5){
                     move_command.linear_vel = 0.0;
                     move_command.steering_angle_vel = 0.0;
                }
                // std::cout << "\n\n\n\nVelocity error: " << velocity_error << "\n";
                // std::cout << "Current x Position: " << vehicle.pos.x << "\n";
                // std::cout << "Current y Position: " << vehicle.pos.y << "\n";
                // std::cout << "Current angle: " << vehicle.vehicle_angle << "\n";

                move_command_pub.publish( move_command );

                //prev_angle = atan2( y_error , x_error ) * RAD_TO_DEG ;
            } else if ( false && got_global_plan){
                const int max =  global_plan.points.size();
                std::cout << "Got Inside!! ATT the Vehicle Controller\n";
                if ( i < max){
                    // lines[i].position = sf::Vector2f( global_plan->points[i].state.pos.x * ZOOM_FACTOR,
                    //                   global_plan->points[i].state.pos.y * ZOOM_FACTOR );
                    vehicle_controller::VehicleMoveCommand move_command;
                    velocity_error_prev = velocity_error;
                    angle_error_prev = angle_error;

                    x_error = global_plan.points[i].state.pos.x - vehicle.pos.x;
                    y_error = global_plan.points[i].state.pos.y - vehicle.pos.y;
                    velocity_error = sqrt( pow( x_error , 2.0 ) + pow( y_error , 2.0 ) );

                    if (velocity_error <= 4.0){
                        move_command.linear_vel = Kp_lin_vel * velocity_error - Kd_lin_vel * vehicle.linear_vel + Ki_lin_vel *  velocity_error_prev;

                        angle_error = atan2( y_error , x_error ) * RAD_TO_DEG - vehicle.vehicle_angle;
                        move_command.steering_angle_vel = Kp_ang_vel * angle_error - Kd_ang_vel * vehicle.steering_angle_vel + Ki_ang_vel *  angle_error_prev;
                        std::cout << "\n\n\n\nVelocity error: " << velocity_error << "\n";
                        std::cout << "Current x Position: " << vehicle.pos.x << "\n";
                        std::cout << "Current y Position: " << vehicle.pos.y << "\n";
                        std::cout << "Current angle: " << vehicle.vehicle_angle << "\n";

                        move_command_pub.publish( move_command );

                        i++;
                    } else {
                        x_error = global_plan.points[i-1].state.pos.x - vehicle.pos.x;
                        y_error = global_plan.points[i-1].state.pos.y - vehicle.pos.y;
                        velocity_error = sqrt( pow( x_error , 2.0 ) + pow( y_error , 2.0 ) );
                        move_command.linear_vel = Kp_lin_vel * velocity_error - Kd_lin_vel * vehicle.linear_vel + Ki_lin_vel *  velocity_error_prev;

                        angle_error = atan2( y_error , x_error ) * RAD_TO_DEG - vehicle.vehicle_angle;
                        move_command.steering_angle_vel = Kp_ang_vel * angle_error - Kd_ang_vel * vehicle.steering_angle_vel + Ki_ang_vel *  angle_error_prev;
                        std::cout << "\n\n\n\nVelocity error: " << velocity_error << "\n";
                        std::cout << "Current x Position: " << vehicle.pos.x << "\n";
                        std::cout << "Current y Position: " << vehicle.pos.y << "\n";
                        std::cout << "Current angle: " << vehicle.vehicle_angle << "\n";

                        move_command_pub.publish( move_command );



                    }



                } else if (i == max){
                    vehicle_controller::VehicleMoveCommand move_command;
                    move_command.linear_vel = 0.0;
                    move_command_pub.publish( move_command );
                    got_global_plan = false;
                    i = 0;

                }
            }

//es(1).x1 = error(1);
  //es(1).x = setpoint1(end) - theta1;
  //es(1).xd = theta1dot;
  //error(1) = es(1).x;
//function u = PDcontroller(gains, e)
   // u = gains.kp * e.x - gains.kd * e.xd + gains.ki * e.x1;
//end

    //move_command_pub.publish( move_command );

    ros::spinOnce();
    rate.sleep();
    }

    return 0;
}
