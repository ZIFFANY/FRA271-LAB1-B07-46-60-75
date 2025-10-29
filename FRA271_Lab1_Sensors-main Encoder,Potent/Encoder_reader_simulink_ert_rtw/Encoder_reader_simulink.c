/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Encoder_reader_simulink.c
 *
 * Code generated for Simulink model 'Encoder_reader_simulink'.
 *
 * Model version                  : 2.20
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Tue Oct 14 16:36:32 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Encoder_reader_simulink.h"
#include "Encoder_reader_simulink_types.h"
#include "rtwtypes.h"
#include "stm_timer_ll.h"
#include "Encoder_reader_simulink_private.h"

/* Block signals (default storage) */
B_Encoder_reader_simulink_T Encoder_reader_simulink_B;

/* Block states (default storage) */
DW_Encoder_reader_simulink_T Encoder_reader_simulink_DW;

/* Real-time model */
static RT_MODEL_Encoder_reader_simul_T Encoder_reader_simulink_M_;
RT_MODEL_Encoder_reader_simul_T *const Encoder_reader_simulink_M =
  &Encoder_reader_simulink_M_;

/* Forward declaration for local functions */
static void Encoder_reader_SystemCore_setup(stm32cube_blocks_EncoderBlock_T *obj);
static void Encoder_reader_SystemCore_setup(stm32cube_blocks_EncoderBlock_T *obj)
{
  uint8_T ChannelInfo;
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  obj->isInitialized = 1;
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  ChannelInfo = ENABLE_CH;

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  enableTimerChannel1(obj->TimerHandle, ChannelInfo);
  enableTimerChannel2(obj->TimerHandle, ChannelInfo);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
    enableCounter(obj->TimerHandle, false);
  }

  obj->isSetupComplete = true;
}

/* Model step function */
void Encoder_reader_simulink_step(void)
{
  {
    real_T delta;
    real_T lastTime;
    real_T *lastU;
    uint32_T pinReadLoc;

    /* MATLABSystem: '<Root>/TIM3_Encoder' */
    Encoder_reader_simulink_B.TIM3_Encoder = getTimerCounterValueForG4
      (Encoder_reader_simulink_DW.obj_h.TimerHandle, false, NULL);

    /* MATLABSystem: '<S4>/Digital Port Read' */
    pinReadLoc = LL_GPIO_ReadInputPort(GPIOC);

    /* MATLAB Function: '<Root>/Relative Position (Pulse)' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion2'
     *  MATLABSystem: '<S4>/Digital Port Read'
     * */
    if (!Encoder_reader_simulink_DW.round_not_empty) {
      Encoder_reader_simulink_DW.round_not_empty = true;
      Encoder_reader_simulink_DW.last_u = Encoder_reader_simulink_B.TIM3_Encoder;
    }

    delta = (real_T)Encoder_reader_simulink_B.TIM3_Encoder -
      Encoder_reader_simulink_DW.last_u;
    if (delta < -32768.0) {
      Encoder_reader_simulink_DW.round_c++;
    } else if (delta > 32768.0) {
      Encoder_reader_simulink_DW.round_c--;
    }

    delta = Encoder_reader_simulink_DW.round_c * 65536.0 + (real_T)
      Encoder_reader_simulink_B.TIM3_Encoder;
    Encoder_reader_simulink_DW.last_u = Encoder_reader_simulink_B.TIM3_Encoder;
    if (((pinReadLoc & 8192U) != 0U) && (!Encoder_reader_simulink_DW.isHomed)) {
      Encoder_reader_simulink_DW.offset = delta;
      Encoder_reader_simulink_DW.isHomed = true;
    }

    Encoder_reader_simulink_B.y = delta - Encoder_reader_simulink_DW.offset;

    /* End of MATLAB Function: '<Root>/Relative Position (Pulse)' */
    /* Gain: '<Root>/degree' */
    Encoder_reader_simulink_B.degraaradian = 0.00076699039394282058 *
      Encoder_reader_simulink_B.y;

    /* Gain: '<Root>/rad' */
    Encoder_reader_simulink_B.degree = 0.0439453125 *
      Encoder_reader_simulink_B.y;

    /* Derivative: '<Root>/diff n' */
    delta = Encoder_reader_simulink_M->Timing.t[0];
    if ((Encoder_reader_simulink_DW.TimeStampA >= delta) &&
        (Encoder_reader_simulink_DW.TimeStampB >= delta)) {
      delta = 0.0;
    } else {
      lastTime = Encoder_reader_simulink_DW.TimeStampA;
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
      if (Encoder_reader_simulink_DW.TimeStampA <
          Encoder_reader_simulink_DW.TimeStampB) {
        if (Encoder_reader_simulink_DW.TimeStampB < delta) {
          lastTime = Encoder_reader_simulink_DW.TimeStampB;
          lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
        }
      } else if (Encoder_reader_simulink_DW.TimeStampA >= delta) {
        lastTime = Encoder_reader_simulink_DW.TimeStampB;
        lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
      }

      delta = (Encoder_reader_simulink_B.y - *lastU) / (delta - lastTime);
    }

    /* End of Derivative: '<Root>/diff n' */

    /* Gain: '<Root>/resolution2' */
    Encoder_reader_simulink_B.omega = 0.00076699039394282058 * delta;
  }

  {
    real_T *lastU;

    /* Update for Derivative: '<Root>/diff n' */
    if (Encoder_reader_simulink_DW.TimeStampA == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampA =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
    } else if (Encoder_reader_simulink_DW.TimeStampB == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampB =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
    } else if (Encoder_reader_simulink_DW.TimeStampA <
               Encoder_reader_simulink_DW.TimeStampB) {
      Encoder_reader_simulink_DW.TimeStampA =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
    } else {
      Encoder_reader_simulink_DW.TimeStampB =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
    }

    *lastU = Encoder_reader_simulink_B.y;

    /* End of Update for Derivative: '<Root>/diff n' */
  }

  {                                    /* Sample time: [0.01s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      ((Encoder_reader_simulink_M->Timing.clockTick1) * 0.01);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1, extmodeTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  Encoder_reader_simulink_M->Timing.t[0] =
    ((time_T)(++Encoder_reader_simulink_M->Timing.clockTick0)) *
    Encoder_reader_simulink_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    Encoder_reader_simulink_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void Encoder_reader_simulink_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Encoder_reader_simulink_M->solverInfo,
                          &Encoder_reader_simulink_M->Timing.simTimeStep);
    rtsiSetTPtr(&Encoder_reader_simulink_M->solverInfo, &rtmGetTPtr
                (Encoder_reader_simulink_M));
    rtsiSetStepSizePtr(&Encoder_reader_simulink_M->solverInfo,
                       &Encoder_reader_simulink_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Encoder_reader_simulink_M->solverInfo,
                          (&rtmGetErrorStatus(Encoder_reader_simulink_M)));
    rtsiSetRTModelPtr(&Encoder_reader_simulink_M->solverInfo,
                      Encoder_reader_simulink_M);
  }

  rtsiSetSimTimeStep(&Encoder_reader_simulink_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Encoder_reader_simulink_M->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&Encoder_reader_simulink_M->solverInfo, false);
  rtsiSetSolverName(&Encoder_reader_simulink_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Encoder_reader_simulink_M,
             &Encoder_reader_simulink_M->Timing.tArray[0]);
  rtmSetTFinal(Encoder_reader_simulink_M, -1);
  Encoder_reader_simulink_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  Encoder_reader_simulink_M->Sizes.checksums[0] = (123287188U);
  Encoder_reader_simulink_M->Sizes.checksums[1] = (2678328737U);
  Encoder_reader_simulink_M->Sizes.checksums[2] = (2644644735U);
  Encoder_reader_simulink_M->Sizes.checksums[3] = (329728238U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    Encoder_reader_simulink_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Encoder_reader_simulink_M->extModeInfo,
      &Encoder_reader_simulink_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Encoder_reader_simulink_M->extModeInfo,
                        Encoder_reader_simulink_M->Sizes.checksums);
    rteiSetTPtr(Encoder_reader_simulink_M->extModeInfo, rtmGetTPtr
                (Encoder_reader_simulink_M));
  }

  /* InitializeConditions for Derivative: '<Root>/diff n' */
  Encoder_reader_simulink_DW.TimeStampA = (rtInf);
  Encoder_reader_simulink_DW.TimeStampB = (rtInf);

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  Encoder_reader_simulink_DW.obj_h.isInitialized = 0;
  Encoder_reader_simulink_DW.obj_h.matlabCodegenIsDeleted = false;
  Encoder_reader_SystemCore_setup(&Encoder_reader_simulink_DW.obj_h);

  /* Start for MATLABSystem: '<S4>/Digital Port Read' */
  Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted = false;
  Encoder_reader_simulink_DW.obj.isInitialized = 1;
  Encoder_reader_simulink_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void Encoder_reader_simulink_terminate(void)
{
  uint8_T ChannelInfo;

  /* Terminate for MATLABSystem: '<Root>/TIM3_Encoder' */
  if (!Encoder_reader_simulink_DW.obj_h.matlabCodegenIsDeleted) {
    Encoder_reader_simulink_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((Encoder_reader_simulink_DW.obj_h.isInitialized == 1) &&
        Encoder_reader_simulink_DW.obj_h.isSetupComplete) {
      disableCounter(Encoder_reader_simulink_DW.obj_h.TimerHandle);
      disableTimerInterrupts(Encoder_reader_simulink_DW.obj_h.TimerHandle, 0);
      ChannelInfo = ENABLE_CH;
      disableTimerChannel1(Encoder_reader_simulink_DW.obj_h.TimerHandle,
                           ChannelInfo);
      disableTimerChannel2(Encoder_reader_simulink_DW.obj_h.TimerHandle,
                           ChannelInfo);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/TIM3_Encoder' */

  /* Terminate for MATLABSystem: '<S4>/Digital Port Read' */
  if (!Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted) {
    Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/Digital Port Read' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
