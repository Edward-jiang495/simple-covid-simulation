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

Do not be fooled by these numbers. The reason that the transmission rate is low here is because I also take account of time. The longer time one spends with another, the higher chance one will have to catch Covid-19.

P(Infection with no rules): 20% (your sneezes and cough can spread far away)

P(Infection with one with masks, one without, no social distancing): 10%

P(Infection with both wearing masks, no social distancing): 5% (covid can still spread if one does not wash their hands often)

P(Lockdown assuming all people are wearing masks, social distancing, and controlling their moves): 5% 

Optional: adding a public area where people moves frequently, like stores

Optional: having a quaratine facility that isolates identified cases
