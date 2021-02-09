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
#define JOIN_MATCH_SIZE 4

// Used to spawn a player on match start or as respawn
#define SPAWN_PLAYER 7
#define SPAWN_PLAYER_SIZE 5

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

//==============================
#define GRAB 9
#define GRAB_SIZE 9

#define DOOR_INTERACTION 12
#define DOOR_INTERACTION_SIZE 10

#define CLOSE_DOOR 13
#define CLOSE_DOOR_SIZE 5

#define ROCKET_ADD 14
#define ROCKET_ADD_SIZE 5

#define ROCKET_MOVE 15
#define ROCKET_MOVE_SIZE 4

#define ROCKET_EXPLODE 16
#define ROCKET_EXPLODE_SIZE 18

#define GAME_OVER 17
#define GAME_OVER_SIZE 2

#endif
