// Flipdot Display 
// Cover of 3D Printed Casing
// RasperryPi B + Voltage Regulator Board
// CC4.0-BY SA NC   surasto.de

difference() {
    cube(size=[190,74,38]);
    translate([2,2,2]) cube(size=[190-4,74-4,40]);

    translate([-5,8,38-24]) cube(size=[10,40,40]);

    translate([185,7,38-8]) cube(size=[10,16,40]);

    translate([185,12,38-9]) rotate([0,90,0]) cylinder(r=2,h=10,$fn=50);
    translate([185,18,38-9]) rotate([0,90,0]) cylinder(r=2,h=10,$fn=50);

    translate([40,-10,10]) cube(size=[2,100,10]);
    translate([46,-10,10]) cube(size=[2,100,10]);    
    translate([52,-10,10]) cube(size=[2,100,10]);    
    translate([58,-10,10]) cube(size=[2,100,10]);
    translate([64,-10,10]) cube(size=[2,100,10]);   
    translate([70,-10,10]) cube(size=[2,100,10]);   
    translate([76,-10,10]) cube(size=[2,100,10]);
    translate([82,-10,10]) cube(size=[2,100,10]);

    translate([130,70,10]) cube(size=[2,10,10]);   
    translate([136,70,10]) cube(size=[2,10,10]);   
    translate([142,70,10]) cube(size=[2,10,10]);
    translate([148,70,10]) cube(size=[2,10,10]);
}