Autonomous Vehicle Routing Problem

Ride-sharing has become an ubiquitous way of getting around in town and cities. Efficient vehicle routing, or figuring out the most efficient way to direct vehicles to pick up and drop off multiple passengers at a time, has become a crucial component of their success. This code base aims to mimic a vehicle routing problem for an autonomous ride-sharing vehicle. 

The city is a grid of perpendicular blocks.  At initialization the code should take as inputs the number of streets in both the x and y directions (ex. x=10, y=10). The starting point of the car can also be specified by the user. 

The car can move in any direction exactly 1 block at a time.  We only care about when the car is at a vertex of two intersecting streets, so a car can be at the intersection (0, 0) in the upper-left corner of our city, or (9, 9) in the bottom-right corner.


There is a function that accepts a list of ride requests. These ride requests come in the form of a list of JSON elements like so:

{ requests: [
         { 
           'name': 'Elon', 
           'start': (3,5), 
           'end': (8,7) 
        },
        { 
           'name': 'George', 
           'start': (1,2), 
           'end': (4,3) 
        }
      ] 
   }


At each time step, the current position of the vehicle and the names of all of the passengers currently in the vehicle are printed, as well as anybody being dropped off or being picked up at this intersection. (It is assumed that the car can fit infinitely many people at a time.)


Trade-offs:
The modular software architecture implemented ensures that the algorithms can be swapped out relatively easily. A path planning algorithm such as A* would not work without developing heuristics on the fly. Since this would add computational complexity to a relatively simple problem statement, I implemented an algorithm which would reduce the x-directional and y-directional offsets in sequence. Finally, once the vehicle has dropped all the passengers and there are no remaining orders left, it is programmed to return to its initial spawn location.

Some of the design functionalities implemented:
1. Homing functionality: vehicle returns home after dropping everyone
2. Modular architecture: path planning and scheduling algorithms can be easily swapped out

Room for improvements:
1. VRP/TSP heuristic-based scheduling algorithms can be implemented