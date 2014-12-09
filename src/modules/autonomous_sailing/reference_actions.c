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
 * @file reference_actions.c
 *
 * Reference actions computed offline.
 *
 * @author Marco Tranzatto <marco.tranzatto@gmail.com>
 */

#include "reference_actions.h"

/**
 * reference actions computed offline.
 * 1 = sail on starboard haul
 * 2 = sail on port haul
 * 3 = tack on the inner line
 * -1 = error in accessing matrix
*/

int16_t total_grids_number = 2;

float d_x = 50.0f;/// N / L

float d_y = 50.0f;

int8_t actions_w1_h1[2][13] = {
{3,3,3,3,3,3,3,3,3,3,3,3,3},
{3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1}};

int8_t actions_w1_h2[2][13] = {
{3,3,3,3,3,3,3,3,3,3,3,3,3},
{3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1}};

int8_t actions_w2_h1[2][13] = {
{3,3,3,3,3,3,3,3,3,3,3,3,3},
{3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1}};

int8_t actions_w2_h2[2][13] = {
{3,3,3,3,3,3,3,3,3,3,3,3,3},
{3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1}};

int16_t actions_row_number = 2;
int16_t actions_col_number = 13;

int16_t y_max[2] = {6,3};

