#include "gui.h"

GUI* GUI::instance = NULL;

// singleton
GUI::GUI(){
    //strcpy(path_obstacles, "../obstacle_files/obstacles_city_0.json");
    strcpy(path_obstacles, "../obstacle_files/obstacles_single.json");
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
    //world->publish_pid_gains(pid_gains);
}

GUI* GUI::Instance(){
    if (!instance)   // Only allow one instance of class to be generated.
	instance = new GUI;

    return instance;
}
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
		    world->load_obstacles("../obstacle_files/obstacles_300.json");
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

		if( ImGui::Button("RESET") ){
		    world->reset();
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
		    world->publish_local_plan_start( true );
		}

		if( ImGui::Button("Stop Local Planner") ){
		    world->publish_local_plan_start( false );
		}

		ImGui::EndTabItem();
	    }

	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("PID Tuning")){

		ImGui::InputFloat("kp_lin_vel",  &(pid_gains.kp_lin_vel) , 0.01);

		ImGui::InputFloat("ki_lin_vel", &(pid_gains.ki_lin_vel), 0.01);

		ImGui::InputFloat("kd_lin_vel", &(pid_gains.kd_lin_vel), 0.01);

		//ImGui::InputFloat("kp_ang_vel", pid_gains.kp_ang_vel);

		ImGui::InputFloat("kp_ang_vel_direction", &(pid_gains.kp_ang_vel_direction), 0.01);

		ImGui::InputFloat("kp_ang_vel_heading", &(pid_gains.kp_ang_vel_heading), 0.01);

		ImGui::InputFloat("ki_ang_vel", &(pid_gains.ki_ang_vel), 0.01);

		ImGui::InputFloat("kd_ang_vel", &(pid_gains.kd_ang_vel), 0.01);


		if( ImGui::Button("Set Gains") ){
		    world->publish_pid_gains(pid_gains);
		}
		ImGui::EndTabItem();
	    }
	    // --------------------------------------------------------------------------------
	    if (ImGui::BeginTabItem("Show/Hide")){
		ImGui::Checkbox("global plan", &(world->show_global_plan) );
		ImGui::Checkbox("local plan", &(world->show_local_plan) );
		ImGui::Checkbox("global rrt", &(world->show_global_rrt) );
		ImGui::Checkbox("local rrt", &(world->show_local_rrt) );

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
