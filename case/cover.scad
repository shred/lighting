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

module roundedBottomSemiBox(size, corner) {
    difference() {
        minkowski() {
            cube([
                size[0] - corner*2,
                size[1] - corner*2,
                (size[2] - corner) * 2
            ], center=true);
            sphere(corner);
        }
        translate([0, 0, size[2]/2]) {
            cube([size[0] + 1, size[1] + 1, size[2]], center=true);
        }
    }
}

module screwhole(pos, diameter, length, headDiam, headDepth) {
    translate([pos[0], pos[1], -length]) {
        cylinder(d=diameter, h=length+0.1);
        cylinder(d=headDiam, h=headDepth);
    }
}

difference() {
    roundedBottomSemiBox([
        pcbWidth + paddingXY*2 + wallSize*2,
        pcbDepth + paddingXY*2 + wallSize*2,
        wallSize
    ], cornerRadius);

    screwhole([(pcbWidth+paddingXY-coverMountOffset)/2, (pcbDepth+paddingXY-coverMountOffset)/2],
        mountHoleDiameter, wallSize, screwHeadDiameter, screwHeadDepth);
    screwhole([-(pcbWidth+paddingXY-coverMountOffset)/2, (pcbDepth+paddingXY-coverMountOffset)/2],
        mountHoleDiameter, wallSize, screwHeadDiameter, screwHeadDepth);
    screwhole([(pcbWidth+paddingXY-coverMountOffset)/2, -(pcbDepth+paddingXY-coverMountOffset)/2],
        mountHoleDiameter, wallSize, screwHeadDiameter, screwHeadDepth);
    screwhole([-(pcbWidth+paddingXY-coverMountOffset)/2, -(pcbDepth+paddingXY-coverMountOffset)/2],
        mountHoleDiameter, wallSize, screwHeadDiameter, screwHeadDepth);
}

difference() {
    translate([0, 0, bottomWallHeight/2]) {
        cube([pcbWidth + paddingXY*2, pcbDepth + paddingXY*2, bottomWallHeight], center = true);
    }
    translate([0, 0, bottomWallHeight/2]) {
        cube([pcbWidth + paddingXY*2 - bottomWallSize, pcbDepth + paddingXY*2 - bottomWallSize, bottomWallHeight + 0.1], center = true);
    }

    translate([(pcbWidth+paddingXY-coverMountOffset)/2, (pcbDepth+paddingXY-coverMountOffset)/2, 0])
        cylinder(d=mountDiameter+0.2, h=bottomWallHeight);
    translate([-(pcbWidth+paddingXY-coverMountOffset)/2, (pcbDepth+paddingXY-coverMountOffset)/2, 0])
        cylinder(d=mountDiameter+0.2, h=bottomWallHeight);
    translate([(pcbWidth+paddingXY-coverMountOffset)/2, -(pcbDepth+paddingXY-coverMountOffset)/2, 0])
        cylinder(d=mountDiameter+0.2, h=bottomWallHeight);
    translate([-(pcbWidth+paddingXY-coverMountOffset)/2, -(pcbDepth+paddingXY-coverMountOffset)/2, 0])
        cylinder(d=mountDiameter+0.2, h=bottomWallHeight);

    translate([0, (pcbDepth+paddingXY)/2, bottomWallHeight/2]) {
        cube([outletWidth + 1, bottomWallSize + 1, bottomWallHeight+0.5], center=true);
    }
}

$fn=180;
