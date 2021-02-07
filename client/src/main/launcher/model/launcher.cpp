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
std::list<Match> Launcher::get_maps() const { return matches; }

unsigned char Launcher::create_match(const std::string& map_name) {
  request_new_match(map_name);
  return receive_join_match_result();
}

void Launcher::request_new_match(const std::string& map_name) {
  unsigned char packet[100];
  size_t size = pack(packet, "CIs", REQUEST_NEW_MATCH, server->get_id(),
                     map_name.c_str());
  Packet request_new_match_packet(size, packet);
  server->send(request_new_match_packet);
}

unsigned char Launcher::join_match(unsigned char match_id) {
  request_join_match(match_id);
  return receive_join_match_result();
}

void Launcher::request_join_match(unsigned char match_id) {
  unsigned char packet[JOIN_MATCH_SIZE];
  size_t size = pack(packet, "CIC", JOIN_MATCH, server->get_id(), match_id);
  Packet join_match_packet(size, packet);
  server->send(join_match_packet);
}

unsigned char Launcher::receive_join_match_result() {
  BlockingQueue<Packet>& reception_queue = server->get_reception_queue();
  Packet packet;
  reception_queue.dequeue(packet);
  if (packet.get_type() != JOIN_MATCH) {
    throw LauncherError("Failed to receive %u packet.", JOIN_MATCH);
  }

  unsigned char type;
  unsigned int client_id;
  unsigned char match_id;
  unpack(packet.get_data(), "CIC", &type, &client_id, &match_id);

  return match_id;
}

Launcher::~Launcher() {}