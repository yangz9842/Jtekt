/*
 * File: validate_driver.c
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

#include "validate_driver.h"
#include "rtwtypes.h"
#include "powerwindow_ec_private.h"

/* Includes for objects with custom storage classes */
#include "powerwindow_ec.h"

/* Output and update for atomic system: '<S1>/validate_driver' */
void validate_driver(void)
{
  boolean_T driver_validated_up_tmp;
  boolean_T rtb_checked_action;

  /* Logic: '<S8>/Logical Operator' incorporates:
   *  Inport: '<Root>/driver_down'
   *  Logic: '<S8>/Logical Operator1'
   */
  driver_validated_down = (driver_down && (!endstop_bottom));

  /* Logic: '<S9>/allow_action' incorporates:
   *  Inport: '<Root>/driver_up'
   *  Logic: '<S9>/not'
   */
  rtb_checked_action = (driver_up && (!endstop_top));

  /* Logic: '<S11>/not_down' incorporates:
   *  Logic: '<S11>/up_after_down1'
   */
  driver_validated_up_tmp = !driver_validated_down;

  /* Logic: '<S11>/up_after_down' incorporates:
   *  Logic: '<S11>/not_down'
   */
  driver_validated_up = (rtb_checked_action && driver_validated_up_tmp);

  /* Logic: '<S11>/default_neutral' incorporates:
   *  DataTypeConversion: '<S10>/control input2'
   *  DataTypeConversion: '<S10>/control input3'
   *  Inport: '<Root>/driver_down'
   *  Inport: '<Root>/driver_up'
   *  Logic: '<S10>/Logical Operator'
   *  Logic: '<S10>/Logical Operator1'
   *  Logic: '<S11>/neutral_after_up'
   *  Logic: '<S11>/not_up'
   *  Logic: '<S11>/not_up1'
   *  Logic: '<S11>/up_after_down1'
   */
  driver_validated_neutral = (((!driver_up) && (!driver_down) &&
    (!driver_validated_up)) || ((!rtb_checked_action) && driver_validated_up_tmp));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
