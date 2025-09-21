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

I also now need to add zooming and panning to the map, but this is enough work for one day

Day 3, Friday 19/9/2025 CE
===========================
Background
----
Yesterday I didn't have time to work on the project, we finally got the files we needed at work and I had something to work on

Today on the other hand, I did have a little spare time, (after finishing my work way ahead of schedule), so at least I did something on this project.

work
----
I have not coded today, I spent all the time drawing a really detailed map of the north atlantic region. It took many hours, but I am extremely satisfied with the direction of the art-style.

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

One Issue I have is that the hexes are too large, I think a reduction to 1/2 side is called for. This will be a lot of work, but I think it is necessary (the unit texture I made has to be thrown out), but better do it sooner rather than later

In the meantime, I should also work on adding a "coastal" hex, which both allows ships and land-units

Actually, come to think of it, terrain type and ownership should be a separate stat