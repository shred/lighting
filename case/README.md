In this directory, you will find the [OpenSCAD](https://www.openscad.org) files of a case for the lighting controller.

The `parameter.scad` file contains a lot of parameters that you can adjust to your needs. Each parameter is commented, and you should also see the effect when changing it and looking at the result in OpenSCAD's preview.

`case.scad` contains the construction of the case itself. Rotate it by 180° along the Y axis before printing it, so the top of the case is printed on the heatbed. No supports are needed.

`cover.scad` contains the bottom cover of the case. I recommend to use supports for the screw holes. The printed part should just snap into the case, so there is no actual need for screws though.

I have used PETG and 15% infill for printing, with good results. PLA should work as well.
