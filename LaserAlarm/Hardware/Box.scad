include <arduino/arduino.scad>

module roundedCase(dimensions, wallThickness=3, mountingHoleDepth = 10, mountingHoleR = 1.25) {
    outherDimensions = [dimensions[0] + wallThickness * 4, dimensions[1] + wallThickness * 4, dimensions[2] + wallThickness];
    boardBase = [wallThickness * 2, wallThickness * 2, wallThickness];

  difference() {
    // case
    roundedCube(dimensions = outherDimensions, cornerRadius = wallThickness);
    translate([wallThickness * 2, wallThickness, wallThickness]) cube(size=[dimensions[0], dimensions[1] + wallThickness * 2, dimensions[2] + 1], center=false);
    translate([wallThickness, wallThickness * 2, wallThickness]) cube(size=[dimensions[0] + wallThickness * 2, dimensions[1], dimensions[2] + 1], center=false);
    // lid mounting holes
    translate([wallThickness, wallThickness, outherDimensions[2] - mountingHoleDepth]) cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    translate([wallThickness, dimensions[1] + wallThickness * 3, outherDimensions[2] - mountingHoleDepth]) cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    translate([dimensions[0] + wallThickness * 3, wallThickness, outherDimensions[2] - mountingHoleDepth]) cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    translate([dimensions[0] + wallThickness * 3, dimensions[1] + wallThickness * 3, outherDimensions[2] - mountingHoleDepth]) cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    // USB and power jack holes
    translate(boardBase) components(boardType = UNO, component = USB, extension = wallThickness * 2 + 1);
    translate(boardBase) components(boardType = UNO, component = POWER, extension = wallThickness * 2 + 1);
  }
  // pillars
  translate(boardBase) standoffs(boardType=UNO, height=height, bottomRadius=1.5, topRadius=1.5, holeRadius=0.75);
}


module roundedCover(dimensions, wallThickness=3, mountingHoleR = 1.25) {
  outherDimensions = [dimensions[0] + wallThickness * 4, dimensions[1] + wallThickness * 4, wallThickness];
  boardBase = [wallThickness * 2, wallThickness * 2, pcbHeight - dimensions[2]];
  mountingHoleDepth = wallThickness+2;

  difference() {
    // cover
    roundedCube(dimensions = outherDimensions, cornerRadius = wallThickness);
    // mounting holes
    translate([wallThickness, wallThickness, outherDimensions[2] - mountingHoleDepth]) 
      cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    translate([wallThickness, dimensions[1] + wallThickness * 3, outherDimensions[2] - mountingHoleDepth]) 
      cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    translate([dimensions[0] + wallThickness * 3, wallThickness, outherDimensions[2] - mountingHoleDepth]) 
      cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
    translate([dimensions[0] + wallThickness * 3, dimensions[1] + wallThickness * 3, outherDimensions[2] - mountingHoleDepth]) 
      cylinder(r = mountingHoleR, $fn = 32, h = mountingHoleDepth + 1);
  }
}

module cylindersCircle(pathRadius, num, r, h) {
  for (i=[1:num])  {
      translate([pathRadius*cos(i*(360/num)),pathRadius*sin(i*(360/num)),0]) cylinder(r=r, h=h, $fn=20);
  }  
}


width=53.3;
depth=100;
height=20;
wallThickness=3;

// case
translate([-wallThickness * 2, -wallThickness * 2, -wallThickness]) roundedCase(dimensions = [width, depth, height], wallThickness = wallThickness);

// cover
!translate([-wallThickness * 2, -wallThickness * 2, height]) difference() {
  roundedCover(dimensions = [width, depth, height], wallThickness = wallThickness);
  // button
  translate([28-7/2, 55-7/2, -1]) 
    cylinder(d=8, h=wallThickness+2);
  // 3 LEDs
  translate([38-22, 69-5/2, -1]) 
    roundedCube(dimensions = [23, 6, wallThickness+2], cornerRadius = 3);
  // 2 alarm LEDs
  translate([10, 90, -1])
    cylinder(d=5, h=wallThickness+2);
  translate([width  + wallThickness * 4 - 10, 90, -1])
    cylinder(d=5, h=wallThickness+2);
  // speaker
  translate([width /2  + wallThickness * 2, 85 + wallThickness * 2, -1]) {
    cylindersCircle(pathRadius = 12.5, num = 8, r = 0.5, h = wallThickness + 2);
    cylindersCircle(pathRadius = 7.5, num = 8, r = 0.5, h = wallThickness + 2);
    cylindersCircle(pathRadius = 2.5, num = 4, r = 0.5, h = wallThickness + 2);
  }
}


// sample arduino
%arduino();

// sample speaker
%translate([width / 2, 85, height]) rotate([0,180,0]) union() {
    color("DarkGray") {        
        cylinder(h=4, d = 30);
        translate([0,0,4]) cylinder(h=4, d = 15);
    }
}

