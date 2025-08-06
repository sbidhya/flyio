#include <iostream>
#include <grpcpp/grpcpp.h>
#include "uuid/uuid.grpc.pb.h"
#include "json/json.h"

static int reply_msg_id = 0;

int main() {
  auto channel = ::grpc::CreateChannel("localhost:50051", ::grpc::InsecureChannelCredentials());
  const int64_t request_uuid_count = 1000000;  // 1 million
  int64_t avail_uuid_count = 0;
  int64_t start_uuid = 0;

  auto request_more_uuids = [&](std::string node_id) {
    auto stub = flyio::uuid::UuidGenerator::NewStub(channel);
    ::grpc::ClientContext context;
    flyio::uuid::UuidRequestProto request;
    request.set_node_id(node_id);
    request.set_count(request_uuid_count);
    flyio::uuid::UuidResponseProto reply;
    // ::grpc::Status status = stub->Generate(&context, request, &reply);
    stub->Generate(&context, request, &reply);
    // can crash  if staus if not okay in the above call.
    return reply.start_uuid();
    };

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

    // Generate UUID
    if (avail_uuid_count == 0) {
      start_uuid = request_more_uuids(target);
      avail_uuid_count = request_uuid_count;
    }

    // Mutate root to make a valid response
    root["src"] = target;
    root["dest"] = source;
    root["body"]["in_reply_to"] = c_msg_id;
    root["body"]["type"] = msg_type + "_ok";

    root["body"]["id"] = start_uuid;
    root["body"]["msg_id"] = start_uuid;
    --avail_uuid_count;
    ++start_uuid;
    // Write the response to standard output
    std::cout << fastWriter.write(root);
  }
  return EXIT_SUCCESS;
}
