#include "myLinkList.h"
#include <stdio.h>

LIST_HANDLE LIST_Init(int _s32NodeDataSize);
int LIST_Destroy(LIST_HANDLE _hndList);
int LIST_AddToHead(LIST_HANDLE _hndList, void* _pData, int _s32DataSize);
int LIST_AddToTail(LIST_HANDLE _hndList, void* _pData, int _s32DataSize);
int LIST_Delete(LIST_HANDLE _hndList, void* pData);
int LIST_DeleteHead(LIST_HANDLE _hndList);
int LIST_DeleteTail(LIST_HANDLE _hndList);
int LIST_Clear(LIST_HANDLE _hndList);
int LIST_GetCnt(LIST_HANDLE _hndList);
void* LIST_GetHead(LIST_HANDLE _hndList);
void* LIST_GetTail(LIST_HANDLE _hndList);
void* LIST_GetNextNode(LIST_HANDLE _hndList, void* pData);
void* LIST_GetPrevNode(LIST_HANDLE _hndList, void* pData);
int LIST_IsEmpty(LIST_HANDLE _hndList);


static LIST_NODE_S* LIST_LookUp(LIST_HANDLE _hndList, void* pData)
{
    LIST_S* pstList = (LIST_S*)_hndList;
    LIST_NODE_S* tmp = pstList->pstHead;
    while (NULL != tmp)
    {
        if (tmp->pData == pData)
        {
            return tmp;
        }
        tmp = tmp->pstNext;
    }
    ERR("the node is not exist.\n");

    return NULL;
}

LIST_HANDLE LIST_Init(int s32NodeDataSize)
{
    CHECK(s32NodeDataSize > 0, NULL, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)COMMON_Malloc(sizeof(LIST_S));
    CHECK(NULL != pstList, NULL, "failed to malloc %d\n", sizeof(LIST_S));

    memset(pstList, 0, sizeof(LIST_S));
    pstList->s32NodeDataSize = s32NodeDataSize;
    pstList->s32Cnt = 0;
    pstList->pstHead = NULL;
    pstList->pstTail = NULL;
    pstList->u32MagicNumer = LIST_MAGIC_NUM;

    return (LIST_HANDLE)pstList;
}

int LIST_Destroy(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");

    int ret = -1;
    ret = LIST_Clear(_hndList);
    CHECK(!ret, ret, "error: ret is %d\n", ret);

    ret = COMMON_Free(_hndList);
    CHECK(!ret, ret, "error: ret is %d\n", ret);

    return ret;
}

int LIST_AddToHead(LIST_HANDLE _hndList, void* pData, int DataSize)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");
    CHECK(NULL != pData, -1, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)_hndList;
    CHECK(pstList->s32NodeDataSize == DataSize, -1, "invalid parameter.\n");

    LIST_NODE_S* pstNewNode = (LIST_NODE_S*)COMMON_Malloc(sizeof(LIST_NODE_S) + pstList->s32NodeDataSize);
    CHECK(NULL != pstNewNode, -1, "failed to malloc %d\n", sizeof(LIST_NODE_S) + pstList->s32NodeDataSize);

    memset(pstNewNode, 0, sizeof(LIST_NODE_S) + pstList->s32NodeDataSize);
    pstNewNode->pData = (void*)(pstNewNode+1);
    memcpy(pstNewNode->pData, pData, pstList->s32NodeDataSize);
    if (NULL == pstList->pstTail && NULL == pstList->pstHead)
    {
        pstList->pstHead = pstNewNode;
        pstList->pstTail = pstNewNode;
        pstNewNode->pstNext = NULL;
        pstNewNode->pstPrev = NULL;
    }
    else
    {
        pstList->pstHead->pstPrev = pstNewNode;
        pstNewNode->pstNext = pstList->pstHead;
        pstList->pstHead = pstNewNode;
        pstNewNode->pstPrev = NULL;
    }
    pstList->s32Cnt++;

    return 0;
}

int LIST_AddToTail(LIST_HANDLE _hndList, void* pData, int DataSize)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");
    CHECK(NULL != pData, -1, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)_hndList;
    CHECK(pstList->s32NodeDataSize == DataSize, -1, "invalid parameter.\n");

    LIST_NODE_S* pstNewNode = (LIST_NODE_S*)COMMON_Malloc(sizeof(LIST_NODE_S) + pstList->s32NodeDataSize);
    CHECK(NULL != pstNewNode, -1, "failed to malloc %d\n", sizeof(LIST_NODE_S) + pstList->s32NodeDataSize);

    memset(pstNewNode, 0, sizeof(LIST_NODE_S) + pstList->s32NodeDataSize);
    pstNewNode->pData = (void*)(pstNewNode+1);
    memcpy(pstNewNode->pData, pData, pstList->s32NodeDataSize);
    if (NULL == pstList->pstTail && NULL == pstList->pstHead)
    {
        pstList->pstHead = pstNewNode;
        pstList->pstTail = pstNewNode;
        pstNewNode->pstNext = NULL;
        pstNewNode->pstPrev = NULL;
    }
    else
    {
        pstList->pstTail->pstNext = pstNewNode;
        pstNewNode->pstPrev = pstList->pstTail;
        pstList->pstTail = pstNewNode;
        pstNewNode->pstNext = NULL;
    }
    pstList->s32Cnt++;

    return 0;
}

int LIST_Delete(LIST_HANDLE _hndList, void* pData)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");
    CHECK(NULL != pData, -1, "invalid parameter.\n");

    int ret = -1;
    LIST_S* pstList = (LIST_S*)_hndList;
    LIST_NODE_S* pstFind = LIST_LookUp(pstList, pData);
    if (NULL != pstFind)
    {
        if (pstList->s32Cnt == 1)
        {
            pstList->pstHead = NULL;
            pstList->pstTail = NULL;
        }
        else
        {
            if (pstFind == pstList->pstHead)
            {
                pstList->pstHead->pstNext->pstPrev = NULL;
                pstList->pstHead = pstList->pstHead->pstNext;
            }
            else if (pstFind == pstList->pstTail)
            {
                pstList->pstTail->pstPrev->pstNext = NULL;
                pstList->pstTail = pstList->pstTail->pstPrev;
            }
            else
            {
                pstFind->pstPrev->pstNext = pstFind->pstNext;
                pstFind->pstNext->pstPrev = pstFind->pstPrev;
            }
        }

        ret = COMMON_Free(pstFind);
        CHECK(!ret, ret, "error: ret is %d\n", ret);

        pstList->s32Cnt--;
    }

    return ret;
}

int LIST_DeleteHead(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");

    int ret = -1;
    LIST_S* pstList = (LIST_S*)_hndList;
    if (NULL != pstList->pstHead)
    {
        if (pstList->s32Cnt == 1) // only one node
        {
            ret = COMMON_Free(pstList->pstHead);
            CHECK(!ret, ret, "error: ret is %d\n", ret);

            pstList->pstHead = NULL;
            pstList->pstTail = NULL;
        }
        else
        {
            LIST_NODE_S* tmp = pstList->pstHead;
            pstList->pstHead->pstNext->pstPrev = NULL;
            pstList->pstHead = pstList->pstHead->pstNext;

            ret = COMMON_Free(tmp);
            CHECK(!ret, ret, "error: ret is %d\n", ret);
        }
        pstList->s32Cnt--;
        //DBG("delete head node success.list size: %d\n", pstList->s32Cnt);
    }

    return ret;
}

int LIST_DeleteTail(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");

    int ret = -1;
    LIST_S* pstList = (LIST_S*)_hndList;
    if (NULL != pstList->pstTail)
    {
        if (pstList->s32Cnt == 1) // only one node
        {
            ret = COMMON_Free(pstList->pstTail);
            CHECK(!ret, ret, "error: ret is %d\n", ret);

            pstList->pstHead = NULL;
            pstList->pstTail = NULL;
        }
        else
        {
            LIST_NODE_S* tmp = pstList->pstTail;
            pstList->pstTail->pstPrev->pstNext = NULL;
            pstList->pstTail = pstList->pstTail->pstPrev;

            ret = COMMON_Free(tmp);
            CHECK(!ret, ret, "error: ret is %d\n", ret);
        }
        pstList->s32Cnt--;
        //DBG("delete tail node success.list size: %d\n", pstList->s32Cnt);
    }

    return ret;
}

int LIST_Clear(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");

    int ret = -1;
    while (LIST_GetCnt(_hndList) > 0)
    {
        ret = LIST_DeleteTail(_hndList);
        CHECK(!ret, ret, "error: ret is %d\n", ret);
    }

    return ret;
}

int LIST_GetCnt(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)_hndList;

    return pstList->s32Cnt;
}

void* LIST_GetHead(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, NULL, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)_hndList;

    return (pstList->pstHead) ? pstList->pstHead->pData : NULL;
}

void* LIST_GetTail(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, NULL, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)_hndList;

    return (pstList->pstTail) ? pstList->pstTail->pData : NULL;
}

int LIST_IsEmpty(LIST_HANDLE _hndList)
{
    CHECK(NULL != _hndList, -1, "invalid parameter.\n");

    LIST_S* pstList = (LIST_S*)_hndList;

    return (pstList->s32Cnt == 0);
}

void* LIST_GetNextNode(LIST_HANDLE _hndList, void* pData)
{
    CHECK(NULL != _hndList, NULL, "invalid parameter.\n");
    CHECK(NULL != pData, NULL, "invalid parameter.\n");

    LIST_NODE_S* pstFind = LIST_LookUp(_hndList, pData);
    if (NULL != pstFind && NULL != pstFind->pstNext)
    {
        return pstFind->pstNext->pData;
    }

    return NULL;
}

void* LIST_GetPrevNode(LIST_HANDLE _hndList, void* pData)
{
    CHECK(NULL != _hndList, NULL, "invalid parameter.\n");
    CHECK(NULL != pData, NULL, "invalid parameter.\n");

    LIST_NODE_S* pstFind = LIST_LookUp(_hndList, pData);
    if (NULL != pstFind && NULL != pstFind->pstPrev)
    {
        return pstFind->pstPrev->pData;
    }

    return NULL;
}
