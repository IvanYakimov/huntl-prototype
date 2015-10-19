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

/* Односвязный список. Добавление ведется в начало. */

/* Операции с отдельными элементами*/
/* Инициализирует элемент типа list_item, возвращает указатель на созданный элемент */
TListItem *CreateListItem(TListItemData *data);
/* Аккуратное высвобождение памяти */
TListItem *DestroyListItem(TListItem *item, void (*FreeItem)(void *));
/* Получение данных */
TListItemData *ExtractListItemData(TListItem *item);
/* Проверяет, существует ли данный список как объект в памяти программы */
BOOL ListExists(TListItem *head);
/* Инициализирует новый список */
TListItem *InitList();

/* Присоединяет элемент к концу списка. */
TListItem *JoinListItem(TListItem *head, TListItem *joined);
/* Ведет поиск элемента в списке используя предикат. Возвращает указатель на искомый элемент. */
TListItem *SearchListItemByPredicate(TListItem *head, void *param, void * (*Predicate)(void *, void *));
/* Особождает память, занимаемую списком. Возвращает указаетль на корень. */
/* При этом элементы и их данные так же уничтожаются */
TListItem *ClearList(TListItem *head, void (*FreeItem)(void *));
/* Печатает список в выходной поток stream. */
void PrintList(TListItem *head, FILE *stream, void (*PrintItem)(FILE*, void *));
void WriteList(TListItem *head, FILE *stream, void (*WriteItem)(FILE*, void *));
/* Применяет к элементам списка функцию */
// <-- сигнатура функции --> Function(TListItemData* data, void* context);
void ProcessList(const TListItem *head, void* context, void (*Function)(TListItemData*, void*));
int GetListLength(const TListItem *head);

#endif
