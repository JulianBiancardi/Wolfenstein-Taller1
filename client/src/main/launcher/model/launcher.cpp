#include "../include/launcher.h"

#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/packets/packing.h"
#include "iostream"
#include "launcher_error.h"

#define MAP_NAME_MAX_SIZE 64  // TODO Move somewhere where it belongs

Launcher::Launcher(Server* server) : server(server), matches() {
  update_matches();
}

void Launcher::update_matches() {
  matches.clear();
  request_matches();
  receive_matches();
  notify();
}

void Launcher::request_matches() {
  unsigned char packet[REQUEST_MATCHES_SIZE];
  size_t size = pack(packet, "CI", REQUEST_MATCHES, server->get_id());
  Packet request_matches_packet(size, packet);
  server->send(request_matches_packet);
}

void Launcher::receive_matches() {
  unsigned char match_amount = get_amount_of_matches();
  for (unsigned char i = 0; i < match_amount; i++) {
    receive_match();
  }
}

unsigned char Launcher::get_amount_of_matches() {
  BlockingQueue<Packet>& reception_queue = server->get_reception_queue();
  Packet packet;
  reception_queue.dequeue(packet);

  if (packet.get_type() != MATCH_AMOUNT ||
      packet.get_size() != MATCH_AMOUNT_SIZE) {
    throw LauncherError("Failed to receive %u packet.", MATCH_AMOUNT);
  }

  unsigned char type;
  unsigned int client_id;
  unsigned char match_amount;
  unpack(packet.get_data(), "CIC", &type, &client_id, &match_amount);

  return match_amount;
}

void Launcher::receive_match() {
  BlockingQueue<Packet>& reception_queue = server->get_reception_queue();
  Packet packet;
  reception_queue.dequeue(packet);

  if (packet.get_type() != MATCH_DATA) {
    throw LauncherError("Failed to receive %u packet.", MATCH_DATA);
  }

  unsigned char type;
  unsigned int client_id;
  unsigned char match_id;
  char map_name[MAP_NAME_MAX_SIZE];
  unsigned char players_joined;
  unsigned char players_total;
  unsigned char status;
  unpack(packet.get_data(), "CICsCCC", &type, &client_id, &match_id, map_name,
         &players_joined, &players_total, &status);

  matches.push_back(
      Match(match_id, map_name, players_joined, players_total, status));
}

std::list<Match> Launcher::get_matches() const { return matches; }

Launcher::~Launcher() {}