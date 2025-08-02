
#include<iostream>
#include<string>
#include "json/json.h"

static int reply_msg_id = 0;

int main(int argc, char* argv[]) {
  std::string line;
  Json::Value root;
  Json::Reader reader;
  Json::FastWriter fastWriter;

  while (std::getline(std::cin, line)) {
    root.clear();
    if (!reader.parse(line, root)) {
      continue;
    };

    // Read the request fields
    std::string source = root["src"].asString();
    std::string target = root["dest"].asString();
    int c_msg_id = root["body"]["msg_id"].asInt();
    std::string msg_type = root["body"]["type"].asString();

    // Mutate root to make a valid response
    root["src"] = target;
    root["dest"] = source;
    root["body"]["in_reply_to"] = c_msg_id;
    root["body"]["type"] = msg_type + "_ok";

    ++reply_msg_id;
    root["id"] = reply_msg_id;
    root["body"]["msg_id"] = reply_msg_id;
    // Write the response to standard output
    std::cout << fastWriter.write(root);
  }
  return EXIT_SUCCESS;
}
