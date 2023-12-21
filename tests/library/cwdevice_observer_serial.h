#ifndef CW_KEY_SOURCE_SERIAL_H
#define CW_KEY_SOURCE_SERIAL_H




#include <stdbool.h>
#include <sys/ioctl.h> /* For those users of the key source that need to specify TIOCM_XXX tty pin. */




#include "cwdevice_observer.h"




/**
   Implementation of cw_key_source_t::open_fn function specific to serial line file
*/
bool cw_key_source_serial_open(cw_key_source_t * source);




/**
   Implementation of cw_key_source_t::close_fn function specific to serial line file
*/
void cw_key_source_serial_close(cw_key_source_t * source);




/**
   Implementation of cw_key_source_t::poll_once_fn function specific to serial line file
*/
bool cw_key_source_serial_poll_once(cw_key_source_t * source, bool * key_is_down, bool * ptt_is_on);




#endif /* #ifndef CW_KEY_SOURCE_SERIAL_H */
