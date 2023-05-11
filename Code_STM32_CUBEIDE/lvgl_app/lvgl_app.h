/*
 * lvgl_app.h
 *
 *  Created on: 8 févr. 2023
 *      Author: laurentf
 */

#ifndef LVGL_APP_LVGL_APP_H_
#define LVGL_APP_LVGL_APP_H_

#include <stdint.h>
#include "lvgl/lvgl.h"

#define TAB_NUMBER 3
#define CC_SLIDERS 4
#define GAIN_INIT 0
#define TAB_CC 0
#define TAB_MIDI_IN 1
#define TAB_KEYBOARD 2



int disp_cc_values(int argc, char ** argv);
int disp_midi_in(int argc, char ** argv);
void create_tabs(void);
void create_sliders(void);
void create_midi_in(void);
void button(lv_coord_t posX,lv_coord_t posY, const char * name);
void button2(lv_coord_t posX,lv_coord_t posY, const char * name);
void GrilleButtons(void);
static void btn_event_cb(lv_event_t * e);

static void btn_event_cb_C(lv_event_t * e );
static void btn_event_cb_Cd(lv_event_t * e );
static void btn_event_cb_D(lv_event_t * e );
static void btn_event_cb_Dd(lv_event_t * e );
static void btn_event_cb_E(lv_event_t * e );
static void btn_event_cb_F(lv_event_t * e );
static void btn_event_cb_Fd(lv_event_t * e );
static void btn_event_cb_G(lv_event_t * e );
static void btn_event_cb_Gd(lv_event_t * e );
static void btn_event_cb_A(lv_event_t * e );
static void btn_event_cb_Ad(lv_event_t * e );
static void btn_event_cb_B(lv_event_t * e );

static void btn_event_octaveP(lv_event_t * e );
static void btn_event_octaveM(lv_event_t * e );

#endif /* LVGL_APP_LVGL_APP_H_ */
