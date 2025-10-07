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

I will hopefully NOT work tomorrow, as I am preparing to finish another video

work
----
Today has been extremely productive day, I focused on the GUI.

I have successfully added the following to the UI:

* A background tile 
* A flashing light, flashing when we are in the execution phase
* A marker of what phase we are in
* An execute button
* A screen for the display of text, which automatically expands and retracts

Also, I believe I may have fixed a severe crash-bug in the texture class (where I was addressing a freed pointer, this only rarely caused a crash, but it should be fixed now)


todo
----
I still need the following GUI:

* Map-modes: you should be able to toggle all hexes shown or hidden, a little like in paradox games
* text for the info screen, describing units, text should use text wrapping. Text should dynamically update (i.e. show current health)

Text seems to be a very big and complicated thing to work with.


Day 10 Saturday and Sunday 27/9/2025 CE and 28/9/2025 CE
=====
background
----------
I have introduced the idea of a half-day, so I can get work done more days. If I work less than 4 hours, I count the day as a half-day.

These two half-days are half because I uploaded another video, it was a lot of work but good to finally be done.

work
----
I did not do much today, I only got the info screen to work.

todo
----

* Map-modes: you should be able to toggle all hexes shown or hidden, and show/hide missile ranges, a little like in paradox games
* Display missile ranges as circles
* Info screen should print stats for units

Day 11, monday 29/9/2025 CE
=========================
background
----------
Office work is insanely inefficient! I just waited 4 hours for a meeting, and the meeting was basically: we agree to have a meeting next wednesday.

At least that gave me some time to work on this project.

work and todo
----
I finally got the map-modes to work, now you can toggle hexagon outlines, sam, and ssm ranges.

Now the time has come to add the attack phase. I will be a lot of days work, but it is time, and I think it would be cool if I could start the next weekly update with a re-enactment of the "russian warship go fuck yourself" incident.

what do I even need for that, truth be told, I haven't even thought this through, this has always been some thing I will figure out later

So let us make a list of what we need, for the full game version, then we will cut it down later

* The game need to go into `ATTACK_PLANNING` mode
    * In attack planning mode, you select units with right click, give attack orders with left click
    * In attack planning mode, you can click units to set up an `attackOrder` which include
      * Who attacks
      * Launch time
        * The time is arbitrarily measured in seconds into execution phase (masquerading as minutes)
        * It is possible to set launch time anywhere inside 60 seconds
        * We need a display in the left sidebar, where the user can modify 
        * I am not good at writing this, but I have a pretty clear idea inside my head
      * Projectile speed
      * Attack vectors: i.e. the waypoints the projectile follows
        * Some missiles allow multiple waypoints, i.e. you can circumvent defences by changing path
      * There should be an option (i.d.k. about the UI for it) of setting the weapon "free" to use its own seeker
      * Display vector as a thick line or with arrow rendering, display waypoints with arrival times
* After `ATTACK_PLANNING` mode, you go to `ATTACK_EXECUTION`
  * In execution mode, SSMs are launched when the launch time arrives (as long as the unit has not been destroyed)
  * Units have an "attack" animation they play
  * We need particle rendering of smoke particles, and textures for the missiles.
  * SSMs strictly follow the attack plan until the last waypoint, where they either explode or activate their seeker (let's experiment with what makes most sense)
  * Maybe add chaff clouds and CIWS with a random chance of destroying the missile
  * Each SSM do 1 hp damage to the unit if it detonates on the same hex
  * When units run out of hp they play their death animation, and disappear at the end of the phase
  * SAMs automatically launch if the calculated interception point is in range
  * SAMs should check if another SAM has been targeted at the same missile first
* I also want a Slava class cruiser to shoot at

Ok, that is a lot of stuff, a first, minimum viable product build must be a lot simpler, let us try for a simplified list

* The game need to go into `ATTACK_PLANNING` mode
    * In attack planning mode, you select units with right click, give attack orders with left click
    * In attack planning mode, you can click units to set up an `attackOrder` which include
        * Who attacks
        * Launch time
            * is always 0, instant launch
        * Projectile speed
        * Attack vectors: i.e. the waypoints the projectile follows
            * single waypoint only
        * no weapon seekers
        * simple display
* After `ATTACK_PLANNING` mode, you go to `ATTACK_EXECUTION`
    * In execution mode, SSMs are launched at the start
    * Just render the missile textures
    * SSMs strictly follow the attack plan until the last waypoint, where they either explode 
    * Units don't take damage
    * SAMs are not considered
* I also want a Slava class cruiser to shoot at

it seriously took about 3 hours to compile these lists, with a lot of thinking inbetween, I might not have time to implement it today

I only managed to do the basics: adding the `ATTACK_PLANNING` phase, and setting up some display of it.

I think I still have done a lot of work today, and I should certainly not work tomorrow


Day 12.5 (yep the half-day rule came back to bite me) 30/9/2025 CE and 1/10/2025 CE
=========
background
--------
So yeah, when I introduced the half-day rule I assumed half days would come in pairs, I guess they do not, I had a half-day then a full day.

work
-------
I worked on the attack planning and execution phases. Now I can display attack plans, and I can press the execute button and ... nothing happens, but behind the scenes I am working on making a physics engine which can actually calculate the missiles flying

I have decided that I will "bake" the physics calculations before playing back the baked calculations, this should allow the user to re-play the attack animations however many times they like.

It is conceptually very complicated and my work.

I have bodged a solution, such that I can actually throw missiles and watch them fly, they don't do any damage yet, and I really think I need to replace the current system, which uses the attackPlan class with one where the attackPlans gets turned into bakedAttackPlans with more info.

Next time I work though, I will add a Slava class cruiser and I will add damage and sinking animations, because Russian warship go fuck yourself 

todo
---
A bunch of things I need to do for the attack planning

* Use drawCircle method instead of manually drawing circle
* Display radius centered on end of path, for doglegging./
* Dogleg missiles./
* Dogleg missiles should obey range
* show arrival and launch times in game ./
* consider adding a keyboard shortcut to dogleg, for example shift
* We need some kind of on-screen gui elements, at the mouse location, indicating that we are about to add a new path or modify existing, maybe a green line indicating the possible path
* show arrival time only for SELECTED order 
* sidebar view attack orders on a per-unit basis
* allow modification of arrival time with scroll wheel
* add salvo size to file
* add salvo delay
* use pixels instead of hex for radius

And for the attack execution

* Bake physics to baked missile path class
* Have some kind of stored memory of which animations should get activated when, most notably the DIE animation
* All this should be in a physicsCake

day 14, 1/10/2025 CE and 2/10/2025 CE
========

background
-------
I forgot to write an entry for the first half-day

Anyway, I got some time to work, and ... it doesn't feel like I have done a lot, the spaghetti code is starting to get out of control (no doubt a result of me trying to rush the project)

work
====
I have gotten the missiles to fly curved paths now, but the (I have heard the term dog-legging used for that, I don't actually know if that is an English word, no wait looked it up, it IS a word, but not a very common one)

Also, I have gotten the physics engine to now bake the physics calculations into a cake.

It was very difficult to get that bit to work, but hopefully it should allow me to do some more calculations in the future


todo
----
I copied over the previous todo list, it sounds like a good idea.

I need to seriously work through this list of requirements before I add new features.

Except, the next  thing I need to do is add a Slava class cruiser I can shoot add, and then I should record the next weekly update

* Use drawCircle method instead of manually drawing circle
* Display radius centered on end of path, for doglegging./
* Dogleg missiles./
* Dogleg missiles should obey range
* show arrival and launch times in game ./
* consider adding a keyboard shortcut to dogleg, for example shift
* We need some kind of on-screen gui elements, at the mouse location, indicating that we are about to add a new path or modify existing, maybe a green line indicating the possible path
* show arrival time only for SELECTED order
* sidebar view attack orders on a per-unit basis
* allow modification of arrival time with scroll wheel
* add salvo size to file
* add salvo delay
* use pixels instead of hex for radius

And for the attack execution

* Bake physics to baked missile path class ./
* Health system for units
* Physics cake should be able to tell units how much damage they have taken
* Missile shall make explosion when they hit
* Death animation for all unit
* Have some kind of stored memory of which animations should get activated when, most notably the DIE animation
* All this should be in a physicsCake ./


Day 15 Saturday 4/10/2025 CE
======
background
---------
Russian Warship, go fuck yourself!

work
------
by bringing together everything I have done so far, I managed to sink a Slava class cruiser

The hitpoint system was a lot of work to get working, and creating death animations for everyone took a long time, but it is actually working! Unlike the Slava class cruiser, which now sits at the bottom of the Demnark straight

Right, now I think it is time to return to that big long list of todos and actually do those


todo
----
The big long list is still there

* Use drawCircle method instead of manually drawing circle ./
* use pixels instead of hex for radius ./
* show arrival time only for SELECTED order ./
* Dogleg missiles should obey range ./
* We need some kind of on-screen gui elements, at the mouse location, indicating that we are about to add a new path or modify existing, maybe a green line indicating the possible path ./
* maybe a marker on the mouse, telling us that we can use shift ./
* sidebar view attack orders on a per-unit basis
* allow modification of arrival time with scroll wheel
* add salvo delay

And for the attack execution

* Missile shall make explosion or splash when they hit (particle effect)

Day 15.5 Tuesday 7/10/2025 CE
=============================
background
-----
I had a few moments to work in-between my work tasks, and while waiting for email replies

work
----
I went through the big long list of todo items and solved a few.

Honestly, I am going through somewhat of a writers block when it comes to this game, I struggle to focus, and I struggle to make big changes

todo
----
Remaining items in the big long list of minor issues

* sidebar view attack orders on a per-unit basis
* allow modification of arrival time with scroll wheel
* add salvo delay

And for the attack execution

* Missile shall make explosion or splash when they hit (particle effect)
* Consider ripping out the physics code and remaking it from scratch because it sucks (pardon my language, but it does)
* consider if it makes sense to add weapon seekers


Longer term items

* Finish off the minimum viable product, and create a new project
* Sounds
* AI Movement
* AI Attack
* What Air-defence doing?
* Building/Lend Lease phase
* Airplanes with many waypoints
* Radar