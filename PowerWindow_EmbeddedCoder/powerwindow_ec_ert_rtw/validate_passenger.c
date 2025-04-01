/*
 * File: validate_passenger.c
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

#include "validate_passenger.h"
#include "rtwtypes.h"
#include "powerwindow_ec_private.h"

/* Includes for objects with custom storage classes */
#include "powerwindow_ec.h"

/* Output and update for atomic system: '<S1>/validate_passenger' */
void validate_passenger(void)
{
  boolean_T passenger_validated_up_tmp;
  boolean_T rtb_checked_action;

  /* Logic: '<S12>/allow_action' incorporates:
   *  Inport: '<Root>/passenger_down'
   *  Logic: '<S12>/not'
   */
  passenger_validated_down = (passenger_down && (!endstop_bottom));

  /* Logic: '<S13>/allow_action' incorporates:
   *  Inport: '<Root>/passenger_up'
   *  Logic: '<S13>/not'
   */
  rtb_checked_action = (passenger_up && (!endstop_top));

  /* Logic: '<S14>/not_down' incorporates:
   *  Logic: '<S14>/up_after_down1'
   */
  passenger_validated_up_tmp = !passenger_validated_down;

  /* Logic: '<S14>/up_after_down' incorporates:
   *  Logic: '<S14>/not_down'
   */
  passenger_validated_up = (rtb_checked_action && passenger_validated_up_tmp);

  /* Logic: '<S14>/default_neutral' incorporates:
   *  DataTypeConversion: '<S15>/control input2'
   *  DataTypeConversion: '<S15>/control input3'
   *  Inport: '<Root>/passenger_down'
   *  Inport: '<Root>/passenger_up'
   *  Logic: '<S14>/neutral_after_up'
   *  Logic: '<S14>/not_up'
   *  Logic: '<S14>/not_up1'
   *  Logic: '<S14>/up_after_down1'
   *  Logic: '<S15>/Logical Operator'
   *  Logic: '<S15>/Logical Operator1'
   */
  passenger_validated_neutral = (((!passenger_up) && (!passenger_down) &&
    (!passenger_validated_up)) || ((!rtb_checked_action) &&
    passenger_validated_up_tmp));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
