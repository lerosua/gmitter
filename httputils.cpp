/*
 * =====================================================================================
 *
 *       Filename:  httputils.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年12月09日 10时29分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include "httputils.h"
#include <stdio.h>
namespace HttpUtils
{

bool httpGet(LPCTSTR host,int nPort,LPCTSTR urlstr, LPCTSTR auth,const char* output_file_name, long* bytes_read)
{
	int nRetCode=0;
	CHttpConnection* conn=NULL;
	CInternetSession* session =new CInternetSession(_T("gmitter"),0);
	CHttpFile* pFile = NULL;
   DWORD dwHttpRequestFlags =
         INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT;
   const TCHAR szHeaders[] =
      _T("Accept: */*\r\nUser-Agent: GMITTER\r\n");

   try
   {
	   conn = session->GetHttpConnection(host,(INTERNET_PORT)nPort);
	   pFile=conn->OpenRequest(CHttpConnection::HTTP_VERB_GET,urlstr);
//			   NULL,1,NULL,NULL,dwHttpRequestFlags);
	   pFile->AddRequestHeaders(auth);
	   pFile->AddRequestHeaders(szHeaders);
	   pFile->SendRequest();

	   DWORD dwRet;
	   pFile->QueryInfoStatusCode(dwRet);

	   if(HTTP_STATUS_OK != dwRet){
		   delete conn;
		   delete pFile;
		   delete session;
		   return false;
	   }
	   

      //TCHAR sz[1024];
#if 1
      char sz[1024];
      int nRead;
      FILE *ofile = fopen( output_file_name, "wb");

      while( (nRead = pFile->Read( sz, 1024)) > 0)
         {
         fwrite( sz, 1, nRead, ofile);
         if( bytes_read)
            *bytes_read += nRead;
         }
      fclose( ofile);
#endif
      pFile->Close();
      conn->Close();
      session->Close();
                delete pFile;
                delete conn;
		delete session;
		return true;
   }
   catch(CInternetException* ex)
   {
;
		return false;
	}

}

bool httpPost(LPCTSTR host,int nPort,LPCTSTR urlstr, LPCTSTR auth,const char* post_str, char* back_str)
{
	CInternetSession* session =new CInternetSession(_T("gmitter"),0);
	try{
		CHttpConnection* conn= session->GetHttpConnection(host,(INTERNET_PORT)nPort);
		CHttpFile* pFile = conn->OpenRequest(CHttpConnection::HTTP_VERB_POST,urlstr);
		   pFile->AddRequestHeaders(auth);
                pFile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded\r\n"));
		pFile->SendRequest(NULL,0,(void*)post_str,strlen(post_str));


                DWORD dwRet;
                pFile->QueryInfoStatusCode(dwRet);
		   if(HTTP_STATUS_OK != dwRet){
			   delete conn;
			   delete pFile;
			   delete session;
			   return false;
		   }

                CString strRetBufLen;
                pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, strRetBufLen);
				char cVal[20];
				sprintf(cVal,"%s",strRetBufLen);
                long max = atol((cVal));
                if(max <= 0)
			max = pFile->GetLength();

                // Read Data
                char buf[1024];
		int len = pFile->Read(buf, 1024);
                //back_str = CString(buf, len);

                pFile->Close();
                conn->Close();
		session->Close();
                delete pFile;
                delete conn;
		delete session;

		return true;
	}
	catch(CInternetException* ex){
#if 0
                char errbuf[1024];
                ex->GetErrorMessage(errbuf, 1024);
                back_str = errbuf;
                ex->Delete();
#endif
                return false;
	}

}


bool HttpDownFIle(LPCTSTR FileURL, LPCTSTR saveFile)
{

	CInternetSession* session =new CInternetSession(_T("gmitter"),0);
	CHttpConnection* conn = NULL;
	CHttpFile* pFile = NULL;
	CString strServer,strObject;
	INTERNET_PORT wPort;

	DWORD dwType;

	  const int nTimeOut = 2000;
	  session->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
	  session->SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //重试次数
	  char* pszBuffer = NULL; 

  try
  {
   AfxParseURL(FileURL, dwType, strServer, strObject, wPort);
   conn = session->GetHttpConnection(strServer, wPort);
   pFile = conn->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
   if(pFile->SendRequest() == FALSE)
    return false;
   DWORD dwStateCode;

   pFile->QueryInfoStatusCode(dwStateCode);
   if(dwStateCode == HTTP_STATUS_OK)
   {
  HANDLE hFile = CreateFile(saveFile, GENERIC_WRITE,
    FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
    NULL);  //创建本地文件
    if(hFile == INVALID_HANDLE_VALUE)
    {
  pFile->Close();
  conn->Close();
  session->Close();
  return false;
    }
 
    char szInfoBuffer[1000];  //返回消息
    DWORD dwFileSize = 0;   //文件长度
    DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
    BOOL bResult = FALSE;
    bResult = pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
      (void*)szInfoBuffer,&dwInfoBufferSize,NULL);

    dwFileSize = atoi(szInfoBuffer);
    const int BUFFER_LENGTH = 1024 * 10;
    pszBuffer = new char[BUFFER_LENGTH];  //读取文件的缓冲
    DWORD dwWrite, dwTotalWrite;
    dwWrite = dwTotalWrite = 0;
    UINT nRead = pFile->Read(pszBuffer, BUFFER_LENGTH); //读取服务器上数据

    while(nRead > 0)
    {
  WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //写到本地文件
  dwTotalWrite += dwWrite;
  nRead = pFile->Read(pszBuffer, BUFFER_LENGTH);
    }

    delete[]pszBuffer;
    pszBuffer = NULL;
    CloseHandle(hFile);
   }
   else
   {
    delete[]pszBuffer;
    pszBuffer = NULL;
    if(pFile != NULL)
    {
  pFile->Close();
  delete pFile;
  pFile = NULL;
    }
    if(conn != NULL)
    {
  conn->Close();
  delete conn;
  conn = NULL;
    }
    session->Close();
  return false;
   }
  }
  catch(...)
  {
   delete[]pszBuffer;
   pszBuffer = NULL;
   if(pFile != NULL)
   {
    pFile->Close();
    delete pFile;
    pFile = NULL;
   }
   if(conn != NULL)
   {
    conn->Close();
    delete conn;
    conn = NULL;
   }
   session->Close();
   return false;
  }

  if(pFile != NULL)
   pFile->Close();
  if(conn != NULL)
   conn->Close();
  session->Close();
  return true;

}



	
} //end of namespace HttpUtils

