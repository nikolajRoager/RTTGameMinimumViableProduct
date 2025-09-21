Pre-minimal viable product build of a game, working title "What airdefence doing" or "defence of Greenland"
=================================================================================

For the pre-mvp we need

* Map display
* Basic land and sea units (no air) and buildings
* Movement phase (planning and execution)
* 2 players: human and human
* Expandable UI for all of the above

We will explicitly not need:

* Sound
* AI
* Fog of War and radar
* Aircraft and airbases
* Missiles
* SAM
* Attack vectors and timing management
* Attack phase
* Events and messages
* Customizable scenarios
* Economy


units
-----
For now, all units are hardcoded, in the full game they should be loaded from files

The units are handled by a `unitType` and `unit` class, the former is an archetype which handles animations and constant data, the latter is an instance in the game

By default, all units are facing left, images can be mirrored if need be.
Each unit should have a number of animations

* idle (MAY just be an image)
* Move left (can be mirrored)
* Prepare attack (select)
* un-prepare attack (deselect)
* attack+recover
* die

In the finished game, some animations may spawn particles using the poisson distribution



Types of units in minimal viable product

* SAM truck
* Cruise Missile Truck
* Frigate
* Destroyer?
* Cruiser?
* Submarine?
* Brigade Headquarter (building)
* ammo depot (building) ?

Buildings are a type of units, with movement point 0


Movement phase
--------------
The finished game shall have 2 phases: Movement phase and attack phase, (each phase is split into planning and execution)

The Pre minimum viable product only has the movement phase

When you click on a friendly unit, it should highlight all the places it is able to move with a red outline

When you mouse over a destination, arrows should highlight which way the unit will move

Dijkstra or A* Pathfinding is required!

Steps today:

Click to select origin, then mouse over destination, dijksta betwixt, show arrows



UI for all of the above
----------------------
In general. The UI should have an option to expand/retract, either based on a keyboard shortcut or a button with an arrow on it


For the units: A sidebar should open when you click on a unit, with some basic information like hp, mp, aa range, anti-surface range, radar range, and maybe a short text


For the movement phase: There should be an "execute" button, which also shows what phase you are in. Pressing it either gives control to the other player, or enters execution phase