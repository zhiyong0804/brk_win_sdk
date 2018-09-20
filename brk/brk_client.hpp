
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>

#include "BRKService.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::concurrency;

using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::brkservice;

int main(int argc, char** argv)
{
    int port = atoi(argv[2]);
    char* ip = argv[1];
    printf("client : try to connect server %s:%d. \r\n", argv[1], argv[2]);
    
    stdcxx::shared_ptr<TSocket> socket(new TSocket(ip, port));
    stdcxx::shared_ptr<TTransport> transport(new TFramedTransport(socket));
    stdcxx::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));
  
    try {
        transport->open();
    }
    catch (TException &e) 
    {
        printf("client : %s. \n", e.what());
    }

    stdcxx::shared_ptr<BRKServiceClient> client(new BRKServiceClient(protocol));

    ApiResult result;
    client->brk_get_mobile_code(result, "15200599665");

    printf("result is %s. \n", result.resultMsg.c_str());
    
    return 0;
}
