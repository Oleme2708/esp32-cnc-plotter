# ✏️ ESP32 CNC Plotter

![PlatformIO](https://img.shields.io/badge/PlatformIO-FF6F00?style=for-the-badge&logo=platformio&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Language](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge)
![G-code](https://img.shields.io/badge/G--code-CNC-green?style=for-the-badge)

A fully 3D-printed three-axis CNC drawing machine controlled by an ESP32.  
The machine receives G-code from **Universal Gcode Sender (UGS)** and uses **Grbl_ESP32** to control three 28BYJ-48 unipolar stepper motors through ULN2003 driver boards.

# Note

This project was developed using **PlatformIO in Visual Studio Code**.

The mechanical structure is based on the **Simple Arduino CNC Plotter** design by **DonTheMaker**.  
The original design uses a fully 3D-printed mechanical structure together with stepper motors and a small number of fasteners.

For my build, I replaced the original controller setup with an **ESP32**, configured **Grbl_ESP32** for three unipolar stepper motors, and used **Universal Gcode Sender** to manually control the axes and run G-code file.

I also designed two additional washer parts because the screws available to me did not fit the original assembly as required.

> CAD source link: https://makerworld.com/en/models/2889145-simple-arduino-cnc-plotter?from=search#profileId-3227843

# Demo

Demo photo and video will be added after final testing.

<!--
Add final image here:

![ESP32 CNC Plotter](media/cnc_plotter.jpg)
-->

<!--
Add demo video here:

[Watch demo video](YOUR_VIDEO_LINK)
-->

# Project overview

This project is a small three-axis CNC pen plotter built around an ESP32 and three 28BYJ-48 5V stepper motors.

The machine is controlled through the following system:

```text
G-code file
     |
     v
Universal Gcode Sender (UGS)
     |
     | USB / Serial
     v
ESP32 + Grbl_ESP32
     |
     v
ULN2003 motor drivers
     |
     v
28BYJ-48 stepper motors
     |
     v
X / Y / Z mechanical movement
     |
     v
Pen drawing on paper
```

UGS is used to:

+ Calibration and setup
+ Jog the X, Y and Z axes manually
+ Send individual G-code commands
+ Preview G-code paths
+ Load complete G-code files
+ Start and monitor drawing jobs


The X and Y axes control the pen position on the paper, while the Z axis lifts and lowers the pen.

The current usable drawing area is approximately:

```text
125 mm × 125 mm
```

# Features

+ Fully 3D-printed CNC plotter structure
+ Three-axis motion control
+ ESP32-based controller
+ Three 28BYJ-48 unipolar stepper motors
+ Three ULN2003 motor drivers
+ Custom Grbl_ESP32 machine configuration
+ G-code control using Universal Gcode Sender
+ Manual X/Y/Z jogging through UGS
+ G-code preview and job execution
+ PlatformIO development

# Hardware

+ ESP32 development board
+ 3 × 28BYJ-48 5V stepper motors
+ 3 × ULN2003 stepper motor driver boards
+ External regulated 5V power supply
+ Fully 3D-printed CNC plotter structure
+ Pen / marker
+ Jumper wires
+ USB cable
+ Small number of M4 screws / fasteners used in the mechanical assembly
+ 2 × custom 3D-printed washers added for my build


# Software

+ Visual Studio Code
+ PlatformIO
+ Universal Gcode Sender (UGS)
+ Grbl_ESP32

## Universal Gcode Sender

UGS is the main interface used to control this CNC plotter from the computer.

Official website:

https://winder.github.io/ugs_website/

UGS is used for manual jogging, sending G-code commands, previewing tool paths, and running complete G-code jobs.

## Grbl_ESP32

This project uses the open-source Grbl_ESP32 firmware by Bart Dring and contributors.

Firmware source:

https://github.com/bdring/Grbl_Esp32

The complete Grbl_ESP32 firmware is not copied into this repository.  
Only the custom configuration used for this machine is included.

# Firmware configuration

The custom machine configuration can be found in:

```text
firmware/esp32_cnc_plotter_config.h
```

The configuration enables unipolar motor control and assigns four ESP32 GPIO pins to each motor.


# ESP32 pin configuration

## X axis

| Motor phase | ESP32 GPIO |
|---|---:|
| Phase 0 | GPIO 26 |
| Phase 1 | GPIO 25 |
| Phase 2 | GPIO 33 |
| Phase 3 | GPIO 32 |

## Y axis

| Motor phase | ESP32 GPIO |
|---|---:|
| Phase 0 | GPIO 19 |
| Phase 1 | GPIO 16 |
| Phase 2 | GPIO 17 |
| Phase 3 | GPIO 18 |

## Z axis

| Motor phase | ESP32 GPIO |
|---|---:|
| Phase 0 | GPIO 14 |
| Phase 1 | GPIO 27 |
| Phase 2 | GPIO 13 |
| Phase 3 | GPIO 23 |

# Axis direction

The physical orientation of the current machine is:

```text
                 X- (up)
                    ↑
                    |
Y- (left)  ←--------+--------→  Y+ (right)
                    |
                    ↓
                 X+ (down)
```

Therefore:

+ `X+` = move down
+ `X-` = move up
+ `Y+` = move right
+ `Y-` = move left

The Z axis controls pen up / pen down movement.

Because of the physical layout:

```text
Paper vertical direction   = Machine X axis
Paper horizontal direction = Machine Y axis
```

This orientation has to be considered when generating G-code.

# Power

The three stepper motors are powered using an external regulated 5V supply.

The ESP32 and all ULN2003 motor drivers share a common ground.

```text
External 5V +  ----> ULN2003 VCC

External GND   ----> ULN2003 GND
                        |
ESP32 GND -------------+
```

The stepper motors are not powered directly from an ESP32 GPIO pin.

# G-code

The machine receives G-code from UGS through the ESP32 serial connection.

Some basic commands used in this project are:

```gcode
G21
G90
G91
```

Where:

```text
G21 = millimetres
G90 = absolute positioning
G91 = relative positioning
```

Example relative movement:

```gcode
G91

G1 X10 F150
G1 X-10 F150

G1 Y10 F150
G1 Y-10 F150
```

With the current machine orientation:

```text
X10  = move 10 mm down
X-10 = move 10 mm up

Y10  = move 10 mm right
Y-10 = move 10 mm left
```

The final drawing tests mainly use `G91` relative positioning because it is easier to start a drawing from a manually selected position without relying on a fixed machine origin.

Custom G-code files are stored in:

```text
gcode/
```

# Pen control

The Z axis lifts and lowers the pen.

Example:

```gcode
G91

G1 Z-1 F20
G1 Y30 F200
G1 Z1 F20
```

Only a small Z movement is required.

The exact pen-up and pen-down distance depends on the mechanical adjustment of the pen holder.

# Calibration

The main Grbl axis calibration settings are:

```text
$100 = X-axis steps/mm
$101 = Y-axis steps/mm
$102 = Z-axis steps/mm
```

The X axis has been tested at approximately:

```text
$100 = 100 steps/mm
```

The calibration method used is:

run G1 X50 F100 to draw a line
measure the line to check the accuracy. The line should be 5cm, changing the value of $100 if different value are drew. repeat for other axis



# Speed testing

The 28BYJ-48 is a small geared stepper motor, so the maximum reliable speed is limited.

Feed rate was increased gradually during testing:

```text
F100
F150
F200
F250
F300
```

If a motor begins to:

+ vibrate without moving,
+ lose steps,
+ make abnormal sounds,
+ or fail to return to the original position,

the feed rate should be reduced.

# How to Use

## 1. Set up Grbl_ESP32

Clone or download Grbl_ESP32:

https://github.com/bdring/Grbl_Esp32

Copy:

```text
firmware/esp32_cnc_plotter_config.h
```

into:

```text
Grbl_Esp32/src/Machines/
```

Configure the build to use:

```text
-DMACHINE_FILENAME=esp32_cnc_plotter_config.h
```

Then build and upload the firmware to the ESP32 using PlatformIO.

## 2. Connect the machine to UGS

Download / install Universal Gcode Sender:

https://winder.github.io/ugs_website/

Then:

+ Connect the ESP32 to the computer using USB
+ Open UGS
+ Select the correct serial port
+ Set the baud rate to `115200`
+ Connect using GRBL mode

The PlatformIO Serial Monitor must be closed before connecting through UGS because only one application can use the serial port at a time.

## 3. Test the axes

Use the UGS Jog Controller to test:

+ X+
+ X-
+ Y+
+ Y-
+ Z+
+ Z-

Start with a small movement such as 1 mm or 10 mm.

## 4. Run a drawing

+ Move the pen to a safe starting position
+ Make sure enough X/Y travel is available
+ Make sure the pen starts raised
+ Load the `.gcode` file into UGS
+ Check the preview
+ Run a dry test if necessary
+ Start the job

# CAD

The main mechanical structure is based on:

**Simple Arduino CNC Plotter — DonTheMaker**

Platform:

**MakerWorld / Bambu Studio Online Models**

> TODO: paste the exact MakerWorld model URL here.

The plotter is designed so that almost the complete mechanical structure can be produced using a 3D printer.

My build uses the original printed mechanism as the base, but the electronics, controller, firmware configuration, wiring, calibration, G-code workflow, and troubleshooting were completed separately for the ESP32 version.

## Additional CAD parts

I designed two simple washer parts for this build because the screws available to me did not fit the original assembly correctly.

Files:

```text
CAD/Washer_1.5mm.STL
CAD/Washer_2mm.STL
```

These washers were used as simple spacing / fitting adjustments during assembly.

The original plotter model is stored in:

```text
CAD/Simple_CNC_Plotter.3mf
```

# What I learned

+ How basic CNC motion control works
+ How G-code controls physical machine movement
+ How to use Universal Gcode Sender to manually control a CNC machine
+ How to preview and execute G-code jobs using UGS
+ How to configure Grbl_ESP32 for a custom machine
+ How to use Grbl_ESP32 with 28BYJ-48 unipolar motors
+ How motor phase order affects direction and movement
+ How to assign ESP32 GPIO pins to three motor axes
+ How to build and upload ESP32 firmware using PlatformIO
+ How to communicate with a CNC controller through serial
+ How to calibrate motion using steps/mm
+ How to test feed rates and detect step loss
+ How to troubleshoot motor-driver and wiring problems
+ How mechanical alignment affects drawing accuracy
+ How to simplify G-code for more reliable motion
+ How to adapt an existing mechanical design to different electronics and available hardware

# Errors and lesson learned

+ **Motor appeared not to move:** the feed rate was too low, so the motor was moving extremely slowly rather than being completely stopped.

+ **Y axis did not move:** the ULN2003 driver board power connection was disconnected. Checking the driver power fixed the issue.

+ **Z axis vibrated instead of moving:** faulty jumper wires caused unreliable motor phase signals. Replacing the wires restored normal movement.

+ **Motor moved correctly in one direction but vibrated in reverse:** one motor phase connection was unreliable.

+ **Axis direction was incorrect:** with the 28BYJ-48 unipolar motors, the motor phase order and physical wiring directly affect direction.

+ **Drawing orientation was incorrect:** the physical X axis of this machine is vertical while the Y axis is horizontal. The G-code generation logic had to be changed to match the actual machine.

+ **Absolute G-code was harder to manage during testing:** incorrect start positions could cause the machine to travel farther than expected. Relative `G91` paths made the final demo easier to control.

+ **Complex automatically generated G-code was difficult to debug:** some generated files contained thousands of small movements. Simpler centre-line drawings using mainly `G0` and `G1` commands were easier to test.

+ **Arc commands caused errors during some tests:** line-based paths were used where possible for a more reliable demo.

+ **The frame can move while drawing:** because the structure is lightweight and mostly 3D printed, the machine can slide during axis movement if it is not fixed to the table.

+ **Pen contact is not always consistent:** the current pen holder has limited vertical compliance, so pen pressure can change across the drawing area.

# Current limitations

+ No limit switches
+ No automatic homing
+ Open-loop stepper control with no position feedback
+ Lightweight 3D-printed frame can move during operation
+ Pen pressure can vary with mechanical alignment
+ Drawing speed is limited by the 28BYJ-48 geared stepper motors

# Future improvements

+ Add a spring-loaded or floating pen holder
+ Fix the machine to a more rigid base
+ Add limit switches
+ Add automatic homing
+ Improve cable management
+ Improve mechanical rigidity
+ Perform more accurate X/Y calibration
+ Optimise G-code paths
+ Test higher reliable feed rates
+ Consider migrating from Grbl_ESP32 to FluidNC in a future version

# Credits

## Mechanical design

**Simple Arduino CNC Plotter**  
Designer: **DonTheMaker**  
Platform: **MakerWorld**

> TODO: add the exact original model link before the final portfolio version.

## Grbl_ESP32

This project uses the open-source **Grbl_ESP32** firmware by Bart Dring and contributors:

https://github.com/bdring/Grbl_Esp32

## Universal Gcode Sender

The machine is controlled using **Universal Gcode Sender**:

https://winder.github.io/ugs_website/

## Grbl

Grbl_ESP32 is based on the original Grbl CNC firmware by Sungeun K. Jeon and contributors:

https://github.com/grbl/grbl
