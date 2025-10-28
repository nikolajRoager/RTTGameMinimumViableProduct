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
* allow deletion of attack orders from gui or with back-space
* allow modification of arrival time with scroll wheel
* add salvo delay

And for the attack execution

* Missile shall make explosion or splash when they hit (particle effect)
* Consider ripping out the physics code and remaking it from scratch because it sucks (pardon my language, but it does)
* consider if it makes sense to add weapon seekers


Day 16.5, Wednesday 8/10/2025 CE
===================

background
-----
Once again, I am waiting for a meeting before I can advance at work, so I have another day for this game

work
---------
I added the attack plans sidebar, which shows the queue of planned attacks in the sidebar, and I added the option to modify launch time and delete attack plans


todo
----
The time has come to create the actual project, now that the minimum viable product is done.

At the same time, here is a list of super-long term features, in no particular order

* create a new project
* Sounds
* AI Movement
* AI Attack
* What Air-defence doing? SAM should automatically get tasked against vampires
* static buildings
* ammunition management
* transport submarine (to move ground units across the sea)
* Building/Lend Lease/recruitment phase
* Airplanes which can accept many waypoints, and which return to base
* submarines and ASW
* Radar and hidden units


Day 17.5, thursay 9/10/2025 CE and Friday 10/10/2025
===================

background
-----
Now, I am waiting for someone else to fix an internal server error, ... and they have just gone on autumn holiday.

As a result, I am unable to do anything at work... (I really need a better job). as a result, I have had some time to work on this project instead.

work
---------
I merely added AI movement to the game, the AI now tries to get to its patrol locations


todo
----
The time has STILL come to create the actual project, now that the minimum viable product is done.

At the same time, here is a list of super-long term features, in no particular order

* Playback replay
* Multithreaded physics calculations (if we encounter poor performance)
* Kirov class cruiser
* create a new project
* Sounds
* AI Attack
* What Air-defence doing? SAM should automatically get tasked against vampires
* static buildings
* ammunition management
* Ai should move back to port when it is out of ammo
* transport submarine (to move ground units across the sea)
* Building/Lend Lease/recruitment phase
* Airplanes which can accept many waypoints, and which return to base
* submarines and ASW
* Radar and hidden units
* Events
* Rubber-banding AI recruitment

Day 18, Sunday 12/10/2025
===================

background
-----
I worked a lot last week, so I didn't feel like working in the weekend, I only got half a day of work sunday

work
---------
I added the option to pause the playing of the attack execution phase


todo
----
I think it is time to add in air-defence next

Day 19, Monday 13/10/2025 CE
===================

background
-----
With the guy I need to fix the internal server error on the server side on holiday, I have nothing to do at work

So I had a little time to work on this project instead. Not a lot of time, I still had a few work assignments I could work on, but enough time to do something amazing

Also, it looks like the peace deal in Gaza is going to hold, this is a good thing.

work
----
I got air-defence interception calculations working, now SAM automatically get tasked against incoming missiles and successfully intercept

Well, the missiles don't get deleted yet when they get intercepted, but getting the paths to line up is a major step in the right direction, figuratively and literally.

todo
----
Here is a short term list of things

* Air defence: delete intercepted missiles
* air defence salvo size
* longer air-defence reload
* print air-defence stat to screen


The time has STILL come to create the actual project, now that the minimum viable product is done.

At the same time, here is a list of super-long term features, in no particular order

* Allow clicking on enemy units during movement phase
* Multithreaded physics calculations (if we encounter poor performance)
* Kirov class cruiser
* create a new project
* Sounds
* AI Attack
* static buildings
* ammunition management
* Ai should move back to port when it is out of ammo
* transport submarine (to move ground units across the sea)
* Building/Lend Lease/recruitment phase
* Airplanes which can accept many waypoints, and which return to base
* submarines and ASW
* Radar and hidden units
* Events
* Rubber-banding AI recruitment

Day 20, Tuesday 14/10/2025 CE and Wednesday 15/10/2025
===================
background
------
I took a few hours to work on this project after work for two days

work
----
Now intercepted missiles get deleted, and they make a nice particle effect indicating their fate.

todo
----
The time has really come to add sound

Day 21, Friday 17/10/2025
===================

background
-------
I took a day off from work, because I literally have nothing to do, since we are waiting for a client to return from holiday to fix an error on their side (I REALLY need a better job)

This log is a bit different, I am writing these words BEFORE I really start working today, because I don't actually know what I shall do today.

Well, before I wrote this I have added sound and made it possible to click enemy units, and both things were surprisingly easy, and now I don't know what to add next.

Let us go back to the big long list, and let us organize it so we can see the things which depend on each other, and lets give each

I also added a letter code for the priority, A is top priority, B is less, and so on

A and B priority definitely, C either needs to be added, or a workaround found, D and E are more questionable nice to have features

* More (mobile) units
  * C Kirov class cruiser
  * C Russian lighter ships
  * C American frigates (LCS, two kinds)
  * D Add submarines and ASW
    * D Add SONAR (should be based on Radar)
    * D Add ability to target submarines (maybe just normal attack, maybe special ASW attacks)
      * D American and Russian missile submarines
      * D Add Swedish submarines
      * B Transport submarines
        * B Dialogue to move units or cargo onto sub (requires ammunition management)
  * B Add Swedish and Norwegian ships and land units
  * C Add other European land and sea units (For lend-lease, oh god, that is a lot of different units)
  * C Add aircraft carriers (requires planes)
    * C Add American aircraft carriers
    * D Add Admiral Kuznetsov (only one hp!, may randomly explode)
    * C Add British and French carriers (For lend lease, yes, I am 100% serious)
* (A If performance is a problem, otherwise E) Multithreaded physics and AI calculations
* B create a new project, with a more fitting name
* A Sweden and norway need to be friendly territory (Denmark is too small for buildings)
* A static buildings, just units with movement range set to 0
  * A Buildings can not move, buildings may stick around if destroyed (can be repaired)
    * A Depot (For ammunition management)
    * C Army headquarters (For land combat, or just as an additional thing to protect)
    * A City (As land target, maybe make it a terrain type)
    * A Factory (For ammunition management, maybe need to be in-range of a city)
    * A Power plant (maybe required by city or factory to function)
    * A Airbase (for airplanes, has super-long range)
    * A Radar site (For spotting, maybe require in range of power-plant)
    * A SAM site
    * A Cruise missile site
    * A Ballistic missile site (Longer range, higher speed)
    * A Population and electricity ranges
* B AI Attack (requires radar and detection)
  * B AI attacks (only detected) friendly units in range
  * D AI should use dogleg path to avoid air-defence bubbles
  * D AI prioritize different units 
* B resource management (requires buildings)
  * B All units can store resources, resources include SSMs, SAMs, Supplies (maybe split into multiple types)
  * B Units should have boolean flags for which resources they can store
  * B When unit is destroyed, all resources are destroyed as well
  * C Units can be stored as a resource
  * C resources have "weight" limiting number 
  * B Depot units can exchange resources within range TEST IF THIS SHOULD BE INSTANT, OR DELAYED
    * C AI should move back to depot when it is out of ammo
    * C AI automatically exchanges resources betwixt depots
    * C Depots can transport to "coastal" sea tiles
  * B transport submarine is a depot
* B Building/Lend Lease/recruitment phase, maybe together with movement phase
  * C There is a "lend lease timer", which gives player event to get unit for free
  * C Player can build buildings if resources are in range
  * C Player can buy (mobile) units
  * C Player can only buy units in core territory (Greenland is NOT core)
  * B player can Repair damaged units (at the cost of resources)
  * D AI repairs damaged units, but does not build buildings
* C Airplanes which can accept many waypoints, and which return to base
* A Radar and hidden units
  * A Units get detected by radar in range (range varies from unit to unit)
  * A Radar itself gets detected at twice the range
  * A Radars have an EMCON (radar off) setting
  * A Display needs to only display units visible to the player (can be disabled for debug)
* Scenario upgrades
  * A Load scenario from a file
  * B Events
  * C Rubber-banding AI recruitment
  * C Narrative campaign
    * Events included in the campaign should be the following, in chronological order:
      * The Nuuk incidence (war breaks out)
      * Article 5 and response (Britain sends thoughts and prayers, Nordics join the war, Hungary says LOL, the rest sends lend lease)
      * US Invasion of Canada
      * Britain only joins lend lease later
      * The midterm election
      * The Rubio-Lavrov pact (Russia joins the war on US side, and invades Europe)
      * The rest of Europe joins the war
      * Victory in the east IF LAND COMBAT HAS BEEN ADDED, triggered by the player conquering the Russian capital Moscow
      * Victory in the west IF LAND COMBAT HAS BEEN ADDED, triggered by the player conquering the American capital Mar-A-Largo
  * c tutorials

Oh god, this is a big long list, I will not have time to add everything!

I think the first thing I should do today, is adding Norway, Sweden and buildings.

Ok, I am done working today, honestly I spend so much time on this list that I didn't have a lot of time to add stuff.
I added Norway, Sweden, Finland, Iceland and the Faroe Islands as friendly territory, and I added the animations for some buildings

todo
----
See the big long list above, in fact I created another file with the big long list, titled bigLongList.md

Day 22, Saturday 18/10/2025 CE
===================

background
-------
This was almost a half day, I really didn't work a lot today, but I worked more than 4 hours so it counts as a full day.

I really need to either commit to work 8 hours or more, or not more than 4 hours

work
-----
I only got the ranges of power and population supplied by cities and factories to work

todo
----
Tomorrow is radar day, I will also be travelling, so I don't know how much work I actually get to do


Day 22.5, Sunday 19/10/2025 CE
=====
background
----------
I am travelling today, so I don't have a lot of time to work, I barely did anything actually, and I probably shouldn't have worked at all

work
----
Today is radar day, but I haven't started working yet, first, I need to come up with the rules for radar and detection.

All units have a `visible` flag, which is true if detected by the enemy.

Visibility is updated before and after the movement planning phase.

All units have a fixed "visual" detection range, inside which they always detect all enemy units.

Units have a `hasFiredWithoutMoving` flag, which is true iff they fired SAM or SSM last attack execution phase, and can be cleared by moving in the movement planning phase.
If a unit has `hasFiredWithoutMoving` then `visible` is true

Units have a `radarOn` flag (has no effect if `radarRange<=0`, and if so is hidden), the player can switch this on/off during both the movement planning phase, and the attack planning phase

Units with `radarOn` and `radarRange>0` detect all hostile units inside their radar range, and are detected by all hostile units inside twice their range.

Ok, those are the rules, it looks like there are a bunch of different coding tasks now:

* include visual range, and load radar range from file
* Make debug rendering of radar-range and visual range
* create `updateVisual` function, and place it in the appropriate places
* Add FiredWithoutMoving
* Add GUI option to show/hide radar range
* Hide display of hidden units, and also hide SSM and SAM range of hidden units
* Add DEBUG option to still show them
* Remember to check that dead, or unpowered radars don't work

Ok, I did a few things at least

todo
-----
Regarding the radar, do this:

* Add GUI option to show/hide radar range
* Continuously update visibility during movement execution
* Hide display of hidden units, and also hide SSM, Radar and SAM range of hidden units
* Add DEBUG option to still show them
* Remember to check that dead, or unpowered radars don't work

Regarding buildings: add "immortal" buildings (only damaged and deactivated at 0 hp, never deleted)

Day 23, 26/10/2025 CE
========
background
------
I am honestly going through a bit of a writers block for this game ... I am also very afraid that it is not actually fun.

work
----
I added enemy attacks, the enemy now autonomously throws missiles in my direction

todo
----
Regarding the radar, do this:

* Add GUI option to show/hide radar range
* Continuously update visibility during movement execution
* Hide display of hidden units, and also hide SSM, Radar and SAM range of hidden units
* Add DEBUG option to still show them
* Remember to check that dead, or unpowered radars don't work

Regarding buildings: add "immortal" buildings (only damaged and deactivated at 0 hp, never deleted)

