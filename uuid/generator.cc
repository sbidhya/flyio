#include<iostream>
#include <grpcpp/grpcpp.h>
#include "uuid/uuid.grpc.pb.h"

namespace flyio::uuid {
  static int start_uuid = 1;
  class GeneratorServiceImpl final : public UuidGenerator::Service {
  public:
    ::grpc::Status Generate(::grpc::ServerContext* context, const UuidRequestProto* request, UuidResponseProto* response) override {
      std::cout << "returning start uuid = " << start_uuid << std::endl;
      response->set_start_uuid(start_uuid);
      start_uuid += request->count();
      return ::grpc::Status::OK;
    }
  };
}   // flyio::uuid

int main() {
  std::string server_address("0.0.0.0:50051");
  flyio::uuid::GeneratorServiceImpl service;
  ::grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, ::grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}
