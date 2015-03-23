/*
 * pathplanning_costfunction.h
 *
 * This file contains all functions/variables for calculating an optimal path to a given target position.
 *
 *  Created on: 02.03.2015
 *      Author: Jonas
 */

#ifndef PATHPLANNING_COSTFUNCTION_H_
#define PATHPLANNING_COSTFUNCTION_H_


#include <math.h>
#include <stdint.h>

#include "pp_config.h"
#include "pp_navigator.h"
//#include "pp_navigation_helper.h"

#if C_DEBUG != 1
	#include "pp_topics_handler.h"
#endif




/* @brief Set the configuration Parameters from QGround Control */
void cm_set_configuration(float Gw, float Go, float Gm, float Gs, float Gt, float GLee, float ObstSafetyRadius, float ObstHorizon, float WindowSize);



/* @brief Calculate the optimal heading and give corresponding command to helsman*/
float cm_NewHeadingReference(struct nav_state_s *state, struct nav_field_s *field);





#endif /* PATHPLANNING_COSTFUNCTION_H_ */