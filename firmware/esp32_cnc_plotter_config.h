#pragma once

#define MACHINE_NAME "ESP32 CNC Plotter"

#ifdef USE_RMT_STEPS
#    undef USE_RMT_STEPS
#endif

// ======================
// X AXIS - 28BYJ-48
// ======================

#define X_UNIPOLAR

#define X_PIN_PHASE_0 GPIO_NUM_26
#define X_PIN_PHASE_1 GPIO_NUM_25
#define X_PIN_PHASE_2 GPIO_NUM_33
#define X_PIN_PHASE_3 GPIO_NUM_32

// ======================
// Y AXIS - 28BYJ-48
// ======================

#define Y_UNIPOLAR

#define Y_PIN_PHASE_0 GPIO_NUM_19
#define Y_PIN_PHASE_1 GPIO_NUM_16
#define Y_PIN_PHASE_2 GPIO_NUM_17
#define Y_PIN_PHASE_3 GPIO_NUM_18

// ======================
// Z AXIS - 28BYJ-48
// ======================

#define Z_UNIPOLAR

#define Z_PIN_PHASE_0 GPIO_NUM_14
#define Z_PIN_PHASE_1 GPIO_NUM_27
#define Z_PIN_PHASE_2 GPIO_NUM_13
#define Z_PIN_PHASE_3 GPIO_NUM_23