/*!
* \file	 KaiXinApp_MessagesList.cpp
* \author	 huxianxiang@GoZone
* \date	
* \brief  ������UI: ����Ϣ�б�
*
* \ref    CopyRight
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/
#include "KaiXinAPICommon.h"

#include "KaiXinAPI_MessagesList.h"

void* KaiXinAPI_MessagesList_JsonParse(char *text)
{
	cJSON *json;
	cJSON *pTemp0;
	tResponseMessagesList*  Response = new tResponseMessagesList;
	memset(Response, 0 , sizeof(tResponseMessagesList));

	json = cJSON_Parse(text);

	pTemp0 = cJSON_GetObjectItem(json,"ret");
	if (pTemp0)
	{
		Response->ret = pTemp0->valueint;	
	}

	//Success
	if(Response->ret == 1)
	{
		pTemp0 = cJSON_GetObjectItem(json, "uid");
		if(pTemp0)
		{
			if(pTemp0->valueint > 0)
				sprintf(Response->uid, "%d", pTemp0->valueint);
			else
				STRCPY_Ex(Response->uid , pTemp0->valuestring);
		}
		pTemp0 = cJSON_GetObjectItem(json, "n");
		if(pTemp0)
		{
			Response->n = pTemp0->valueint;
		}
		pTemp0 = cJSON_GetObjectItem(json, "total");
		if(pTemp0)
		{
			Response->total = pTemp0->valueint;
		}
		pTemp0 = cJSON_GetObjectItem(json, "msgs");
		if(pTemp0)
		{
			int nSize1 = 0, i = 0;
			nSize1 = cJSON_GetArraySize(pTemp0);
			Response->nSize_msgs = nSize1;
			if( nSize1 != 0 )
			{
				Response->msgs = NULL;
				Response->msgs = (MessagesList_msgs*) malloc(sizeof( MessagesList_msgs ) * nSize1 );
				memset(Response->msgs, 0 , sizeof(MessagesList_msgs) * nSize1 );
			}
			for ( i = 0; i < nSize1; i++ )
			{
				cJSON *Item1 = NULL, *pTemp1 = NULL;
				Item1 = cJSON_GetArrayItem(pTemp0,i);
				pTemp1 = cJSON_GetObjectItem(Item1, "flogo");
				if(pTemp1)
				{
					STRCPY_Ex(Response->msgs[i].flogo, pTemp1->valuestring);
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "fuid");
				if(pTemp1)
				{
					Response->msgs[i].fuid = pTemp1->valueint;
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "fnames");
				if(pTemp1)
				{
					int nSize2 = 0, j = 0;
					nSize2 = cJSON_GetArraySize(pTemp1);
					Response->msgs[i].nSize_fnames = nSize2;
					if( nSize2 != 0 )
					{
						Response->msgs[i].fnames = NULL;
						Response->msgs[i].fnames = (MessagesList_fnames*) malloc(sizeof( MessagesList_fnames ) * nSize2 );
						memset(Response->msgs[i].fnames, 0 , sizeof(MessagesList_fnames) * nSize2 );
					}
					for ( j = 0; j < nSize2; j++ )
					{
						cJSON *Item2 = NULL, *pTemp2 = NULL;
						Item2 = cJSON_GetArrayItem(pTemp1,j);
						if(Item2)
						{
							STRCPY_Ex(Response->msgs[i].fnames[j].fname, Item2->valuestring);
						}
					}
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "fuids");
				if(pTemp1)
				{
					int nSize2 = 0, j = 0;
					nSize2 = cJSON_GetArraySize(pTemp1);
					Response->msgs[i].nSize_fuids = nSize2;
					if( nSize2 != 0 )
					{
						Response->msgs[i].fuids = NULL;
						Response->msgs[i].fuids = (MessagesList_fuids*) malloc(sizeof( MessagesList_fuids ) * nSize2 );
						memset(Response->msgs[i].fuids, 0 , sizeof(MessagesList_fuids) * nSize2 );
					}
					for ( j = 0; j < nSize2; j++ )
					{
						cJSON *Item2 = NULL, *pTemp2 = NULL;
						Item2 = cJSON_GetArrayItem(pTemp1,j);
						if(Item2)
						{
							Response->msgs[i].fuids[j].uid = Item2->valueint;
						}
					}
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "mid");
				if(pTemp1)
				{
					if(pTemp1->valuedouble> 0)
						DoubleToChar(pTemp1->valuedouble, Response->msgs[i].mid);
					else
						STRCPY_Ex(Response->msgs[i].mid, pTemp1->valuestring);
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "mtype");
				if(pTemp1)
				{
					Response->msgs[i].mtype = pTemp1->valueint;
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "msgnum");
				if(pTemp1)
				{
					if(pTemp1->valueint> 0)
						sprintf(Response->msgs[i].msgnum, "%d", pTemp1->valueint);
					else
						STRCPY_Ex(Response->msgs[i].msgnum, pTemp1->valuestring);
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "unread");
				if(pTemp1)
				{
					Response->msgs[i].unread = pTemp1->valueint;
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "abscont");
				if(pTemp1)
				{
					STRCPY_Ex(Response->msgs[i].abscont, pTemp1->valuestring);
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "ctime");
				if(pTemp1)
				{
					Response->msgs[i].ctime = pTemp1->valueint;
				}
				pTemp1 = cJSON_GetObjectItem(Item1, "strctime");
				if(pTemp1)
				{
					STRCPY_Ex(Response->msgs[i].strctime, pTemp1->valuestring);
				}

			}
		}

	}
	else
	{

	}
	cJSON_Delete(json);
	return Response;
}

