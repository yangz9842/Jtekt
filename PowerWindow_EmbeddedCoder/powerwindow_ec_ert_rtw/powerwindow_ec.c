/*
 * File: powerwindow_ec.c
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

#include "powerwindow_ec.h"
#include "rtwtypes.h"
#include "detect_obstacle_endstop.h"
#include "validate_driver.h"
#include "validate_passenger.h"
#include "powerwindow_ec_private.h"

/* Named constants for Chart: '<S1>/control' */
#define powerwindow_ec_IN_DriverDown   ((uint8_T)1U)
#define powerwindow_ec_IN_DriverUp     ((uint8_T)1U)
#define powerwindow_ec_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define powerwindow_ec_IN_PassengerUp  ((uint8_T)1U)
#define powerwindow_ec_IN_autoDriverDown ((uint8_T)2U)
#define powerwindow_ec_IN_autoDriverUp ((uint8_T)2U)
#define powerwindow_ec_IN_autoPassengerDown ((uint8_T)1U)
#define powerwindow_ec_IN_autoPassengerUp ((uint8_T)2U)
#define powerwindow_ec_IN_driverDown   ((uint8_T)1U)
#define powerwindow_ec_IN_driverNeutral ((uint8_T)2U)
#define powerwindow_ec_IN_driverUp     ((uint8_T)3U)
#define powerwindow_ec_IN_emergencyDown ((uint8_T)1U)
#define powerwindow_ec_IN_iniDriverDown ((uint8_T)3U)
#define powerwindow_ec_IN_iniDriverUp  ((uint8_T)3U)
#define powerwindow_ec_IN_iniPassengerDown ((uint8_T)2U)
#define powerwindow_ec_IN_iniPassengerUp ((uint8_T)3U)
#define powerwindow_ec_IN_passengerDown ((uint8_T)1U)
#define powerwindow_ec_IN_passengerDown_g ((uint8_T)3U)
#define powerwindow_ec_IN_passengerUp  ((uint8_T)2U)
#define powerwindow_ec_IN_passengerneutral ((uint8_T)3U)
#define powerwindow_ec_IN_safe         ((uint8_T)2U)

/* Exported data definition */

/* Definition for custom storage class: ExportToFile */
boolean_T driver_down;                 /* '<Root>/driver_down' */
boolean_T driver_up;                   /* '<Root>/driver_up' */
boolean_T driver_validated_down;       /* '<S8>/Logical Operator' */
boolean_T driver_validated_neutral;    /* '<S11>/default_neutral' */
boolean_T driver_validated_up;         /* '<S11>/up_after_down' */
boolean_T endstop_bottom;              /* '<S6>/endstop_bottom_disp' */
boolean_T endstop_top;                 /* '<S6>/endstop_top_disp' */
boolean_T move_down;                   /* '<S1>/control' */
boolean_T move_up;                     /* '<S1>/control' */
boolean_T obstacle_detection;          /* '<S7>/detection_obstacle' */
uint16_T obstacle_position;            /* '<Root>/obstacle_position' */
boolean_T passenger_down;              /* '<Root>/passenger_down' */
boolean_T passenger_up;                /* '<Root>/passenger_up' */
boolean_T passenger_validated_down;    /* '<S12>/allow_action' */
boolean_T passenger_validated_neutral; /* '<S14>/default_neutral' */
boolean_T passenger_validated_up;      /* '<S14>/up_after_down' */
boolean_T prev_move_up;                /* '<S1>/Unit Delay' */
uint16_T window_position;              /* '<Root>/window_position' */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile uint8_T auto_down_time = 100U;/* Referenced by: '<S1>/Constant1' */
const volatile uint8_T auto_up_time = 100U;/* Referenced by: '<S1>/Constant2' */
const volatile uint8_T emergency_down_time = 100U;/* Referenced by: '<S1>/Constant' */
const volatile uint16_T position_endstop_top = 400U;/* Referenced by: '<S6>/Constant' */

/* Block signals and states (default storage) */
DW_powerwindow_ec_T powerwindow_ec_DW;

/* Real-time model */
static RT_MODEL_powerwindow_ec_T powerwindow_ec_M_;
RT_MODEL_powerwindow_ec_T *const powerwindow_ec_M = &powerwindow_ec_M_;

/* Forward declaration for local functions */
static void powerwindow__exit_internal_driverNeutral(void);
static void powerwindow_ec_safe(void);

/* Function for Chart: '<S1>/control' */
static void powerwindow__exit_internal_driverNeutral(void)
{
  /* Exit Internal 'driverNeutral': '<S2>:3' */
  switch (powerwindow_ec_DW.is_driverNeutral) {
   case powerwindow_ec_IN_passengerDown:
    /* Exit Internal 'passengerDown': '<S2>:7' */
    powerwindow_ec_DW.is_passengerDown = powerwindow_ec_IN_NO_ACTIVE_CHILD;

    /* Exit 'passengerDown': '<S2>:7' */
    move_down = false;
    powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_NO_ACTIVE_CHILD;
    break;

   case powerwindow_ec_IN_passengerUp:
    /* Exit Internal 'passengerUp': '<S2>:24' */
    powerwindow_ec_DW.is_passengerUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

    /* Exit 'passengerUp': '<S2>:24' */
    move_up = false;
    powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_NO_ACTIVE_CHILD;
    break;

   default:
    powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/control' */
static void powerwindow_ec_safe(void)
{
  /* During 'safe': '<S2>:1' */
  if (obstacle_detection) {
    /* Transition: '<S2>:60' */
    /* Exit Internal 'safe': '<S2>:1' */
    switch (powerwindow_ec_DW.is_safe) {
     case powerwindow_ec_IN_driverDown:
      /* Exit Internal 'driverDown': '<S2>:41' */
      powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_NO_ACTIVE_CHILD;

      /* Exit 'driverDown': '<S2>:41' */
      powerwindow_ec_DW.is_safe = powerwindow_ec_IN_NO_ACTIVE_CHILD;
      break;

     case powerwindow_ec_IN_driverNeutral:
      powerwindow__exit_internal_driverNeutral();
      powerwindow_ec_DW.is_safe = powerwindow_ec_IN_NO_ACTIVE_CHILD;
      break;

     case powerwindow_ec_IN_driverUp:
      /* Exit Internal 'driverUp': '<S2>:49' */
      powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

      /* Exit 'driverUp': '<S2>:49' */
      powerwindow_ec_DW.is_safe = powerwindow_ec_IN_NO_ACTIVE_CHILD;
      break;

     default:
      powerwindow_ec_DW.is_safe = powerwindow_ec_IN_NO_ACTIVE_CHILD;
      break;
    }

    powerwindow_ec_DW.is_c1_powerwindow_ec = powerwindow_ec_IN_emergencyDown;
    powerwindow_ec_DW.temporalCounter_i1 = 0U;

    /* Entry 'emergencyDown': '<S2>:59' */
    move_up = false;
    move_down = true;
  } else {
    switch (powerwindow_ec_DW.is_safe) {
     case powerwindow_ec_IN_driverDown:
      /* During 'driverDown': '<S2>:41' */
      if (endstop_bottom) {
        /* Transition: '<S2>:65' */
        /* Exit Internal 'driverDown': '<S2>:41' */
        powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_NO_ACTIVE_CHILD;

        /* Exit 'driverDown': '<S2>:41' */
        powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverNeutral;

        /* Entry 'driverNeutral': '<S2>:3' */
        /* Entry Internal 'driverNeutral': '<S2>:3' */
        /* Transition: '<S2>:23' */
        powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerneutral;

        /* Entry 'passengerneutral': '<S2>:4' */
        move_up = false;
        move_down = false;
      } else if (driver_validated_up) {
        /* Transition: '<S2>:71' */
        /* Exit Internal 'driverDown': '<S2>:41' */
        powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_NO_ACTIVE_CHILD;

        /* Exit 'driverDown': '<S2>:41' */
        move_down = false;
        powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverUp;

        /* Entry 'driverUp': '<S2>:49' */
        move_up = true;
        powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_DriverUp;
      } else {
        switch (powerwindow_ec_DW.is_driverDown) {
         case powerwindow_ec_IN_DriverDown:
          /* During 'DriverDown': '<S2>:47' */
          if (driver_validated_neutral) {
            /* Transition: '<S2>:64' */
            powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_NO_ACTIVE_CHILD;

            /* Exit 'driverDown': '<S2>:41' */
            powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverNeutral;

            /* Entry 'driverNeutral': '<S2>:3' */
            /* Entry Internal 'driverNeutral': '<S2>:3' */
            /* Transition: '<S2>:23' */
            powerwindow_ec_DW.is_driverNeutral =
              powerwindow_ec_IN_passengerneutral;

            /* Entry 'passengerneutral': '<S2>:4' */
            move_up = false;
            move_down = false;
          }
          break;

         case powerwindow_ec_IN_autoDriverDown:
          /* During 'autoDriverDown': '<S2>:42' */
          break;

         default:
          /* Constant: '<S1>/Constant1' */
          /* During 'iniDriverDown': '<S2>:43' */
          if (powerwindow_ec_DW.temporalCounter_i1 >= auto_down_time) {
            /* Transition: '<S2>:45' */
            if (driver_validated_neutral) {
              /* Transition: '<S2>:46' */
              powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_autoDriverDown;
            } else {
              /* Transition: '<S2>:48' */
              powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_DriverDown;
            }
          }
          break;
        }
      }
      break;

     case powerwindow_ec_IN_driverNeutral:
      /* During 'driverNeutral': '<S2>:3' */
      if (driver_validated_up) {
        /* Transition: '<S2>:62' */
        powerwindow__exit_internal_driverNeutral();
        powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverUp;

        /* Entry 'driverUp': '<S2>:49' */
        move_up = true;
        powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_iniDriverUp;
        powerwindow_ec_DW.temporalCounter_i1 = 0U;
      } else if (driver_validated_down) {
        /* Transition: '<S2>:63' */
        powerwindow__exit_internal_driverNeutral();
        powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverDown;

        /* Entry 'driverDown': '<S2>:41' */
        move_down = true;
        powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_iniDriverDown;
        powerwindow_ec_DW.temporalCounter_i1 = 0U;
      } else {
        switch (powerwindow_ec_DW.is_driverNeutral) {
         case powerwindow_ec_IN_passengerDown:
          /* During 'passengerDown': '<S2>:7' */
          if (endstop_bottom) {
            /* Transition: '<S2>:22' */
            /* Exit Internal 'passengerDown': '<S2>:7' */
            powerwindow_ec_DW.is_passengerDown =
              powerwindow_ec_IN_NO_ACTIVE_CHILD;

            /* Exit 'passengerDown': '<S2>:7' */
            powerwindow_ec_DW.is_driverNeutral =
              powerwindow_ec_IN_passengerneutral;

            /* Entry 'passengerneutral': '<S2>:4' */
            move_up = false;
            move_down = false;
          } else if (passenger_validated_up) {
            /* Transition: '<S2>:38' */
            /* Exit Internal 'passengerDown': '<S2>:7' */
            powerwindow_ec_DW.is_passengerDown =
              powerwindow_ec_IN_NO_ACTIVE_CHILD;

            /* Exit 'passengerDown': '<S2>:7' */
            move_down = false;
            powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerUp;

            /* Entry 'passengerUp': '<S2>:24' */
            move_up = true;
            powerwindow_ec_DW.is_passengerUp = powerwindow_ec_IN_PassengerUp;
          } else {
            switch (powerwindow_ec_DW.is_passengerDown) {
             case powerwindow_ec_IN_autoPassengerDown:
              /* During 'autoPassengerDown': '<S2>:9' */
              break;

             case powerwindow_ec_IN_iniPassengerDown:
              /* Constant: '<S1>/Constant1' */
              /* During 'iniPassengerDown': '<S2>:15' */
              if (powerwindow_ec_DW.temporalCounter_i1 >= auto_down_time) {
                /* Transition: '<S2>:16' */
                if (passenger_validated_neutral) {
                  /* Transition: '<S2>:17' */
                  powerwindow_ec_DW.is_passengerDown =
                    powerwindow_ec_IN_autoPassengerDown;
                } else {
                  /* Transition: '<S2>:18' */
                  powerwindow_ec_DW.is_passengerDown =
                    powerwindow_ec_IN_passengerDown_g;
                }
              }
              break;

             default:
              /* During 'passengerDown': '<S2>:13' */
              if (passenger_validated_neutral) {
                /* Transition: '<S2>:35' */
                powerwindow_ec_DW.is_passengerDown =
                  powerwindow_ec_IN_NO_ACTIVE_CHILD;

                /* Exit 'passengerDown': '<S2>:7' */
                powerwindow_ec_DW.is_driverNeutral =
                  powerwindow_ec_IN_passengerneutral;

                /* Entry 'passengerneutral': '<S2>:4' */
                move_up = false;
                move_down = false;
              }
              break;
            }
          }
          break;

         case powerwindow_ec_IN_passengerUp:
          /* During 'passengerUp': '<S2>:24' */
          if (passenger_validated_down) {
            /* Transition: '<S2>:39' */
            /* Exit Internal 'passengerUp': '<S2>:24' */
            powerwindow_ec_DW.is_passengerUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

            /* Exit 'passengerUp': '<S2>:24' */
            move_up = false;
            powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerDown;

            /* Entry 'passengerDown': '<S2>:7' */
            move_down = true;
            powerwindow_ec_DW.is_passengerDown =
              powerwindow_ec_IN_passengerDown_g;
          } else if (endstop_top) {
            /* Transition: '<S2>:36' */
            /* Exit Internal 'passengerUp': '<S2>:24' */
            powerwindow_ec_DW.is_passengerUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

            /* Exit 'passengerUp': '<S2>:24' */
            powerwindow_ec_DW.is_driverNeutral =
              powerwindow_ec_IN_passengerneutral;

            /* Entry 'passengerneutral': '<S2>:4' */
            move_up = false;
            move_down = false;
          } else {
            switch (powerwindow_ec_DW.is_passengerUp) {
             case powerwindow_ec_IN_PassengerUp:
              /* During 'PassengerUp': '<S2>:25' */
              if (passenger_validated_neutral) {
                /* Transition: '<S2>:37' */
                powerwindow_ec_DW.is_passengerUp =
                  powerwindow_ec_IN_NO_ACTIVE_CHILD;

                /* Exit 'passengerUp': '<S2>:24' */
                powerwindow_ec_DW.is_driverNeutral =
                  powerwindow_ec_IN_passengerneutral;

                /* Entry 'passengerneutral': '<S2>:4' */
                move_up = false;
                move_down = false;
              }
              break;

             case powerwindow_ec_IN_autoPassengerUp:
              /* During 'autoPassengerUp': '<S2>:27' */
              break;

             default:
              /* Constant: '<S1>/Constant2' */
              /* During 'iniPassengerUp': '<S2>:28' */
              if (powerwindow_ec_DW.temporalCounter_i1 >= auto_up_time) {
                /* Transition: '<S2>:32' */
                if (passenger_validated_neutral) {
                  /* Transition: '<S2>:30' */
                  powerwindow_ec_DW.is_passengerUp =
                    powerwindow_ec_IN_autoPassengerUp;
                } else {
                  /* Transition: '<S2>:31' */
                  powerwindow_ec_DW.is_passengerUp =
                    powerwindow_ec_IN_PassengerUp;
                }
              }
              break;
            }
          }
          break;

         default:
          /* During 'passengerneutral': '<S2>:4' */
          if (passenger_validated_up) {
            /* Transition: '<S2>:33' */
            powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerUp;

            /* Entry 'passengerUp': '<S2>:24' */
            move_up = true;
            powerwindow_ec_DW.is_passengerUp = powerwindow_ec_IN_iniPassengerUp;
            powerwindow_ec_DW.temporalCounter_i1 = 0U;
          } else if (passenger_validated_down) {
            /* Transition: '<S2>:34' */
            powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerDown;

            /* Entry 'passengerDown': '<S2>:7' */
            move_down = true;
            powerwindow_ec_DW.is_passengerDown =
              powerwindow_ec_IN_iniPassengerDown;
            powerwindow_ec_DW.temporalCounter_i1 = 0U;
          }
          break;
        }
      }
      break;

     default:
      /* During 'driverUp': '<S2>:49' */
      if (driver_validated_down) {
        /* Transition: '<S2>:68' */
        /* Exit Internal 'driverUp': '<S2>:49' */
        powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

        /* Exit 'driverUp': '<S2>:49' */
        move_up = false;
        powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverDown;

        /* Entry 'driverDown': '<S2>:41' */
        move_down = true;
        powerwindow_ec_DW.is_driverDown = powerwindow_ec_IN_DriverDown;
      } else if (endstop_top) {
        /* Transition: '<S2>:67' */
        /* Exit Internal 'driverUp': '<S2>:49' */
        powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

        /* Exit 'driverUp': '<S2>:49' */
        powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverNeutral;

        /* Entry 'driverNeutral': '<S2>:3' */
        /* Entry Internal 'driverNeutral': '<S2>:3' */
        /* Transition: '<S2>:23' */
        powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerneutral;

        /* Entry 'passengerneutral': '<S2>:4' */
        move_up = false;
        move_down = false;
      } else {
        switch (powerwindow_ec_DW.is_driverUp) {
         case powerwindow_ec_IN_DriverUp:
          /* During 'DriverUp': '<S2>:51' */
          if (driver_validated_neutral) {
            /* Transition: '<S2>:66' */
            powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_NO_ACTIVE_CHILD;

            /* Exit 'driverUp': '<S2>:49' */
            powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverNeutral;

            /* Entry 'driverNeutral': '<S2>:3' */
            /* Entry Internal 'driverNeutral': '<S2>:3' */
            /* Transition: '<S2>:23' */
            powerwindow_ec_DW.is_driverNeutral =
              powerwindow_ec_IN_passengerneutral;

            /* Entry 'passengerneutral': '<S2>:4' */
            move_up = false;
            move_down = false;
          }
          break;

         case powerwindow_ec_IN_autoDriverUp:
          /* During 'autoDriverUp': '<S2>:53' */
          break;

         default:
          /* Constant: '<S1>/Constant2' */
          /* During 'iniDriverUp': '<S2>:50' */
          if (powerwindow_ec_DW.temporalCounter_i1 >= auto_up_time) {
            /* Transition: '<S2>:56' */
            if (driver_validated_neutral) {
              /* Transition: '<S2>:57' */
              powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_autoDriverUp;
            } else {
              /* Transition: '<S2>:58' */
              powerwindow_ec_DW.is_driverUp = powerwindow_ec_IN_DriverUp;
            }
          }
          break;
        }
      }
      break;
    }
  }
}

/* Model step function */
void powerwindow_ec_step(void)
{
  /* UnitDelay: '<S1>/Unit Delay' */
  prev_move_up = powerwindow_ec_DW.UnitDelay_DSTATE;

  /* Outputs for Atomic SubSystem: '<S1>/detect_obstacle_endstop' */
  detect_obstacle_endstop();

  /* End of Outputs for SubSystem: '<S1>/detect_obstacle_endstop' */

  /* Outputs for Atomic SubSystem: '<S1>/validate_driver' */
  validate_driver();

  /* End of Outputs for SubSystem: '<S1>/validate_driver' */

  /* Outputs for Atomic SubSystem: '<S1>/validate_passenger' */
  validate_passenger();

  /* End of Outputs for SubSystem: '<S1>/validate_passenger' */

  /* Chart: '<S1>/control' incorporates:
   *  Constant: '<S1>/Constant'
   */
  /* Gateway: powerwindow_controller/control */
  if (powerwindow_ec_DW.temporalCounter_i1 < 255U) {
    powerwindow_ec_DW.temporalCounter_i1++;
  }

  /* During: powerwindow_controller/control */
  if (powerwindow_ec_DW.is_active_c1_powerwindow_ec == 0U) {
    /* Entry: powerwindow_controller/control */
    powerwindow_ec_DW.is_active_c1_powerwindow_ec = 1U;

    /* Entry Internal: powerwindow_controller/control */
    /* Transition: '<S2>:2' */
    powerwindow_ec_DW.is_c1_powerwindow_ec = powerwindow_ec_IN_safe;

    /* Entry Internal 'safe': '<S2>:1' */
    /* Transition: '<S2>:40' */
    powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverNeutral;

    /* Entry 'driverNeutral': '<S2>:3' */
    /* Entry Internal 'driverNeutral': '<S2>:3' */
    /* Transition: '<S2>:23' */
    powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerneutral;

    /* Entry 'passengerneutral': '<S2>:4' */
    move_up = false;
    move_down = false;
  } else if (powerwindow_ec_DW.is_c1_powerwindow_ec ==
             powerwindow_ec_IN_emergencyDown) {
    /* During 'emergencyDown': '<S2>:59' */
    if (endstop_bottom || (powerwindow_ec_DW.temporalCounter_i1 >=
                           emergency_down_time)) {
      /* Transition: '<S2>:61' */
      powerwindow_ec_DW.is_c1_powerwindow_ec = powerwindow_ec_IN_safe;
      powerwindow_ec_DW.is_safe = powerwindow_ec_IN_driverNeutral;

      /* Entry 'driverNeutral': '<S2>:3' */
      powerwindow_ec_DW.is_driverNeutral = powerwindow_ec_IN_passengerneutral;

      /* Entry 'passengerneutral': '<S2>:4' */
      move_up = false;
      move_down = false;
    }
  } else {
    powerwindow_ec_safe();
  }

  /* End of Chart: '<S1>/control' */

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  powerwindow_ec_DW.UnitDelay_DSTATE = move_up;
}

/* Model initialize function */
void powerwindow_ec_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
