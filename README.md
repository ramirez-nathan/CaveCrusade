# Cave Crusade: Rise of the Shadow Master
 Developers: [Nathan Ramirez](https://github.com/ramirez-nathan), 
            [Russell Ly](https://github.com/Ampherost), 
            [Alexis Manalastas](https://github.com/amana032), 
            [Rachel Lee](https://github.com/rache11ee)

## Project Description
 **Cave Crusade: Rise of the Shadow Master** is a whimsical dungeon-crawler RPG that will have you battling through swarms of evil monsters in hopes of making it out alive!<!--  Boulder the Wizard, an evil rock who plans to take over the kingdom with an army of despicable monsters! --> Fight your way to the end using your trusty weapons and see what lies at the end of the cave... if you can even make it there! <!-- to recover the Box of Wonder that was stolen from your kingdom! -->

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
![CaveCrusadeNavigationDiagram](https://github.com/user-attachments/assets/cad7f079-2842-4067-9c82-fc7e3e7a014f)

### Screen Layouts
Start Screen:
![CCStartScreen](https://github.com/user-attachments/assets/8149608f-3092-488b-9a96-6489d7c40afd)

In-Game Screen:
![CCInGameScreen](https://github.com/user-attachments/assets/8bc4d1f5-3721-4b2d-bb96-bf8f2c031cd5)

Game Over Screen:
![CCGameOverScreen](https://github.com/user-attachments/assets/2b2edb44-72d1-46da-9373-7b83038af5eb)

## Class Diagram
![CaveCrusadeClassDiagram](https://github.com/user-attachments/assets/58ce9731-5ec3-4256-a852-1d5ce5682248)

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

![CCScreenshot1](https://github.com/user-attachments/assets/7b00a17d-a184-44f4-a4ae-f548b160e2e3)

 Bow attack loads from clicking left-click

![CCScreenshot2](https://github.com/user-attachments/assets/cd51afca-ce44-46e0-8941-9bc163d33b5e)

 Sword attack loads when clicking right-click

![CCScreenshot3](https://github.com/user-attachments/assets/124e918d-3f31-4cbd-8621-9f9f9f132209)

 Chest interactable

![CCScreenshot4](https://github.com/user-attachments/assets/03da3bf6-7f50-4881-8676-c85b1eff63d4)

 Enemy variety




 ## Installation/Usage
 In order to install you can download the repository as a zip, extract it, and in the main folder use the Cave Crusade executable. 
 If you would like to edit and run the application, we need to first install Visual Studio, SFML, and the correct desktop extensions. Then you need to have all of the necessary files (you can clone the repository). Then you need to build the solution and then run it through the local windows debugger. The local windows debugger should be set to "Debug" and "x64". The game application will now run and the terminal should show up adjacently and display any necessary messages. 

 ## Testing
 
In order to test our project we created and looked over unit tests that took several classes and functions into consideration. We used Visual Studio's built-in Google Test framework in order to easily reference our classes and make sure we have good test coverage. 

We also attempted to utilize Valgrind in the hopes of detecting any memory leaks and other memory-related issues. Our team hopes to be able to work with Valgrind in the future in order to make sure the project stays stable as well as reliable. 
