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

#endif
