Day 1, Tuesdag 16/9/2025 CE
============
background
---
I am going to only count working days, for the purpose of this self-made challenge, a working day is any day I do any work at all, regardless of how much or how little

Anyway, today I was stuck at work, because someone else broke the key-file we need to get access to an authentification server... so I am unable to work at work, so I had several hours for this project

work
----
I am going to start with a pre-minimum viable product, where I just play around with the map, try to get zooming and panning to work, and try to maybe eventually get units I can move around on a hex grid.


I set up some kind of basic framework, with an Engine loading and initializing SDL, and opening a black screen; and a scenario class doing nothing at all for now.

For now, all assets loaded and settings will be hardcoded in the scenario, but I hope to make the scenario able to load different, well, scenarios

C++ + SDL Is much slower than C# + Monogame to work in for sure, since I have to think about memory management myself.

todo
----
we will see

Day 2, Wednesday 17/9/2025 CE
=====================================
background
---
Still no progress getting the new key-file, the people who has the file responded to our email, confirming that they did, in fact, break it. But they asked us to look in a not-actually-shared word document

As a result, I had the entire working day to work on this project instead.

If only I actually got paid for not working ...

work
----

I Spend a lot of time getting the framework to work on Windows, which is a terrible operating system compared to Linux in every metric.

Apart from that, I created a texwrap class as a wrapper for textures, and got a static picture of greenland on the screen

Oh, and I have decided I want a hexagonal grid for sure, and I have started painting a hexified map of Greenland... I think it is all a waste of time though, since I think the image is the wrong resolution.

One problem I have is that Greenland is much taller than it is wide, but my screen is wider than it is tall, so there is a lot of uggly black-space next to greenland.

For now, I included the rest of Europe and the continental US, I am still not sure of the art style for the map though

todo
-----
I also now need to add zooming and panning to the map

Day 3, Friday 19/9/2025 CE
===========================
Background
----
Yesterday I didn't have time to work on the project, we finally got the files we needed at work and I had something to work on

Today on the other hand, I did have a little spare time, (after finishing my work way ahead of schedule), so at least I did something on this project.

work
----
I have not coded today, I spent all the time drawing a really detailed map of the north atlantic region. It took many hours, but I am extremely satisfied with the direction of the art-style.

todo
-----
Tomorrow, it is time to get scaling and maybe zooming and panning of the map to work. It must work on any size display.

Day 4, Saturday 20/9/2025 CE
========
Background
----------
Weekend, I did work on another video, but I still had some time to work on this.

It begins to dawn on me what a massive project this is, and how little time I have for it

Work
----
I have done some work on selecting hexes, and I have begun working on adding units to the map.

I still can't select them or move them around, and they are not animated, but some of the framework is there

I decided to not do scaling and panning, so far the entire game fits on the screen, and I will keep it that way for now

todo
----
One Issue I have is that the hexes are too large, I think a reduction to 1/2 side is called for. This will be a lot of work, but I think it is necessary (the unit texture I made has to be thrown out), but better do it sooner rather than later

Day 5, Sunday 21/9/2025 CE
==========================
Background
---------
I had a lot of time to work today, I don't feel like I had a lot of progress though

Day 5, that is 1/20 of the way to 100, time really does fly and I doubt I will be able to finish this project

I should aim for being done with the Mimimum viable product by day 20

Work
-----
I re-scaled the hexagons to be half the size, I much prefer it this way. It took a lot of time since I am still manually hardcoding the individual hexagons

I also refactored the code, now there is a hexGrid class which handles the grid, including rendering and pathfinding utilities ...

... well ok, pathfinding was supposed to work today, but it does not.

I can however find the neighbours of each hex, and find the hexes within a number of steps of each hex.

todo
----
Next day I work (i.d.k. if it will be tomorrow) I need to get Dijkstra pathfinding to work.

I also need some kind of arrow rendering, so that I can draw arrows from the selected units to wherever they can go.

On a second thought, arrow rendering might be too much for a minimum viable product, lets save that for later

Day 6, Monday 22/09/2025 CE
=====
background
----------
Today I successfully finished my work surprisingly early, now I need to wait for a meeting tomorrow before I get a new task.

Which means ... I have time to work on THIS project

Work
-----
Pathfinding was surprisingly easy to get working, it is not Dijkstra's algorithm, but rather a custom algorithm for pathfinding on a hexagonal grid.

I thought that would be a full day of work. What on Earth do I do now!?

Well, I decided to work on animations, now units have a distinct animation when selected and deselected, and I think that works really well.

A lot of refactoring was needed to make the animations work, so I didn't have time to execute the movement phase, but some initial work was done.

Todo
----
Actually adding in an execution phase to the movement is really called for.

Actually, I need a movement phase for the other player as well, followed by

You know, now might be time to make the first video report, let us do that next day I have time to work.

Day 7, tuesday 23/9/2025 CE
====
Background
----------
It amazes me how inefficient office work is, I spent the entire day working on this project, because I was waiting on a video-call

Work
----
I added animated motion during the execution of the movement phase, I also started work on a Danish frigate as my next type of unit

I believe the pre-minimum viable product might soon be finished

Tomorrow, I am working from home, I will take that as a chance to record the first video update.



Remaining problems/Todo
------------
I have decided that from now on, I will copy all remaining problems into the todo section, and keep copying them until they get solved, so here you go:

Continue adding Danish frigates and American destroyers (maybe add LCS as a stand-in for frigates)

add cruise missile launchers

Pressing execute should clear selected tile and unit

It is currently possible for different units to travel to the same tile, fix it 

Make the button to move units right click, left click to cancel 

Make propper arrow rendering

Make enemy side take turn, just like the player (for now, to be replaced with ai later), make sure enemy can't be controlled when it is the player's turn

Day 8, tuesday 25/9/2025 CE
============
background
-----------
I didn't have a lot of time to work this day, only around 3 hours. But yesterday I recorded the first weekly update

Work
----
I didn't do a lot, I only tied up some loose ends without really starting anything new. I fixed the following

* we now give movement orders with right-click
* moving to the same position is now impossible
* units no longer need to maneuver around each other
* a marker for the friendly units during the movement planning phase
* executing movement phase now clears selection

Day 9, 26/9/2025 CE
=======
background
-----------
Today, I have once again finished my work assignment ahead of time, and I don't have anything other than this project to work on.

Only problem is that I have no idea what I should work on now

work
----
I think I should work on the GUI, really that is the final thing I need for the Minimal Viable Product. I haven't really done any thinking as to how.

Should I make a specific GUI class, or should I just wing it, by putting it in the scenario class?

well, I know the right answer is to give it its own class... so that is what I have done now

I have successfully added the following to the UI:

* A background tile 
* A flashing light, flashing when we are in the execution phase
* A marker of what phase we are in
* An execute button

Also, I believe I may have fixed a crash-bug

I still need:

* Map-modes
* A screen displaying text info of units, text should use text wrapping, screen should be expandable
* We need mouse-over text when hovering over gui elements, should activate after half a second of hovering
* The above requires installation of the SDL2_TTF library