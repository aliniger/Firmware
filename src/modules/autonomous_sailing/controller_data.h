/****************************************************************************
 *
 *   Copyright (c) 2012, 2013 PX4 Development Team. All rights reserved.
 *   Author: Marco Tranzatto <marco.tranzatto@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * @file controller_data.h
 *
 * Store information used by controller.
 *
 * @author Marco Tranzatto <marco.tranzatto@gmail.com>
 */

#ifndef CONTROLLER_DATA_H
#define CONTROLLER_DATA_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "settings.h"
#include "send_msg_qgc.h"


/** @brief initialize controller data before starting*/
void cd_init_controller_data(void);

/** @brief modify size of the moving window for alpha angle*/
void cd_update_k(const uint16_t k, uint16_t opt_tack_alpha_win);

/** @brief modify size of the moving window for true wind speed*/
void cd_update_k_tws(const uint16_t k);

/** @brief modify size of the moving window for true wind angle*/
void cd_update_k_twd(const uint16_t k, uint16_t opt_tack_twd_win);

/** @brief update course over ground with a new raw value from the GPS*/
void cd_update_raw_cog(const float cog_r);

/** @brief update true wind (estimated) raw direction and speed*/
void cd_update_raw_tw_info(float twd_r, float tws_m_s);

/** @brief get the average value of alpha*/
float cd_get_alpha_dumas(void);

/** @brief get the average value of the true wind speed*/
float cd_get_tws(void);

/** @brief get the average value of true wind direction in sensor frame*/
float cd_get_twd_sns(void);

/** @brief update yaw and yawRate (w.r.t. true North)*/
void cd_update_raw_yaw_yaw_rate(float yaw_r, float yaw_rate_r);

/** @brief get alpha_yaw in Dumas' convention*/
float cd_get_alpha_yaw_dumas(void);

/** @brief set the maximum time after that alpha = alpha_yaw if cog not updated*/
void cd_set_max_time_cog_not_up(float max_time_cog_not_up_sec);

/** @brief get latest yawRate value*/
float cd_get_yaw_rate_sns(void);

/** @brief notify boat is performing a tack using either LQR or MPC*/
void cd_optimal_tack_started(void);

/** @brief notify that the "optimal" tack is completed*/
void cd_optimal_tack_completed(void);

/** @brief set if alpha must be computed using the real TWD or a fixed one */
void cd_use_fixed_twd(int32_t use_fixed_twd);

/** @brief set mean true wind direction */
void cd_set_mean_twd(float fixed_twd_r);

/** @brief set how alpha should be computed during a maneuver */
void cd_use_only_yaw_on_man(int use_only_yaw);

#endif // CONTROLLER_DATA_H
