# Cake Crusade: Rise of the Pastry Master
 Authors: [Nathan Ramirez](https://github.com/ramirez-nathan), 
            [Russell Ly](https://github.com/Ampherost), 
            [Alexis Manalastas](https://github.com/amana032), 
            [Rachel Lee](https://github.com/rache11ee)

## Project Description
 **Cake Crusade: Rise of the Pastry Master** is a whimsical dungeon-crawler RPG that will have you battling through swarms of delicious monsters to defeat Baker the Wizard, an evil magician who plans to take over the kingdom with an army of mouthwatering monsters! Fight your way to the end of his dungeon using an array of weapons to recover the Whisk of Wonder that was stolen from your kingdom! 

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
![CakeCrusadeStartScreen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/04672150-48c8-4f90-b208-026b84f8847f)

Menu Screen: 
![CakeCrusadeMenuScreen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/99c0eaeb-a8a6-4b30-8d0e-24a48d2c6bed)

In-Game Screen:
![CakeCrusadeInGameScreen](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/6cd9e566-1971-4390-891e-0a0d6bc4eecc)

## Class Diagram
![CakeCrusadeUML](https://github.com/cs100/final-project-amana032-rlee205-rly014-nrami112/assets/136412424/da454239-e67f-4412-91af-c28893160b8a)

| Class | Description |
| --- | --- |
| `Main` | Depends on GameState, Entity, & Interactable; Main screen for creating and calling other classes |
| `Entity` | Inherits from Object; Template for entities |
| `Player` | Inherits from Entity; Sets player weapon, powerup, and moveset |
| `Enemy` | Inherits from Entity; Sets enemy target and knockback |
| `Interactable` | Associates with Entity; Template for interactable objects |
| `Heart` | Inherits from Interactable; Contains health value |
| `Chest` | Inherits from Interactable; Contains chest contents |
| `Main Menu` | Depends on Main; Template for Menus |
| `Start Screen` | Inherits from Main Menu; Can start and quit |
| `Options`| Inherits from Start Screen; Has window, sound, and control options |
| `GameState` | Depends on TileMap; Contains level templates and updates the level |
| `Tilemap` | SFML map drawing |
| `Sounds` | Associated with Main; Sound Effects |

 
 > ## Final deliverable
 > All group members will give a demo to the reader during lab time. ou should schedule your demo on Calendly with the same reader who took your second scrum meeting. The reader will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Project board.
 > * Make sure your README file and Project board are up-to-date reflecting the current status of your project (e.g. any changes that you have made during the project such as changes to your class diagram). Previous versions should still be visible through your commit history. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
