#ifndef PACKET_IDS_H
#define PACKET_IDS_H

#define SIZE_SIZE 2

/* Packet Types - Declaration and Explanation
 * ------------------------------------------
 * Comment on cases of use
 * Name and ID
 * Size
 * ------------------------------------------
 */

// To end the connection
#define END_OF_CONNECTION 0
#define END_OF_CONNECTION_SIZE 3

// To notify the client his ID
#define START_OF_CONNECTION 1
#define START_OF_CONNECTION_SIZE 3

// To request matches information during launcher
#define REQUEST_MATCHES 2
#define REQUEST_MATCHES_SIZE 3

// To notify how many matches are available
#define MATCH_AMOUNT 3
#define MATCH_AMOUNT_SIZE 4

// To send general data about a match
#define MATCH_DATA 4
// Undefined size

// To create a new match on the client
#define REQUEST_NEW_MATCH 5
// Undefined size

// Used to join a match and notify the result
#define JOIN_MATCH 6
#define JOIN_MATCH_SIZE 5

// Used to spawn a player on match start or as respawn
#define SPAWN_PLAYER 7
#define SPAWN_PLAYER_SIZE 6

// Used to start a match being the host or notify the rest
#define MATCH_START 8
#define MATCH_START_SIZE 4

// Used to move a player
#define MOVEMENT 9
#define MOVEMENT_SIZE 5

// Used to rotate a player
#define ROTATION 10
#define ROTATION_SIZE 5

// Used to shoot the gun
#define SHOT 11
#define SHOT_SIZE 7

// Used to change the gun
#define CHANGE_GUN 12
#define CHANGE_GUN_SIZE 5

// Used to grab items on the client
#define GRAB 13
#define GRAB_SIZE 5

// Used to add items on the client
#define ADD_ITEM 14
#define ADD_ITEM_SIZE 6

/* Used to add a rocket on the client. */
#define ROCKET_ADD 15
#define ROCKET_ADD_SIZE 3

/* Used to move a rocket. */
#define ROCKET_MOVE 16
#define ROCKET_MOVE_SIZE 6

/* Used to explode a rocket. */
#define ROCKET_EXPLODE 17
#define ROCKET_EXPLODE_MAX_PLAYERS 5
#define ROCKET_EXPLODE_SIZE 3 + ROCKET_EXPLODE_MAX_PLAYERS * 3

/* Used to attempt to open a doorway. */
#define DOORWAY_INTERACTION 18
#define DOORWAY_INTERACTION_SIZE 4

/* Used to open or close a door on the client. */
#define DOOR_UPDATE 19
#define DOOR_UPDATE_SIZE 9

/* Used to close a door on the server. */
#define CLOSE_DOOR 20
#define CLOSE_DOOR_SIZE 6

#define GAME_OVER 21
#define GAME_OVER_SIZE 3

#define EXIT_MATCH 22
#define EXIT_MATCH_SIZE 4

#endif
