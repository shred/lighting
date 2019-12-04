/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

// All dimensions are in millimeters!

// General case parameters
cornerRadius    = 2;        // Radius of the case edges and corners
wallSize        = 2.5;      // Thickness of the case walls

// Your PCB dimensions
pcbWidth        =  58;      // Width of your controller (X axis)
pcbDepth        =  80;      // Depth of your controller (Y axis)
pcbHeight       =  27;      // Height of your controller (Z axis),
                            //   from the very bottom to the top of the display,
                            //   but without the button caps.

// Padding (distance of PCB to case walls)
paddingXY       =  3;       // Padding at the X and Y axis
paddingZ        =  2;       // Padding at the Z axis

// Buttons
buttonY         = -pcbDepth/2 + 19.6; // Y position of the button caps' centers, relative to case center
buttonX         = 1.4;      // X position of the middle button, relative to case center
buttonDiameter  = 10.2;     // Diameter of the button caps
buttonDistance  = 12.7;     // Distance between center of left and middle button cap
rotaryDiameter  = 10.2;     // Diameter of the rotary encoder cap
rotaryDistance  = 12.7;     // Distance between center of middle button and rotary encoder cap

// LCD
lcdY            = -pcbDepth/2 + 43.5; // Y position of the LCD window's center, relative to case center
windowWidth     = 34.8;     // Width of the LCD window
windowHeight    = 14.1;     // Height of the LCD window
windowThickness = 0.8;      // Thickness of the case around the LCD window
lcdWidth        = 40;       // Total width of the LCD
lcdHeight       = 33;       // Total height of the LCD

// Mounts
pcbThickness    = 1.6;      // Thickness of the bottom PCB
mountDistanceX  = 39.0;     // X distance of the PCB mounting holes
mountOffsetY    = -2.0;     // Y offset of the PCB mounting holes (0 = at the PCB edge)
mountDiameter   = 6;        // Diameter of the mounting columns
mountLength     = 20;       // PCB mounting column length
mountHoleDiameter = 3;      // Screw hole diameter
mountHoleDepth  = 15;       // Screw hole depth
coverMountOffset = 1;       // Offset of cover mounting colums from the case corners
screwHeadDepth  = 1;        // Depth of the insets for the cover screw heads
screwHeadDiameter = 5;      // Diameter of the cover screw heads

// Wire Outlet
outletWidth     = 4.8;      // Width of the wire outlet
outletHeight    = 1.5;      // Height of the wire outlet

// Bottom cover wall
bottomWallSize  = 3;        // Cover's inside wall thickness
bottomWallHeight = 2;       // Cover's inside wall height
