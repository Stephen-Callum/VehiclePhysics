# VehiclePhysics

Developed with Unreal Engine 4

A challenge for myself to create hover vehicle physics from scratch. This project includes:

## 4-point Suspension
![Image of 4-point suspension](https://i.imgur.com/GOhpXIn.jpg)

Consists of a raycast from each bottom corner of the vehicle going down for the length of the suspension. If the raycast does not hit anything, then that means the suspension is fully extended. 

If it hits, calculcate the compression ratio (compression delta / suspension height). Compression delta is calculated from subtracting the hit distance (Hit.Distance from the FHitResult structure) from the suspension height. 

The resulting force is the sumation of the raw force and spring damping. The force is them applied upwards at the points of the suspension.

## Accelration/Braking

Acceleration and braking occurs through the application of a forward force from just below the center of gravity for the vehicle. This gives the vehichle a jerking motion when going forward or backward.

## Traction

Traction is achieved through the increase in the linear and angular damping of the mesh of the vehicle.
