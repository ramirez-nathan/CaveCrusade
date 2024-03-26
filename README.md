# Cave Crusade: Rise of the Shadow Master
 Developers: [Nathan Ramirez](https://github.com/ramirez-nathan), 
            [Russell Ly](https://github.com/Ampherost), 
            [Alexis Manalastas](https://github.com/amana032), 
            [Rachel Lee](https://github.com/rache11ee)

## Project Description
 **Cave Crusade: Rise of the Shadow Master** is a whimsical dungeon-crawler RPG that will have you battling through swarms of evil monsters in hopes of making it out alive!<!--  Boulder the Wizard, an evil rock who plans to take over the kingdom with an army of despicable monsters! --> Fight your way to the end using your trusty weapons and see what lies at the end of the cave... if you can even make it that far! <!-- to recover the Box of Wonder that was stolen from your kingdom! -->

Our project aims to captivate players through <!-- an immersive storyline, -->strategic gameplay and a visually appealing environment.

 Tools & Technologies:
* Visual Studio Community
* SFML C++ Library

 Inputs:
* Keyboard input for player movement, actions, and interacting with in game elements
* Mouse input for navigating menus and attacking

 Outputs:
* Rendered graphics and animations displayed on the game window using SFML
* Game sound effects and music
* Information about player's status, like health, ammo, and weapons available
* In-game text for dialogue and game events

 Features:
 * Immersive movement and combat system --> Movement will be done using WASD controls to get around the tile map(s) and the player will be able to fight against the opponent close and personal by using their sword, or from afar using their bow
 * Unique monsters and bosses --> Enemies and the Boss will be distinguishable in terms of their looks as well as what types of attacks will be executed against the player.
 * Dungeon-crawling gameplay --> The player encounters and fights against opponents in a dungeon environment to advance to the next room and progress through the cave.

### Navigation Diagram
![caveNav](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156261930/e50224f3-62bc-40a0-8f93-a95e0ea631a8)

### Screen Layouts
Start Screen:
![home page](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/3a4a98e1-0fb9-4123-8827-ccc4e3f329c3)

In-Game Screen:
![in-game-screen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/117fff29-f7d6-4bcb-a653-542f7f481f7f)

Game Over Screen:
![game over](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/3302e9b2-aec1-468d-9c47-49bf13b52025)

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

![bow attack](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/ab6562dd-6ad8-4456-8e14-e587b8c833b4)

 Bow attack loads from clicking left-click

 ![sword attack](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/880a0052-b773-49ff-95fc-904cb93977f9)

 Sword attack loads when clicking right-click

![chest interactable](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/d32fbc32-854b-494f-9128-0a49e29c9a7d)

 Chest interactable

![enemy variety](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/156156677/dac396e3-4347-4b94-9d23-b9614b3841bd)

 Enemy variety




 ## Installation/Usage
 In order to install you can download the repository, unzip it, and in the main folder use the Cave Crusade shortcut. 
 If you would like to edit and run the application, we need to first install Visual Studio, SFML, and the correct desktop extensions. Then you need to have all of the necessary files (you can clone the repository). Then you need to build the solution and then run it through the local windows debugger. The local windows debugger should be set to "Debug" and "x64". The game application will now run and the terminal should show up adjacently and display any necessary messages. 

 ## Testing
 
In order to test our project we created and looked over unit tests that took several classes and functions into consideration. We used Visual Studio's built-in Google Test framework in order to easily reference our classes and make sure we have good test coverage. 

We also attempted to utilize Valgrind in the hopes of detecting any memory leaks and other memory-related issues. Our team hopes to be able to work with Valgrind in the future in order to make sure the project stays stable as well as reliable. 
