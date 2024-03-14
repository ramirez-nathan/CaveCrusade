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
![NavigationDiagram](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/4f71f844-6aaa-457a-b4aa-285a62cca0ec)

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
 > Screenshots of the input/output after running your application
>
 ## Installation/Usage
> In order to install and run the application, we need to first install Visual Studio, SFML, and the correct desktop extensions. Then we need to have all of the necessary files (we can clone the repository). Then we need to build the solution and then run it through the local windows debugger. The local windows debugger should be set to "Debug" and "x64". The game application will now run and the terminal should show up adjacently and display any necessary messages

 ## Testing
> We tested and validated our project using unit tests and Valgrind. Visual Studio has an integrated Google test adapter. We are using the built-in Google test project for the unit tests. We have extensive unit tests to cover all aspects of our project thoroughly. Valgrind has also been used extensively to prevent any memory leaks from occuring. 
 
