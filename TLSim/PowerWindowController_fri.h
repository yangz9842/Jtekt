/**************************************************************************************************\
 *** 
 *** Simulink model       : powerwindow_tl
 *** TargetLink subsystem : powerwindow_tl/PowerWindowController
 *** Codefile             : PowerWindowController_fri.h
 ***
 *** Generation date: 2025-03-31 17:59:10
 ***
 *** TargetLink version      : 22.1 from 02-Nov-2022
 *** Code generator version  : Build Id 22.1.0.27 from 2022-10-13 12:48:15
\**************************************************************************************************/

#ifndef POWERWINDOWCONTROLLER_FRI_H
#define POWERWINDOWCONTROLLER_FRI_H

#include "tl_defines_a.h"
#include "tl_basetypes.h"
#ifdef TL_FRAME
#include "PowerWindowController_frm.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************\
   MERGEABLE_GLOBAL: mergeable global variables (RAM) | Width: 8
\**************************************************************************************************/
extern MERGEABLE_GLOBAL Bool move_down_cmd;
extern MERGEABLE_GLOBAL Bool move_up_cmd;

/**************************************************************************************************\
   SLGlobal: Default storage class for global variables | Width: 16
\**************************************************************************************************/
extern UInt16 Sa1_obstacle_position; /* LSB: 2^-9 OFF: 0 MIN/MAX: 0 .. 1 */
extern UInt16 Sa1_window_position; /* LSB: 2^-9 OFF: 0 MIN/MAX: 0 .. 1 */

/**************************************************************************************************\
   SLGlobal: Default storage class for global variables | Width: 8
\**************************************************************************************************/
extern Bool Sa1_driver_down;
extern Bool Sa1_driver_neutral;
extern Bool Sa1_driver_up;
extern UInt8 Sa1_mode;
extern Bool Sa1_obstacle_detection;
extern Bool Sa1_passenger_down;
extern Bool Sa1_passenger_neutral;
extern Bool Sa1_passenger_up;

/**************************************************************************************************\
   GlobalStep: Default function class for not static model step functions
\**************************************************************************************************/
extern void PowerWindowController(void);

#ifdef __cplusplus
}
#endif

#endif /* POWERWINDOWCONTROLLER_FRI_H */
/*------------------------------------------------------------------------------------------------*\
  END OF FILE
\*------------------------------------------------------------------------------------------------*/
