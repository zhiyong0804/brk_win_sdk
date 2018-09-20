/**
 * @file api_brk_client_type.h
 * @brief  types define
 * @author lizhiyong4360@gmail.com
 * @version 1.0
 * @date 2018-09-17
 */

#ifndef API_BRK_CLIENT_TYPES_H
#define API_BRK_CLIENT_TYPES_H

#ifdef _WIN32
#define _API __declspec(dllexport)
#define _APICALL __stdcall
#else
#define _API
#define _APICALL
#endif

typedef  void*   BRK_Client_Handler;

enum EErrorCode
{
      ERRC_SUCCESS              = 200,
	  ERRC_INVALID_MSG          = 400,
	  ERRC_INVALID_DATA         = 404,
	  ERRC_METHOD_NOT_ALLOWED   = 405,
	  ERRO_PROCCESS_FAILED      = 406,
	  ERRO_BIKE_IS_TOOK         = 407,
	  ERRO_BIKE_IS_RUNNING      = 408,
	  ERRO_BIKE_IS_DAMAGED      = 409
};

typedef  int BRK_ErrorCode;



#endif
