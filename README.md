# Cave Crusade: Rise of the Shadow Master
 Authors: [Nathan Ramirez](https://github.com/ramirez-nathan), 
            [Russell Ly](https://github.com/Ampherost), 
            [Alexis Manalastas](https://github.com/amana032), 
            [Rachel Lee](https://github.com/rache11ee)

## Project Description
 **Cave Crusade: Rise of the Shadow Master** is a whimsical dungeon-crawler RPG that will have you battling through swarms of evil monsters to defeat Boulder the Wizard, an evil rock who plans to take over the kingdom with an army of despicable monsters! Fight your way to the end of his dungeon using an array of weapons to recover the Box of Wonder that was stolen from your kingdom! 

The project aims to captivate players through an immersive storyline, strategic gameplay, and a visually appealing environment.

 Tools & Technologies:
* Visual Studio Community
* SFML C++ Library

 Inputs:
* Keyboard input for player movement and actions
* Mouse input for navigating menus and interacting with in game elements

 Outputs:
* Rendered graphics and animations displayed on the game window using SFML
* Game sound effects and music
* Information about player's status, like health and weapon equipped
* In-game text for dialogue and game events 

 Features:
 * Immersive movement and combat system --> Movement will be done using WASD controls to get around the tile map(s) and the player will be able to fight against the opponent with a weapon of choice.
 * Unique monsters and bosses --> Enemies and the Boss will be distinguishable in terms of their looks as well as what types of attacks will be executed against the player.
 * Dungeon-crawling gameplay --> The hero encounters and fights against opponents in a dungeon environment to advance through different rooms to get the Whisk of Wonder.

### Navigation Diagram
![caveNav](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/e50224f3-62bc-40a0-8f93-a95e0ea631a8)


### Screen Layouts
Start Screen:
![CaveCrusadeStartScreen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/04672150-48c8-4f90-b208-026b84f8847f)

Menu Screen: 
![CaveCrusadeMenuScreen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/99c0eaeb-a8a6-4b30-8d0e-24a48d2c6bed)

In-Game Screen:
![CaveCrusadeInGameScreen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/6cd9e566-1971-4390-891e-0a0d6bc4eecc)

## Class Diagram
![CakeCrusadeClassDiagram](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/d2a5c061-6ec1-4a4d-84b2-7e3b3b2f16b1)

| Class | Description |
| --- | --- |
| `Main` | Depends on GameState, Entity, & Interactable; Main screen for creating and calling other classes |
| `Entity` | Inherits from Object; Template for entities |
| `Player` | Inherits from Entity; Sets player weapon, powerup, and moveset |
| `Arrow` | Deals with Arrow handling. player and skeleton are dependent on this | 
| `Math` | Deals with Collision handling |
| `Enemy` | Inherits from Entity; Sets enemy target and knockback |
| `Soldier` | Inherits from Enemy, chases and attacks the player; |
| `Skeleton` | Inherits from Enemy, acts as a stationary sentry turret; |
| `Slime` | Inherits from Enemy, a slow gelatinous blobby enemy; |
| `RockHandler` | Inherits from Enemy, sets up functionality for Rock;
| `Rock` |  Inherits from RockHandler, makes rocks fall from the top of the map; |
| `Interactable` | Associates with Entity; Template for interactable objects |
| `Main Menu` | Depends on Main; Template for Menus |
| `Cutscene` | Inherits from Main Menu; Can start and quit |
| `GameState` | Depends on TileMap; Contains level templates and updates the level |
| `Tilemap` | SFML map drawing |
| `Sounds` | Associated with Main; Sound Effects |

 
 
 ## Screenshots
 ![caveIdle](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/933f54ef-bab4-4797-9e4c-b56ac38a5444)
 Idle animation when doing nothing

 
 ![caveLeftclick](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/3b78b636-ab57-429c-ab3f-a9f207134d99)
 Bow attack loads from clicking left-click

 
 ![caveRightclick](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/b5be76a1-4bef-4031-8d90-38e760646f65)
 Sword attack loads when clicking right-click

 
 ![caveRoom1](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/627824f2-6f82-4555-98f0-087027e6e221)
 View of the first room


 ![caveRoom2](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/268a7f72-ca3c-45fc-ba52-0fc43fccd2f8)
 Moves to the door and the second room loads

 
 ![caveWorld2 1](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/6ada7dbe-0046-4f45-b167-6085b4b61509)
 Finishes first-world and loads second-world

 
 ![caveWorld2](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/0c534900-1303-45f8-9ae8-248941bd6ef2)
 Second room of the second-world






 ## Installation/Usage
 In order to install and run the application, we need to first install Visual Studio, SFML, and the correct desktop extensions. Then we need to have all of the necessary files (we can clone the repository). Then we need to build the solution and then run it through the local windows debugger. The local windows debugger should be set to "Debug" and "x64". The game application will now run and the terminal should show up adjacently and display any necessary messages

 ## Testing
 
In order to test our project we created and looked over unit tests that took several classes and functions into consideration. We used Visual Studio's built-in Google Test framework in order to easily reference our classes and make sure we have good test coverage. 

We also attempted to utilize Valgrind in the hopes of detecting any memory leaks and other memory-related issues. Our team hopes to be able to work with Valgrind in the future in order to make sure the project stays stable as well as reliable. 
