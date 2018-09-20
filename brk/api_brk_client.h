/**
 * @file api_brk_client.h
 * @brief  brks client API
 * @author lizhiyong4360@gmaili.com
 * @version 1.0
 * @date 2018-09-17
 */

#ifndef API_BRK_CLIENT_H
#define API_BRK_CLIENT_H

#include "api_brk_client_type.h"

#ifdef __cplusplus
extern "C"
{
#endif 

	/**
	 * @brief  BRK_Client_Handler_Create 
	 *		创建BRK客户端SDK的句柄
	 * @param ip	服务器端的ip地址
	 * @param port  服务器端的端口号
	 *
	 * @return  返回SDK句柄 
	 */
	_API BRK_Client_Handler _APICALL BRK_HandlerCreate(char* ip, unsigned short port);

	/**
	* @brief  BRK_GetMobileVidateCode
	*		获取短信验证码
	* @param ip	服务器端的ip地址
	* @param port  服务器端的端口号
	*
	* @return  返回SDK句柄
	*/
    _API BRK_ErrorCode _APICALL BRK_GetMobileValidateCode(BRK_Client_Handler handler, const char* mobile);

	_API BRK_ErrorCode _APICALL BRK_LoginWithValidateCode(BRK_Client_Handler handler, const char* mobile, const char* code);

	_API BRK_ErrorCode _APICALL BRK_Recharge(BRK_Client_Handler handler, const char* mobile, int account);

	_API BRK_ErrorCode _APICALL BRK_GetAccountBalance(BRK_Client_Handler handler, const char* mobile, int* balance);

	_API char* _APICALL BRK_GetErrorString();

	_API void _APICALL BRK_HandlerRelease(BRK_Client_Handler handler);

#ifdef __cplusplus
}
#endif 

#endif 
