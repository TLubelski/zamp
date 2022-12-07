/*
* Apollo11 - 20 lipca 1969 (koloryzowane)
*/

#define ROTATE_SPEED 50
#define FLIGHT_SPEED 20

Begin_Parallel_Actions //poszukiwanie miejsca 
Move Rocket FLIGHT_SPEED 10
Rotate Rocket ROTATE_SPEED 360
End_Parallel_Actions

Pause 1000 //czekanie na odpowidni moment

Move Rocket FLIGHT_SPEED 10 // lądowanie

