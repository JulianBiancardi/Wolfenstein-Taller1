#ifndef CLIENT_H
#define CLIENT_H

class Client {
 private:
 public:
  Client();
  ~Client();

  void run_client(int argc, char** argv);
};

#endif