/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

include <parameter.scad>

module roundedSemiBox(size, corner) {
    difference() {
        minkowski() {
            cube([
                size[0] - corner*2,
                size[1] - corner*2,
                (size[2] - corner*2) * 2
            ], center=true);
            sphere(corner);
        }
        translate([0, 0, -size[2]/2]) {
            cube([size[0] + 1, size[1] + 1, size[2]], center=true);
        }
    }
}

module box(innerSize, wall, corner=0) {
    difference() {
        if (corner == 0) {
            translate([0, 0, (innerSize[2] + wall)/2])
                cube([
                    innerSize[0] + wall*2,
                    innerSize[1] + wall*2,
                    innerSize[2] + wall
                ], center = true);
        } else {
            roundedSemiBox([
                innerSize[0] + wall*2,
                innerSize[1] + wall*2,
                innerSize[2] + wall
            ], corner);
        }

        translate([0, 0, innerSize[2]/2 - wall/2]) {
            cube(innerSize, center = true);
        }
    }
}

module buttonCutout(pos, diameter, wall) {
    translate([pos[0], pos[1], pos[2] - 0.5]) {
        cylinder(wall + 1, d=diameter, center=true);
    }
}

module lcdCutout(pos, window, inner, framewall, wall) {
    translate([pos[0], pos[1], pos[2] - 0.5]) {
        cube([window[0], window[1], wall + 1], center=true);
    }
    translate([pos[0], pos[1], pos[2] - wall/2 + framewall/2 - 0.01]) {
        cube([inner[0], inner[1], wall - framewall], center=true);
    }
}

module mountColumn(pos, diameter, length, offset) {
    translate([pos[0], pos[1], offset]) {
        difference() {
            cylinder(d=diameter, h=length+0.3);
            translate([0, 0, -0.1])
                cylinder(d=mountHoleDiameter, h=mountHoleDepth+0.1, $fn=5);
        }
    }
}

caseHeight = pcbHeight + paddingZ + windowThickness;

difference() {
    box([
        pcbWidth + paddingXY*2,
        pcbDepth + paddingXY*2,
        caseHeight
    ], wallSize, cornerRadius);

    translate([-(abs(buttonDistance - rotaryDistance))/2 + buttonX, 0, 0]) {
        buttonCutout([-buttonDistance, buttonY, caseHeight], buttonDiameter, wallSize);
        buttonCutout([0, buttonY, caseHeight], buttonDiameter, wallSize);
        buttonCutout([rotaryDistance, buttonY, caseHeight], rotaryDiameter, wallSize);
    }

    lcdCutout(
        [0, lcdY, caseHeight],
        [windowWidth, windowHeight],
        [lcdWidth, lcdHeight],
        windowThickness,
        wallSize
    );

    translate([0, (pcbDepth+paddingXY)/2 + wallSize, outletHeight/2-0.5]) {
        cube([outletWidth, wallSize + 1, outletHeight+0.5], center=true);
    }
}

caseInnerHeight = pcbHeight + paddingZ;

mountColumn([(mountDistanceX-mountDiameter)/2, (pcbDepth-mountDiameter+mountOffsetY)/2],
    mountDiameter, mountLength + 0.1, caseInnerHeight - mountLength);
mountColumn([-(mountDistanceX-mountDiameter)/2, (pcbDepth-mountDiameter+mountOffsetY)/2],
    mountDiameter, mountLength + 0.1, caseInnerHeight - mountLength);
mountColumn([(mountDistanceX-mountDiameter)/2, -(pcbDepth-mountDiameter+mountOffsetY)/2],
    mountDiameter, mountLength + 0.1, caseInnerHeight - mountLength);
mountColumn([-(mountDistanceX-mountDiameter)/2, -(pcbDepth-mountDiameter+mountOffsetY)/2],
    mountDiameter, mountLength + 0.1, caseInnerHeight - mountLength);

mountColumn([(pcbWidth+paddingXY-coverMountOffset)/2, (pcbDepth+paddingXY-coverMountOffset)/2],
    mountDiameter, caseInnerHeight+0.1, 0);
mountColumn([-(pcbWidth+paddingXY-coverMountOffset)/2, (pcbDepth+paddingXY-coverMountOffset)/2],
    mountDiameter, caseInnerHeight+0.1, 0);
mountColumn([(pcbWidth+paddingXY-coverMountOffset)/2, -(pcbDepth+paddingXY-coverMountOffset)/2],
    mountDiameter, caseInnerHeight+0.1, 0);
mountColumn([-(pcbWidth+paddingXY-coverMountOffset)/2, -(pcbDepth+paddingXY-coverMountOffset)/2],
    mountDiameter, caseInnerHeight+0.1, 0);

$fn=180;
