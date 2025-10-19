TODO: The Big Long List
============

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
        * A Depot (For ammunition management) ./
        * C Army headquarters (For land combat, or just as an additional thing to protect)
        * A City (As land target, maybe make it a terrain type) ./
        * A Factory (For ammunition management, maybe need to be in-range of a city) ./
        * A Power plant (maybe required by city or factory to function) ./
        * B Airbase (for airplanes, has super-long range)
        * A Radar site (For spotting, maybe require in range of power-plant) ./
        * A SAM site
        * A Cruise missile site
        * A Ballistic missile site (Longer range, higher speed)
        * A Population and electricity ranges ./
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
    * A Units get detected by radar in range (range varries from unit to unit)
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
