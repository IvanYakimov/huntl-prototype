#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include "definitions.h"
#include <stdarg.h>

#define LIST_ITEM_DATA_HEADER	char name[NAME_LENGTH];

// "Abstract" parent structure
typedef struct
{
	//	LIST_ITEM_DATA_HEADER
	char name[NAME_LENGTH];
	// child body
}TListItemData;

typedef TListItemData TListItemDataName;

/*	// TChild : TListItemData
 *  typedef struct
 *  {
 *  	LIST_ITEM_DATA_HEADER
 *  	// child's data
 *  }TListItemDataChild
 */

typedef struct
{
	struct TListItem *next;
	TListItemData *data;
}TListItem;

/* ����������� ������. ���������� ������� � ������. */

/* �������� � ���������� ����������*/
/* �������������� ������� ���� list_item, ���������� ��������� �� ��������� ������� */
TListItem *CreateListItem(TListItemData *data);
/* ���������� ������������� ������ */
TListItem *DestroyListItem(TListItem *item, void (*FreeItem)(void *));
/* ��������� ������ */
TListItemData *ExtractListItemData(TListItem *item);
/* ���������, ���������� �� ������ ������ ��� ������ � ������ ��������� */
BOOL ListExists(TListItem *head);
/* �������������� ����� ������ */
TListItem *InitList();

/* ������������ ������� � ����� ������. */
TListItem *JoinListItem(TListItem *head, TListItem *joined);
/* ����� ����� �������� � ������ ��������� ��������. ���������� ��������� �� ������� �������. */
TListItem *SearchListItemByPredicate(TListItem *head, void *param, void * (*Predicate)(void *, void *));
/* ���������� ������, ���������� �������. ���������� ��������� �� ������. */
/* ��� ���� �������� � �� ������ ��� �� ������������ */
TListItem *ClearList(TListItem *head, void (*FreeItem)(void *));
/* �������� ������ � �������� ����� stream. */
void PrintList(TListItem *head, FILE *stream, void (*PrintItem)(FILE*, void *));
void WriteList(TListItem *head, FILE *stream, void (*WriteItem)(FILE*, void *));
/* ��������� � ��������� ������ ������� */
// <-- ��������� ������� --> Function(TListItemData* data, void* context);
void ProcessList(const TListItem *head, void* context, void (*Function)(TListItemData*, void*));
int GetListLength(const TListItem *head);

#endif
