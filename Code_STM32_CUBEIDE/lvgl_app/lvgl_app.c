/*
 * lvgl_app.c
 *
 *  Created on: 8 févr. 2023
 *      Author: laurentf
 */

#include "lvgl_app.h"
#include "usbd_midi_if.h"

#include <stdio.h>

//#include "lvgl/lvgl.h"

static uint8_t cc_values[CC_SLIDERS];

static lv_obj_t * tab[TAB_NUMBER];
static lv_obj_t * tabview;
static char text_buffer[32];
static lv_obj_t * slider_CC_label[CC_SLIDERS];
static lv_obj_t * midi_in_label;

int octave = 36;


void create_CC_slider(lv_obj_t * tab, int num, const char * name);

int disp_cc_values(int argc, char ** argv)
{
	for (int i = 0 ; i < CC_SLIDERS ; i++)
	{
		printf("CC%d = %d\r\n", i, (int)cc_values[i]);
	}

	return 0;
}

int disp_midi_in(int argc, char ** argv)
{
	if (argc > 1)
	{
		for (int i = 1 ; i < argc ; i++)
		{
			lv_label_set_text(midi_in_label, argv[i]);
		}
	}
	else
	{
		printf("Error: need at least one argument\r\n");
	}

	return 0;
}

void create_tabs(void)
{
	tabview = lv_tabview_create(lv_scr_act(), LV_DIR_BOTTOM, 40);

	sprintf(text_buffer, "CC0-3");
	tab[TAB_CC] = lv_tabview_add_tab(tabview, text_buffer);

	sprintf(text_buffer, "MIDI IN");
	tab[TAB_MIDI_IN] = lv_tabview_add_tab(tabview, text_buffer);

	sprintf(text_buffer, "KEYBOARD");
	tab[TAB_KEYBOARD] = lv_tabview_add_tab(tabview, text_buffer);

	lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}

void create_sliders(void)
{
	create_CC_slider(tab[TAB_CC], 0, "CC0");
	create_CC_slider(tab[TAB_CC], 1, "CC1");
	create_CC_slider(tab[TAB_CC], 2, "CC2");
	create_CC_slider(tab[TAB_CC], 3, "CC3");
}

void create_midi_in(void)
{
	midi_in_label = lv_label_create(tab[TAB_MIDI_IN]);
	lv_label_set_text(midi_in_label, "Nothing yet...");
	lv_obj_align(midi_in_label, LV_ALIGN_TOP_LEFT, 10, 10);
}

static void slider_CC_event_cb(lv_event_t * e)
{
	lv_obj_t * slider = lv_event_get_target(e);
	uint32_t index = (uint32_t)lv_obj_get_user_data(slider);
	char buf[8];
	int32_t val = lv_slider_get_value(slider);
	lv_snprintf(buf, sizeof(buf), "%d", (int)val);

	cc_values[index] = val;

	lv_label_set_text(slider_CC_label[index], buf);
	lv_obj_align_to(slider_CC_label[index], slider, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
}

void create_CC_slider(lv_obj_t * tab, int num, const char * name)
{
	lv_obj_t * slider_CC = lv_slider_create(tab);
	lv_slider_set_range(slider_CC, 0 , 127);
	lv_slider_set_value(slider_CC, GAIN_INIT, LV_ANIM_ON);
	lv_obj_align(slider_CC, LV_ALIGN_TOP_MID, 0, 20 + 50*num);
	lv_obj_add_event_cb(slider_CC, slider_CC_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
	lv_obj_set_user_data(slider_CC, (void *)num);

	slider_CC_label[num] = lv_label_create(tab);
	sprintf(text_buffer, "%d", GAIN_INIT);	// Reuse old buffer, whatever
	lv_label_set_text(slider_CC_label[num], text_buffer);
	lv_obj_align_to(slider_CC_label[num], slider_CC, LV_ALIGN_OUT_RIGHT_MID, 20, 0);

	lv_obj_t * slider_CC_text_label;
	slider_CC_text_label = lv_label_create(tab);

	lv_label_set_text(slider_CC_text_label, name);
	lv_obj_align_to(slider_CC_text_label, slider_CC, LV_ALIGN_OUT_LEFT_MID, -15, 0);
}

#if LV_BUILD_EXAMPLES && LV_USE_BTN

static void btn_event_cb(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 10, 127);
    	processMidiMessage();
    	sendNoteOff(0, 10);
    	processMidiMessage();

    	//static uint8_t cnt = 0;
        //cnt++;

        /*Get the first child of the button which is the label and change its text*/
        //lv_obj_t * label = lv_obj_get_child(btn, 0);
        //lv_label_set_text_fmt(label, "Button: %d", cnt);
    }

}

static void btn_event_cb_C(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 0+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 0+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_Cd(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 1+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 1+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_D(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 2+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 2+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_Dd(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 3+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 3+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_E(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 4+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 4+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_F(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 5+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 5+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_Fd(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 6+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 6+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_G(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 7+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 7+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_Gd(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 8+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 8+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_A(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 9+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 9+octave);
    	processMidiMessage();
    }
}

static void btn_event_cb_Ad(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 10+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0, 10+octave);
    	processMidiMessage();

    }
}

static void btn_event_cb_B(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	sendNoteOn(0, 11+octave, 127);
    	processMidiMessage();
    	sendNoteOff(0,11+octave);
    	processMidiMessage();
    }
}

static void btn_event_octaveP(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	if(octave<=96){
    		octave = octave +12;
    	}
    }

    //static uint8_t cnt1 = 0;
    /*if(cnt1<11){
    	cnt1++;
    }*/

    /*Get the first child of the button which is the label and change its text*/
    //lv_obj_t * label = lv_obj_get_child(btn, 0);
    //lv_label_set_text_fmt(label, "+ : %d", octave/12);

}

static void btn_event_octaveM(lv_event_t * e )
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
    	if(octave>0)
    		octave = octave -12;
    }

    //static uint8_t cnt1 = 0;
    /*if(cnt1>0){
       cnt1--;
    }*/

    /*Get the first child of the button which is the label and change its text*/
    /*lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "- : %d", cnt1);*/

}



/**
 * Create a button with a label and react on click event.
 */
void button(lv_coord_t posX,lv_coord_t posY, const char * name)
{
    lv_obj_t * btn = lv_btn_create(tab[TAB_KEYBOARD]);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, posX, posY);                            /*Set its position*/
    lv_obj_set_size(btn, 90, 50);                          /*Set its size*/
    if(name=="C"){
    	lv_obj_add_event_cb(btn, btn_event_cb_C, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    }
    else if(name=="C#"){
    	lv_obj_add_event_cb(btn, btn_event_cb_Cd, LV_EVENT_ALL, NULL);
    }
    else if(name=="D"){
        lv_obj_add_event_cb(btn, btn_event_cb_D, LV_EVENT_ALL, NULL);
    }
    else if(name=="D#"){
        lv_obj_add_event_cb(btn, btn_event_cb_Dd, LV_EVENT_ALL, NULL);
    }
    else if(name=="E"){
        lv_obj_add_event_cb(btn, btn_event_cb_E, LV_EVENT_ALL, NULL);
    }
    else if(name=="F"){
        lv_obj_add_event_cb(btn, btn_event_cb_F, LV_EVENT_ALL, NULL);
    }
    else if(name=="F#"){
        lv_obj_add_event_cb(btn, btn_event_cb_Fd, LV_EVENT_ALL, NULL);
    }
    else if(name=="G"){
        lv_obj_add_event_cb(btn, btn_event_cb_G, LV_EVENT_ALL, NULL);
    }
    else if(name=="G#"){
        lv_obj_add_event_cb(btn, btn_event_cb_Cd, LV_EVENT_ALL, NULL);
    }
    else if(name=="A"){
        lv_obj_add_event_cb(btn, btn_event_cb_A, LV_EVENT_ALL, NULL);
    }
    else if(name=="A#"){
        lv_obj_add_event_cb(btn, btn_event_cb_Ad, LV_EVENT_ALL, NULL);
    }
    else if(name=="B"){
        lv_obj_add_event_cb(btn, btn_event_cb_B, LV_EVENT_ALL, NULL);
    }


    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, name);                     /*Set the labels text*/
    lv_obj_center(label);
}

void button2(lv_coord_t posX,lv_coord_t posY, const char * name)
{
	lv_obj_t * btn = lv_btn_create(tab[TAB_KEYBOARD]);     /*Add a button the current screen*/
	lv_obj_set_pos(btn, posX, posY);                            /*Set its position*/
	lv_obj_set_size(btn, 45, 70);
	if(name == "+"){
		lv_obj_add_event_cb(btn, btn_event_octaveP, LV_EVENT_ALL, NULL);
	}
	else if(name == "-"){
		lv_obj_add_event_cb(btn, btn_event_octaveM, LV_EVENT_ALL, NULL);
	}


	 lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
	 lv_label_set_text(label, name);                     /*Set the labels text*/
	 lv_obj_center(label);
}




void GrilleButtons(void){

	button(5,10, "C");
	button(105, 10, "C#");
	button(205, 10, "D");
	button(305,10, "D#");

	button(5,70, "E");
	button(105, 70, "F");
	button(205, 70, "F#");
	button(305,70, "G");

	button(5,130, "G#");
	button(105, 130, "A");
	button(205, 130, "A#");
	button(305,130, "B");

	button2(405, 20, "+");
	button2(405, 100, "-");

}

#endif
