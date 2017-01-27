// Flipdot Display 
// Bottomplate of 3D Printed Casing
// RasperryPi B + Voltage Regulator Board
// CC4.0-BY SA NC   surasto.de

difference() {
  union() {
    cube(size=[190,74,2.5]);
    translate([2.1,2.1,2.4]) cube(size=[190-4.2,74-4.2,8]);
  }
  translate([4,4,2.5]) cube(size=[190-8,74-8,10]);
}

translate([190-6,74-22,2.4]) cube(size=[6,14,8]);

translate([0,27,2.4]) cube(size=[4,15,8]);
translate([0,49,2.4]) cube(size=[4,16,8]);


//Bolzen für Raspi 1
translate([11,24,2]) 
  difference() {
    cylinder(h=6, r=5, $fn=50);
    translate([0,0,0.1]) cylinder(h=6.5, r=1, $fn=50);
}

translate([11+55,24+25,2]) 
  difference() {
    cylinder(h=6, r=5, $fn=50);
    translate([0,0,0.1]) cylinder(h=6.5, r=1, $fn=50);
}

//Bolzen für Spannungsregler-Platine
translate([190-9,4+4,2]) 
  difference() {
    cylinder(h=6, r=4, $fn=50);
    translate([0,0,0.1]) cylinder(h=6.5, r=1, $fn=50);
}

translate([190-9-56,4+4,2]) 
  difference() {
    cylinder(h=6, r=5, $fn=20);
    translate([0,0,0.1]) cylinder(h=6.5, r=1, $fn=50);
}

translate([190-9,8+36,2]) 
  difference() {
    cylinder(h=6, r=4, $fn=20);
    translate([0,0,0.1]) cylinder(h=6.5, r=1, $fn=50);
}

translate([190-9-56,4+4+36,2]) 
  difference() {
    cylinder(h=6, r=5, $fn=20);
    translate([0,0,0.1]) cylinder(h=6.5, r=1, $fn=50);
} 