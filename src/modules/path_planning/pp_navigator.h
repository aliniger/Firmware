/*
 * pp_navigator.h
 *
 * This file contains a navigator. The navigator calculates a new heading reference and gives orders to the helsman.
 * In our case the helsman is the "autonomous_sailing module". The helsman polls the uORB topic "path_planning" for
 * changes and adjustes its control according to the orders.
 *
 *  Created on: 04.03.2015
 *      Author: Jonas Wirz <wirzjo@student.ethz.ch>
 */

#ifndef PP_NAVIGATOR_H_
#define PP_NAVIGATOR_H_

#include <stdbool.h>

#include "pp_config.h"
#include "pp_navigation_helper.h"

#if C_DEBUG == 0
#include "pp_topics_handler.h"
#endif


/**Struct containing the status of the Navigator */
struct nav_state_s {
	NEDpoint position; 				//Last known Position (x,y in NED-Frame) [m]
	float heading_cur;				//Current Heading of the boat [rad]	(Compass-Frame)
	float heading_ref;				//Heading Reference for optimal path [rad] (Compass-Frame)
	float wind_dir; 				//average direction of the wind (where the wind is coming from) [rad] (Compass-Frame)
	float wind_speed; 				//average Wind Speed [m/s]
	uint8_t targetNum; 				//Current number of target to be reached (limits number of targets to 256)
	bool maneuver;					//true, iff a maneuver is in progress
	uint64_t last_call; 			//Systemtime, when the Pathplanning was done the last time [us]
	bool command_maneuver;			//True, if the boat should do a maneuver, false else(<=> command a maneuver)
};

/**Struct containing the Race-Field-Information */
struct nav_field_s {
	NEDpoint targets[MAXTARGETNUMBER];	//Matrix holding all targets (waypoints) (in NED-Frame)
	uint8_t NumberOfTargets;		//Number of waypoints currently in the Matrix
	NEDpoint obstacles[MAXOBSTACLENUMBER];	//Matrix holding the obstacles (in NED-Frame)
	uint8_t NumberOfObstacles;		//Number of obstacles currently in the Matrix

	NEDpoint startline[2]; 			//Matrix containing the start-line [buoy1, buoy2]
};



/** @brief Init a Navigator */
void nav_init(void);


/** @brief Calculate a new optimal heading reference */
void nav_navigator(void);


/** @brief Speak to the helsman */
void nav_speak2helsman(void);


/** @brief New position information is available */
void nav_position_update(void);


/** @brief New wind-information is available */
void nav_wind_update(void);


/** @brief New heading information is available */
void nav_heading_update(void);


/** @brief Use the Yaw for calculating the heading */
void yaw_update(struct structs_topics_s *strs);


/** @brief Set Obstacles */
void nav_set_obstacle(uint8_t ObstNumber, PointE7 ObstPos);


/** @brief Set Targets */
void nav_set_target(uint8_t TargetNumber, PointE7 TargetPos);


/** @brief Set Targets in NED-Coordinates */
void nav_set_target_ned(uint8_t TargetNumber, NEDpoint TargetPos);


/** @brief Set the Start-Line */
void nav_set_startline(PointE7 buoy1, PointE7 buoy2);


/** @brief Set Configuration Parameters for the Navigator */
void nav_set_configuration(uint64_t period, uint32_t turnrate);


/** @brief Set the current position of the boat as the next target position*/
void nav_set_quick_target(void);


/** @brief Enable the communication between pathplanner and autonomous sailing app */
void nav_enable_navigator(uint8_t enable);


/** @brief Set the method that is used for pathplanning */
void nav_set_method(uint8_t method);


/** @brief Use Yaw instead of alpha from autonomous sailing app for Heading calcualtion of the boat */
void nav_set_use_yaw(uint8_t state);


/* FUNCTIONS FOR DEBUGGING */

/* @brief Set a fake-state for debugging */
void DEBUG_nav_set_fake_state(NEDpoint pos, float heading);


/* @brief Set a fake-field for debugging */
void DEBUG_nav_set_fake_field(NEDpoint target, NEDpoint obstacle);


#endif /* PP_NAVIGATOR_H_ */
