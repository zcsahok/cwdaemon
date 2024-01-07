#ifndef CWDAEMON_TEST_LIB_MORSE_RECEIVER_H
#define CWDAEMON_TEST_LIB_MORSE_RECEIVER_H




#include "cw_rec_utils.h"
#include "misc.h"
#include "thread.h"




typedef struct morse_receiver_config_t {
	tty_pins_t observer_tty_pins_config;
	int wpm;                                 /**< Receiver speed (words-per-minute), for receiver working in non-adaptive mode (which is usually the case). */
} morse_receiver_config_t;




typedef struct morse_receiver_t {
	thread_t thread;
	morse_receiver_config_t config;
} morse_receiver_t;




morse_receiver_t * morse_receiver_ctor(const morse_receiver_config_t * config);
void morse_receiver_dtor(morse_receiver_t ** receiver);
int morse_receiver_start(morse_receiver_t * receiver);
int morse_receiver_wait(morse_receiver_t * receiver);




/**
   @brief Test whether text received through Morse receiver matches expected string

   @param[in] received_text Text received by Morse receiver
   @param[in] expected_message The text that we have expected to receive

   @return true if there is a match
   @return false otherwise
*/
bool morse_receive_text_is_correct(const char * received_text, const char * expected_message);




#endif /* #ifndef CWDAEMON_TEST_LIB_MORSE_RECEIVER_H */
