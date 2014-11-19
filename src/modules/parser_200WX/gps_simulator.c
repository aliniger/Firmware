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
 * @file gps_simulator.c
 *
 * Interface for common utility functions.
 *
 *
 * @author Marco Tranzatto <marco.tranzatto@gmail.com>
 */

#include "gps_simulator.h"



static int32_t elap_sec = 0;//start from midnight

#if GPS_SIMULATION == 1 //save memory, define geo_steady_state only in simulation mode


#define NUM_GEO_STEADY_STATE 250

static int32_t counter_steady_state = 0;

static double geo_steady_state[NUM_GEO_STEADY_STATE][3] = {{8.5526656,47.3785248,498.6000366},
                                                           {8.5527016,47.3785312,497.9000244},
                                                           {8.5527032,47.3785312,497.4000244},
                                                           {8.5526864,47.3785312,496.7000122},
                                                           {8.552676,47.3785248,497.6000366},
                                                           {8.5526808,47.3785312,499.7000122},
                                                           {8.5526632,47.3785408,500.8000183},
                                                           {8.552644,47.3785408,502.2000122},
                                                           {8.5526352,47.3785472,503.2000122},
                                                           {8.5526416,47.3785312,504.1000366},
                                                           {8.55264,47.3785312,505.6000366},
                                                           {8.5526152,47.3785312,507.9000244},
                                                           {8.5525976,47.3785248,508.4000244},
                                                           {8.5526064,47.3785248,507.5000305},
                                                           {8.5526216,47.3784992,506.8000183},
                                                           {8.5526208,47.3784672,506.5000305},
                                                           {8.552624,47.3784608,506.2000122},
                                                           {8.552624,47.3784736,505.4000244},
                                                           {8.5526296,47.3784832,505.7000122},
                                                           {8.552644,47.3784832,506.7000122},
                                                           {8.5526368,47.3784736,507.6000366},
                                                           {8.5526392,47.3784672,508.3000183},
                                                           {8.55264,47.3784672,508.4000244},
                                                           {8.5526336,47.3784608,508.8000183},
                                                           {8.5526312,47.3784608,509.3000183},
                                                           {8.5526312,47.3784672,509.7000122},
                                                           {8.5526248,47.3784896,509.4000244},
                                                           {8.552616,47.3784992,508.5000305},
                                                           {8.552616,47.3785056,508.3000183},
                                                           {8.5526312,47.3785184,509.0000305},
                                                           {8.5526248,47.3785184,509.2000122},
                                                           {8.5526184,47.3784992,507.8000183},
                                                           {8.5526208,47.3784896,505.0000305},
                                                           {8.5526056,47.3784736,503.0000305},
                                                           {8.5525936,47.3784672,502.9000244},
                                                           {8.5525712,47.3784736,502.9000244},
                                                           {8.5525592,47.3784896,503.5000305},
                                                           {8.5525552,47.3785056,504.4000244},
                                                           {8.5525416,47.3785056,503.6000366},
                                                           {8.55252,47.3785056,503.5000305},
                                                           {8.552544,47.3784992,503.8000183},
                                                           {8.5525816,47.3784992,505.3000183},
                                                           {8.5526136,47.3785056,507.1000366},
                                                           {8.55264,47.3784992,506.6000366},
                                                           {8.55264,47.3784992,503.7000122},
                                                           {8.552624,47.3784992,501.3000183},
                                                           {8.5526,47.3784896,498.9000244},
                                                           {8.5526,47.3784992,499.2000122},
                                                           {8.5526136,47.3784896,500.3000183},
                                                           {8.5526136,47.3784736,501.0000305},
                                                           {8.5526104,47.3784672,502.4000244},
                                                           {8.5526136,47.3784672,504.6000366},
                                                           {8.5526392,47.3784672,506.1000366},
                                                           {8.5526632,47.3784736,507.0000305},
                                                           {8.5526712,47.3784992,507.9000244},
                                                           {8.5526712,47.3785056,508.9000244},
                                                           {8.5526632,47.3784992,508.6000366},
                                                           {8.5526448,47.3784896,506.7000122},
                                                           {8.55264,47.3784832,504.7000122},
                                                           {8.552652,47.3784832,502.9000244},
                                                           {8.5526552,47.3784832,501.3000183},
                                                           {8.552644,47.3784736,500.4000244},
                                                           {8.5526568,47.3784736,501.3000183},
                                                           {8.5526704,47.3784672,502.8000183},
                                                           {8.5526752,47.3784736,503.5000305},
                                                           {8.5526288,47.3784832,503.9000244},
                                                           {8.5525872,47.3784896,504.3000183},
                                                           {8.5525688,47.3784832,504.8000183},
                                                           {8.5525768,47.3784832,504.2000122},
                                                           {8.552616,47.3784736,503.7000122},
                                                           {8.5526664,47.3784736,502.2000122},
                                                           {8.5526992,47.3784736,500.9000244},
                                                           {8.5527016,47.3784672,500.5000305},
                                                           {8.5526968,47.3784736,500.7000122},
                                                           {8.552708,47.3784992,502.7000122},
                                                           {8.5527264,47.3785056,504.5000305},
                                                           {8.5527424,47.3785056,505.6000366},
                                                           {8.55274,47.3784992,505.5000305},
                                                           {8.5527312,47.3784896,505.7000122},
                                                           {8.5526944,47.3784832,505.5000305},
                                                           {8.5526664,47.3784736,505.2000122},
                                                           {8.5526616,47.3784832,504.5000305},
                                                           {8.5526712,47.3784896,503.3000183},
                                                           {8.5526896,47.3785056,502.4000244},
                                                           {8.5526936,47.3785184,501.7000122},
                                                           {8.5526816,47.3785184,500.6000366},
                                                           {8.552676,47.3785056,500.8000183},
                                                           {8.5526712,47.3785056,500.9000244},
                                                           {8.5526656,47.3784992,500.9000244},
                                                           {8.552676,47.3784992,501.1000366},
                                                           {8.5527,47.3784992,501.8000183},
                                                           {8.5527128,47.3785056,501.7000122},
                                                           {8.5527048,47.3784992,502.8000183},
                                                           {8.5526936,47.3784992,503.4000244},
                                                           {8.5526808,47.3784992,503.7000122},
                                                           {8.5526664,47.3784992,503.9000244},
                                                           {8.5526656,47.3784992,504.1000366},
                                                           {8.5526736,47.3784896,504.6000366},
                                                           {8.5526736,47.3784896,504.6000366},
                                                           {8.5526816,47.3784896,504.9000244},
                                                           {8.5526912,47.3785056,505.7000122},
                                                           {8.5526808,47.3785184,505.5000305},
                                                           {8.5526752,47.3785184,504.2000122},
                                                           {8.552676,47.3785184,504.1000366},
                                                           {8.5526816,47.3785056,504.7000122},
                                                           {8.5526816,47.3785056,504.6000366},
                                                           {8.5526752,47.3784992,505.0000305},
                                                           {8.5526584,47.3784832,504.1000366},
                                                           {8.5526616,47.3784672,504.2000122},
                                                           {8.5526712,47.3784672,503.7000122},
                                                           {8.5526736,47.3784672,504.3000183},
                                                           {8.5526736,47.3784608,504.7000122},
                                                           {8.5526848,47.3784608,504.6000366},
                                                           {8.5527016,47.3784672,504.5000305},
                                                           {8.5526896,47.3784736,505.5000305},
                                                           {8.5526752,47.3784736,504.7000122},
                                                           {8.55266,47.3784672,503.6000366},
                                                           {8.5526448,47.3784736,503.2000122},
                                                           {8.5526368,47.3784736,503.5000305},
                                                           {8.5526296,47.3784608,503.8000183},
                                                           {8.55264,47.3784416,504.9000244},
                                                           {8.552652,47.3784256,506.3000183},
                                                           {8.5526584,47.3784256,507.2000122},
                                                           {8.5526656,47.378432,507.7000122},
                                                           {8.5526704,47.3784608,509.0000305},
                                                           {8.5526752,47.3784832,509.7000122},
                                                           {8.5526656,47.3784896,511.0000305},
                                                           {8.5526464,47.3784992,510.9000244},
                                                           {8.5526352,47.3784896,509.8000183},
                                                           {8.552624,47.3784736,508.6000366},
                                                           {8.5526208,47.3784736,507.6000366},
                                                           {8.5526352,47.3784832,507.2000122},
                                                           {8.5526464,47.3784896,506.5000305},
                                                           {8.5526472,47.3784896,507.3000183},
                                                           {8.5526568,47.3784896,509.0000305},
                                                           {8.55266,47.3784896,509.6000366},
                                                           {8.5526808,47.3784896,510.0000305},
                                                           {8.5527064,47.3784992,508.0000305},
                                                           {8.5527128,47.3784992,505.7000122},
                                                           {8.5527016,47.3785056,503.8000183},
                                                           {8.5526944,47.3785184,504.9000244},
                                                           {8.5527,47.3785184,505.6000366},
                                                           {8.5527176,47.3785248,505.2000122},
                                                           {8.5527136,47.3785248,504.4000244},
                                                           {8.5527032,47.3785248,504.7000122},
                                                           {8.5526936,47.3785248,505.5000305},
                                                           {8.5526968,47.3785184,505.6000366},
                                                           {8.5527016,47.3785056,504.9000244},
                                                           {8.5527064,47.3785184,504.4000244},
                                                           {8.5527136,47.3785184,504.0000305},
                                                           {8.5527184,47.3785056,503.9000244},
                                                           {8.5527184,47.3784992,504.4000244},
                                                           {8.5527288,47.3784896,504.8000183},
                                                           {8.5527096,47.3784896,504.9000244},
                                                           {8.5526968,47.3784992,504.9000244},
                                                           {8.5527016,47.3784992,506.3000183},
                                                           {8.5527,47.3784992,507.1000366},
                                                           {8.5527016,47.3785056,506.3000183},
                                                           {8.5526944,47.3785184,506.2000122},
                                                           {8.5526968,47.3785248,507.3000183},
                                                           {8.5526888,47.3785312,508.9000244},
                                                           {8.5526704,47.3785248,510.6000366},
                                                           {8.5526736,47.3785248,510.2000122},
                                                           {8.5526808,47.3785184,508.4000244},
                                                           {8.5526816,47.3785184,506.4000244},
                                                           {8.5526752,47.3785056,506.6000366},
                                                           {8.5526784,47.3784992,507.0000305},
                                                           {8.552676,47.3784896,506.2000122},
                                                           {8.552676,47.3784992,505.0000305},
                                                           {8.5526808,47.3784992,504.9000244},
                                                           {8.5526936,47.3784992,505.3000183},
                                                           {8.5527,47.3784896,505.4000244},
                                                           {8.5526936,47.3784832,505.2000122},
                                                           {8.5526752,47.3784832,504.9000244},
                                                           {8.5526752,47.3784896,505.1000366},
                                                           {8.5526848,47.3784992,505.6000366},
                                                           {8.5526912,47.3785184,506.9000244},
                                                           {8.5526736,47.3785248,507.6000366},
                                                           {8.5526632,47.3785312,506.6000366},
                                                           {8.5526584,47.3785312,505.7000122},
                                                           {8.5526584,47.3785248,505.8000183},
                                                           {8.5526584,47.3785184,504.7000122},
                                                           {8.5526816,47.3785056,503.0000305},
                                                           {8.5526968,47.3785184,502.4000244},
                                                           {8.5526848,47.3785248,503.3000183},
                                                           {8.5526784,47.3785312,504.3000183},
                                                           {8.5526752,47.3785408,505.9000244},
                                                           {8.5526816,47.3785408,507.7000122},
                                                           {8.5526912,47.3785408,508.1000366},
                                                           {8.5526912,47.3785312,507.5000305},
                                                           {8.5526944,47.3785248,506.1000366},
                                                           {8.5526992,47.3784992,505.6000366},
                                                           {8.5526936,47.3784896,505.6000366},
                                                           {8.5526704,47.3784832,504.4000244},
                                                           {8.5526656,47.3784832,503.9000244},
                                                           {8.5526704,47.3784832,504.5000305},
                                                           {8.552676,47.3784896,504.4000244},
                                                           {8.5526808,47.3784896,503.8000183},
                                                           {8.5526888,47.3784896,502.9000244},
                                                           {8.5527016,47.3784992,503.3000183},
                                                           {8.5527032,47.3785184,504.1000366},
                                                           {8.5527016,47.3785056,504.3000183},
                                                           {8.5526912,47.3784896,503.9000244},
                                                           {8.5526912,47.3784896,502.8000183},
                                                           {8.5527048,47.3784896,503.1000366},
                                                           {8.5526936,47.3784832,504.0000305},
                                                           {8.5526688,47.3784736,505.3000183},
                                                           {8.5526472,47.3784672,504.6000366},
                                                           {8.5526504,47.3784672,504.2000122},
                                                           {8.5526704,47.3784672,503.1000366},
                                                           {8.5526848,47.3784736,503.7000122},
                                                           {8.5526736,47.3784832,505.4000244},
                                                           {8.55266,47.3784992,506.7000122},
                                                           {8.5526616,47.3785056,505.8000183},
                                                           {8.5526616,47.3785184,504.2000122},
                                                           {8.5526584,47.3785056,502.5000305},
                                                           {8.5526632,47.3784896,500.5000305},
                                                           {8.5526736,47.3784896,500.3000183},
                                                           {8.5526848,47.3784992,501.9000244},
                                                           {8.5526848,47.3785056,504.6000366},
                                                           {8.5526632,47.3784992,506.4000244},
                                                           {8.5526296,47.3784832,506.0000305},
                                                           {8.5526368,47.3784896,505.2000122},
                                                           {8.552652,47.3785184,504.3000183},
                                                           {8.5526712,47.3785408,503.2000122},
                                                           {8.5526808,47.3785472,502.1000366},
                                                           {8.552684,47.3785408,500.8000183},
                                                           {8.5526784,47.3785312,499.9000244},
                                                           {8.5526736,47.3785312,499.8000183},
                                                           {8.5526584,47.3785408,500.8000183},
                                                           {8.5526584,47.3785472,501.7000122},
                                                           {8.5526752,47.3785408,502.5000305},
                                                           {8.5526896,47.3785312,503.5000305},
                                                           {8.5527048,47.3785184,502.5000305},
                                                           {8.5527096,47.3784992,500.3000183},
                                                           {8.5527128,47.3784896,499.5000305},
                                                           {8.5527136,47.3784896,500.3000183},
                                                           {8.5527176,47.3784992,500.4000244},
                                                           {8.55272,47.3784992,498.0000305},
                                                           {8.5527264,47.3784992,495.4000244},
                                                           {8.55272,47.3784992,495.9000244},
                                                           {8.5527016,47.3784992,496.8000183},
                                                           {8.5526888,47.3785056,497.4000244},
                                                           {8.5526784,47.3785056,498.7000122},
                                                           {8.5526888,47.3784992,499.1000366},
                                                           {8.5526912,47.3784896,499.0000305},
                                                           {8.5527048,47.3784736,498.4000244},
                                                           {8.552708,47.3784832,498.9000244},
                                                           {8.5526992,47.3784992,498.4000244},
                                                           {8.5526896,47.3785248,499.3000183}};

#endif


double degree2nmea_ndeg(double input)
{
    double deg;
    double min;
    double secOver60;
    double app;

    deg = (int)input;
    app =((input - deg) * 60.0);
    min = (int) app;

    secOver60 = (app - ((int)app));
   // printf("deg: %f \t min %f \t secOver60: %f \n",deg, min, secOver60);

    return deg * 100.0 + min + secOver60;
}

void sim_steady_pos(char *buf, int *lgt){

    double lat = 0.0;
    double lon = 0.0;
    int32_t alt = 0;

    //force time to increase of 5 seconds
    elap_sec += 5;
    int32_t hh = elap_sec / 3600;
    int32_t mm = (elap_sec - hh * 3600) /60;
    double ss = (elap_sec - hh * 3600 - mm * 60);


    #if GPS_SIMULATION == 1

    lat = degree2nmea_ndeg(geo_steady_state[counter_steady_state][1]);
    lon = degree2nmea_ndeg(geo_steady_state[counter_steady_state][0]);
    alt = (int)geo_steady_state[counter_steady_state][2];

    counter_steady_state++;
    if(counter_steady_state >= NUM_GEO_STEADY_STATE)
        counter_steady_state = 0;

    #endif

    sprintf(buf, "GPGGA,hhmmss.ss,%4.4f,N,%4.4f,E,3,8,2,%d,M,********************* \
            GPVTG,182.9,T,181.0,M,0.0,N,0.0,K,A,*,\
            $,GPGSA,A,3,11,17,20,4,,,,,,,,,14.0,9.3,2*,55555...\
            $GPZDA,%02u%02u%06.3f,14,11,2014,00,00*4...5555555555555555555555555555555555\0\0",
            lat, lon, alt, hh, mm, ss);

    *lgt = strlen(buf);
}


