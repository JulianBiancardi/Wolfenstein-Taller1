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

// Used to start a match being the host or notify the rest
#define MATCH_START 7
#define MATCH_START_SIZE 0  // TODO Define size

// Used to move a player
#define MOVEMENT 8
#define MOVEMENT_SIZE 5

// Used to rotate a player
#define ROTATION 9
#define ROTATION_SIZE 5

//==============================
#define MOVE 7
#define MOVE_SIZE 7

#define ROTATE 8
#define ROTATE_SIZE 7

#define GRAB 9
#define GRAB_SIZE 9

#define SHOT 10
#define SHOT_SIZE 8

#define CHANGE_GUN 11
#define CHANGE_GUN_SIZE 7

#define DOOR_INTERACTION 12
#define DOOR_INTERACTION_SIZE 10

#define GAME_OVER 13
#define GAME_OVER_SIZE 2

#endif
