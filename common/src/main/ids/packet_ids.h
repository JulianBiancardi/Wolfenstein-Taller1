#ifndef PACKET_IDS_H
#define PACKET_IDS_H

#define SIZE_SIZE 2

// Packet types
#define END_OF_CONNECTION 0  // To end the connection
#define END_OF_CONNECTION_SIZE 3

#define START_OF_CONNECTION 1  // To notify the client his ID
#define START_OF_CONNECTION_SIZE 3

#define REQUEST_MATCHES 2  // To request matches information during launcher
#define REQUEST_MATCHES_SIZE 3

#define MATCH_AMOUNT 3  // To notify how many matches are available
#define MATCH_AMOUNT_SIZE 4

#define MATCH_DATA 4  // To send general data about a match
// Undefined size

#define REQUEST_NEW_MATCH 5  // To create a new match on the client
// Undefined size

#define JOIN_MATCH 6  // Used to join a match and notify the result
#define JOIN_MATCH_SIZE 4

#define GRAB 5  // Player grabbed an item
#define GRAB_SIZE 6

#endif
