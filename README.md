# Simple Covid Simulation Project

My idea comes from this video:https://www.youtube.com/watch?v=gxAaO2rsdIs&t=1102s

Using SFML Library to simulate covid infection.

To run this project, one must have the SFML library named "SFML" in your c drive, or change the directory in CMake

Disclaimer: This model is for simulation purpose only. It does not represent covid in the real world.

Goals:

Simulate covid epidemic in a population. People are represented as dots and they can move around in the community based on the rules.

There are several states of the people: vulnerable (blue), cured (green) or vaccinated(assuming they do not catch the virus again, which is not the case in the real world), infected (red),dead (gray).

People can move around based on the rules: no rules, wear masks but no social distancing, wear masks and social distancing by percentage, complete lockdown.

Having a timer that keeps track of time.  

Information:

These information come from this page:https://www.doh.wa.gov/Portals/1/Documents/1600/coronavirus/WearAClothFaceCovering.pdf

Note that these stats are only for simulation only. It does not represent covid in the real world.

P(Infection with no rules): 90% (your sneezes and cough can spread far away)

P(Infection with one with masks, one without, no social distancing): 50%

P(Infection with one with masks, one without with social distancing): 30% 

P(Infection with both wearing masks, no social distancing): 20% (covid can still spread if one do wash their hands often)

P(Infection with both wearing masks, and social distancing): 5%

P(Lockdown assuming all people are wearing masks, social distancing, and controlling their moves): 5% 

Optional: adding a public area where people moves frequently, like stores

Optional: having a quaratine facility that isolates identified cases
