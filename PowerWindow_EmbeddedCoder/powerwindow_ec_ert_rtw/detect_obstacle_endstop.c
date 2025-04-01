/*
 * File: detect_obstacle_endstop.c
 *
 * Code generated for Simulink model 'powerwindow_ec'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Mar 31 18:22:11 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "detect_obstacle_endstop.h"
#include "rtwtypes.h"
#include "powerwindow_ec_private.h"

/* Includes for objects with custom storage classes */
#include "powerwindow_ec.h"

/* Output and update for atomic system: '<S1>/detect_obstacle_endstop' */
void detect_obstacle_endstop(void)
{
  /* RelationalOperator: '<S6>/endstop_bottom_disp' incorporates:
   *  Constant: '<S6>/position_endstop_bottom'
   *  Inport: '<Root>/window_position'
   */
  endstop_bottom = (window_position <= ((int32_T)(bFALSE * 250U) << 2));

  /* RelationalOperator: '<S6>/endstop_top_disp' incorporates:
   *  Constant: '<S6>/Constant'
   *  Inport: '<Root>/window_position'
   */
  endstop_top = (window_position >= position_endstop_top);

  /* Logic: '<S7>/ ' incorporates:
   *  Constant: '<S7>/Obstacle_off_value'
   *  Inport: '<Root>/obstacle_position'
   *  Inport: '<Root>/window_position'
   *  RelationalOperator: '<S7>/  '
   *  RelationalOperator: '<S7>/   '
   */
  powerwindow_ec_DW.u = ((window_position > obstacle_position) &&
    (obstacle_position > ((uint16_T)0U)));

  /* Logic: '<S7>/detection_obstacle' */
  obstacle_detection = (powerwindow_ec_DW.u && prev_move_up);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
