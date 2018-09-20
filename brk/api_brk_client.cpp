/**
 * @file API_PusherModule.cpp
 * @brief  
 * @author lizhiyong4360@gmail.com
 * @version 1.0.0
 * @date 2018-09-17
 */

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

#include "api_brk_client_type.h"
#include "api_brk_client.h"

#define check_parameters_2(exp1, exp2)                                             \
    do {                                                                           \
        if (exp1 || exp2)                                                          \
		{                                                                          \
			memset(g_err_str, 0, sizeof(g_err_str));                               \
			strcpy(g_err_str, "input parameters is invalid");                      \
			return ERRO_PROCCESS_FAILED;                                           \
		}                                                                          \
	} while (0)                                                                    \


typedef struct BRK_Handler_Params
{
	stdcxx::shared_ptr<TSocket> socket;
	stdcxx::shared_ptr<TTransport> transport;
	stdcxx::shared_ptr<TProtocol> protocol;
	stdcxx::shared_ptr<BRKServiceClient> client;
}BRK_Handler_Params_S;

static char g_err_str[1024] = { 0 };

_API BRK_Client_Handler _APICALL BRK_HandlerCreate(char* ip, unsigned short port)
{
	BRK_Handler_Params* handler = new BRK_Handler_Params;
	handler->socket = stdcxx::shared_ptr<TSocket >(new TSocket(ip, port));
	handler->transport = stdcxx::shared_ptr<TTransport>(new TFramedTransport(handler->socket));
	handler->protocol = stdcxx::shared_ptr<TProtocol>(new TCompactProtocol(handler->transport));

	try {
		handler->transport->open();
	}
	catch (TException &e)
	{
		memset(g_err_str, 0, sizeof(g_err_str));
		strcpy(g_err_str, "connect server failed");
		return NULL;
	}

	handler->client = stdcxx::shared_ptr<BRKServiceClient>(new BRKServiceClient(handler->protocol));

	return (BRK_Client_Handler)(handler);
}

_API BRK_ErrorCode _APICALL BRK_GetMobileValidateCode(BRK_Client_Handler handler, const char* mobile)
{
	check_parameters_2((handler == NULL), (((BRK_Handler_Params*)handler)->client == NULL) );

	::brkservice::ApiResult result;
	((BRK_Handler_Params*)handler)->client->brk_get_mobile_code(result, mobile);

	memset(g_err_str, 0, sizeof(g_err_str));
	strcpy(g_err_str, result.resultMsg.c_str());
	return result.resultCode;
}

_API BRK_ErrorCode _APICALL BRK_LoginWithValidateCode(BRK_Client_Handler handler, const char* mobile, const char* code)
{
	check_parameters_2((handler == NULL), (((BRK_Handler_Params*)handler)->client == NULL));

	::brkservice::ApiResult result;
	((BRK_Handler_Params*)handler)->client->brk_login(result, mobile, code);

	memset(g_err_str, 0, sizeof(g_err_str));
	strcpy(g_err_str, result.resultMsg.c_str());

	return result.resultCode;
}

_API char* _APICALL BRK_GetErrorString()
{
	return g_err_str;
}

_API void _APICALL BRK_HandlerRelease(BRK_Client_Handler handler)
{
	if (handler == NULL)
	{
		((BRK_Handler_Params*)handler)->transport.reset();
		((BRK_Handler_Params*)handler)->protocol.reset();
		((BRK_Handler_Params*)handler)->socket.reset();
		((BRK_Handler_Params*)handler)->client.reset();

		delete handler;
		handler = NULL;
	}
}

_API BRK_ErrorCode _APICALL BRK_Recharge(BRK_Client_Handler handler, const char* mobile, int account)
{
	check_parameters_2((handler == NULL), (((BRK_Handler_Params*)handler)->client == NULL));

	::brkservice::ApiResult result;
	((BRK_Handler_Params*)handler)->client->brk_recharge(result, mobile, account);

	memset(g_err_str, 0, sizeof(g_err_str));
	strcpy(g_err_str, result.resultMsg.c_str());
	return result.resultCode;
}

_API BRK_ErrorCode _APICALL BRK_GetAccountBalance(BRK_Client_Handler handler, const char* mobile, int* balance)
{
	check_parameters_2((handler == NULL), (((BRK_Handler_Params*)handler)->client == NULL));
}
