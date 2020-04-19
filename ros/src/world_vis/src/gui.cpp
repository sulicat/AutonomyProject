#include "gui.h"

GUI* GUI::instance = NULL;

// singleton
GUI::GUI(){}

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

                if (ImGui::BeginTabItem("Obstacles")){
                    ImGui::EndTabItem();
		}

                if (ImGui::BeginTabItem("Vehicle Position")){
                    ImGui::EndTabItem();
		}

                if (ImGui::BeginTabItem("Goals/Trajectories")){
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
