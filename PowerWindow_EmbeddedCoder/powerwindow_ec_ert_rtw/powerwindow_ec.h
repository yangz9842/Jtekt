/*
 * File: powerwindow_ec.h
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

#ifndef RTW_HEADER_powerwindow_ec_h_
#define RTW_HEADER_powerwindow_ec_h_
#ifndef powerwindow_ec_COMMON_INCLUDES_
#define powerwindow_ec_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* powerwindow_ec_COMMON_INCLUDES_ */

#include "powerwindow_ec_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define bFALSE                         false                     /* Referenced by: '<S6>/position_endstop_bottom' */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_c1_powerwindow_ec;        /* '<S1>/control' */
  uint8_T is_safe;                     /* '<S1>/control' */
  uint8_T is_driverNeutral;            /* '<S1>/control' */
  uint8_T is_passengerDown;            /* '<S1>/control' */
  uint8_T is_passengerUp;              /* '<S1>/control' */
  uint8_T is_driverUp;                 /* '<S1>/control' */
  uint8_T is_driverDown;               /* '<S1>/control' */
  uint8_T is_active_c1_powerwindow_ec; /* '<S1>/control' */
  uint8_T temporalCounter_i1;          /* '<S1>/control' */
  boolean_T u;                         /* '<S7>/ ' */
  boolean_T UnitDelay_DSTATE;          /* '<S1>/Unit Delay' */
} DW_powerwindow_ec_T;

/* Real-time Model Data Structure */
struct tag_RTM_powerwindow_ec_T {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW_powerwindow_ec_T powerwindow_ec_DW;

/* Model entry point functions */
extern void powerwindow_ec_initialize(void);
extern void powerwindow_ec_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: ExportToFile */
extern boolean_T driver_down;          /* '<Root>/driver_down' */
extern boolean_T driver_up;            /* '<Root>/driver_up' */
extern boolean_T driver_validated_down;/* '<S8>/Logical Operator' */
extern boolean_T driver_validated_neutral;/* '<S11>/default_neutral' */
extern boolean_T driver_validated_up;  /* '<S11>/up_after_down' */
extern boolean_T endstop_bottom;       /* '<S6>/endstop_bottom_disp' */
extern boolean_T endstop_top;          /* '<S6>/endstop_top_disp' */
extern boolean_T move_down;            /* '<S1>/control' */
extern boolean_T move_up;              /* '<S1>/control' */
extern boolean_T obstacle_detection;   /* '<S7>/detection_obstacle' */
extern uint16_T obstacle_position;     /* '<Root>/obstacle_position' */
extern boolean_T passenger_down;       /* '<Root>/passenger_down' */
extern boolean_T passenger_up;         /* '<Root>/passenger_up' */
extern boolean_T passenger_validated_down;/* '<S12>/allow_action' */
extern boolean_T passenger_validated_neutral;/* '<S14>/default_neutral' */
extern boolean_T passenger_validated_up;/* '<S14>/up_after_down' */
extern boolean_T prev_move_up;         /* '<S1>/Unit Delay' */
extern uint16_T window_position;       /* '<Root>/window_position' */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile uint8_T auto_down_time;/* Referenced by: '<S1>/Constant1' */
extern const volatile uint8_T auto_up_time;/* Referenced by: '<S1>/Constant2' */
extern const volatile uint8_T emergency_down_time;/* Referenced by: '<S1>/Constant' */
extern const volatile uint16_T position_endstop_top;/* Referenced by: '<S6>/Constant' */

/* Real-time Model object */
extern RT_MODEL_powerwindow_ec_T *const powerwindow_ec_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'powerwindow_ec'
 * '<S1>'   : 'powerwindow_ec/powerwindow_controller'
 * '<S2>'   : 'powerwindow_ec/powerwindow_controller/control'
 * '<S3>'   : 'powerwindow_ec/powerwindow_controller/detect_obstacle_endstop'
 * '<S4>'   : 'powerwindow_ec/powerwindow_controller/validate_driver'
 * '<S5>'   : 'powerwindow_ec/powerwindow_controller/validate_passenger'
 * '<S6>'   : 'powerwindow_ec/powerwindow_controller/detect_obstacle_endstop/detect_endstop'
 * '<S7>'   : 'powerwindow_ec/powerwindow_controller/detect_obstacle_endstop/detect_obstacle'
 * '<S8>'   : 'powerwindow_ec/powerwindow_controller/validate_driver/check_down'
 * '<S9>'   : 'powerwindow_ec/powerwindow_controller/validate_driver/check_up'
 * '<S10>'  : 'powerwindow_ec/powerwindow_controller/validate_driver/driver_switch'
 * '<S11>'  : 'powerwindow_ec/powerwindow_controller/validate_driver/mutually_exclusive'
 * '<S12>'  : 'powerwindow_ec/powerwindow_controller/validate_passenger/check_down'
 * '<S13>'  : 'powerwindow_ec/powerwindow_controller/validate_passenger/check_up'
 * '<S14>'  : 'powerwindow_ec/powerwindow_controller/validate_passenger/mutually_exclusive'
 * '<S15>'  : 'powerwindow_ec/powerwindow_controller/validate_passenger/passenger_switch'
 */
#endif                                 /* RTW_HEADER_powerwindow_ec_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
