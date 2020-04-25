#include "gui.h"
//#include "world_vis/PID_Gains.h"
//#include "ros/ros.h"


GUI* GUI::instance = NULL;
// int* kp_ang_vel_direction;
// int* kp_ang_vel_heading;
// int* kp_lin_vel;
// int* kp_ang_vel;
// int* ki_lin_vel;
// int* ki_ang_vel;
// int* kd_lin_vel;
// int* kd_ang_vel;




// singleton
GUI::GUI(){
    strcpy(path_obstacles, "../obstacle_files/obstacles_300.json");
    status = new std::string;
    tele_angle = new int;

    pid_gains.kp_lin_vel = 1.0;
    pid_gains.ki_lin_vel = 0.7;
    pid_gains.kd_lin_vel = 0.5;

    pid_gains.kp_ang_vel_direction = 10.0;
    pid_gains.kp_ang_vel_heading = 10.0;
    pid_gains.ki_ang_vel = 0.0;
    pid_gains.kd_ang_vel = 0.0;
    //pid_gains.kp_ang_vel = 0.0;
    *status = "gains";

}

GUI* GUI::Instance(){
    if (!instance)   // Only allow one instance of class to be generated.
	instance = new GUI;

    return instance;
}


	//world_vis::PID_Gains pid_gains;
	//ros::init();
	 //ros::init(argc, argv, "gui");


	// ros::NodeHandle node_handle;
	// ros::Publisher pid_gains_pub = node_handle.advertise<world_vis::PID_Gains>( "pid_gains", 1 );
void GUI::render(){


    // draw the main window
    {
	ImGui::Begin("controls");

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("Controls", tab_bar_flags)){
	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("Obstacles")){
		ImGui::InputText("Load Obstacles Path", path_obstacles, IM_ARRAYSIZE(path_obstacles));

		if( ImGui::Button("Load Obstacels") ){
		    std::cout << "loading obstacles from: " << path_obstacles << "\n";
		    world->load_obstacles(path_obstacles);
		}

		if( ImGui::Button("Load Empty") ){
		    world->load_obstacles("../obstacle_files/empty.json");
		}

		ImGui::EndTabItem();
	    }

	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("Vehicle Position")){

		ImGui::InputInt("Teleport Angle", tele_angle);
		if( ImGui::Button("Teleport Vehicle") ){
		    *status = "tele";
		}

		ImGui::InputInt("Tracked Angle", tracked_angle);
		if( ImGui::Button("Set Tracked") ){
		    *status = "tracked";
		}
		if( ImGui::Button("Clear Tracked") ){
		    world->clear_track();
		}
		ImGui::EndTabItem();
	    }

	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("Goals/Trajectories")){

		if( ImGui::Button("Set End Goal") ){
		    *status = "end_goal";
		}

		if( ImGui::Button("Perform Global Plan") ){
		    world->publish_global_plan_start();
		}

		if( ImGui::Button("Run Local Planner") ){
		    world->publish_local_plan_start();
		}

		ImGui::EndTabItem();
	    }

	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("PID Tuning")){

    	ImGui::InputFloat("kp_lin_vel",  &(pid_gains.kp_lin_vel) , 0.01);
    	//pid_gains.kp_lin_vel = &kp_lin_vel;//x / 100.0;

    	ImGui::InputFloat("ki_lin_vel", &(pid_gains.ki_lin_vel), 0.01);
    	//pid_gains.ki_lin_vel = &ki_lin_vel;//x / 100.0;

    	ImGui::InputFloat("kd_lin_vel", &(pid_gains.kd_lin_vel), 0.01);
    	//pid_gains.kd_lin_vel = &kd_lin_vel;//x / 100.0;

    	//ImGui::InputFloat("kp_ang_vel", pid_gains.kp_ang_vel);

    	ImGui::InputFloat("kp_ang_vel_direction", &(pid_gains.kp_ang_vel_direction), 0.01);
    	//pid_gains.kp_ang_vel_direction = &kp_ang_vel_direction;//x / 100.0;

		ImGui::InputFloat("kp_ang_vel_heading", &(pid_gains.kp_ang_vel_heading), 0.01);
		//pid_gains.kp_ang_vel_heading = &kp_ang_vel_heading;//x / 100.0;

		ImGui::InputFloat("ki_ang_vel", &(pid_gains.ki_ang_vel), 0.01);
		//pid_gains.ki_ang_vel = &ki_ang_vel;//x / 100.0;

		ImGui::InputFloat("kd_ang_vel", &(pid_gains.kd_ang_vel), 0.01);
		//pid_gains.kd_ang_vel = &kd_ang_vel;//x / 100.0;


		if( ImGui::Button("Set Gains") ){
		    //pid_gains_pub.publish(pid_gains);
		    *status = "gains";
		}
		ImGui::EndTabItem();
	    }
	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("Show/Hide")){

		ImGui::EndTabItem();
	    }

	    ImGui::EndTabBar();
	}

	ImGui::End();
    }

    // draw the vehicle info window
    {
	ImGui::Begin("state");
	ImGui::Text("Linear Vel: %f", veh_state.linear_vel);
	ImGui::Text("Steering Angle Vel: %f", veh_state.steering_angle_vel);
	ImGui::Text("linear Accel: %f", veh_state.linear_accel);
	ImGui::Text("Steering Angle Accel: %f", veh_state.steering_angle_acel);

	ImGui::Text("x: %f", veh_state.pos.x);
	ImGui::Text("y: %f", veh_state.pos.y);
	ImGui::Text("angle: %f", (int)(veh_state.vehicle_angle) % 360);

	ImGui::End();
    }
}
