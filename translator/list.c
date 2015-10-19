/*
Part of GenTesc translator.
Copyright (C) 2015 Ivan Yakimov, e-mail: ivan.yakimov.sibfu@yandex.ru

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "list.h"
#include <stdlib.h>
#include <string.h>

TListItem *InitList()
{
  return NULL;
}

TListItem *ListTail(TListItem *head)
{
  TListItem *cur = head;
  if (!head)
    return NULL;
  while (cur->next)
    cur = cur->next;
  return cur;
}

TListItem *CreateListItem(TListItemData *data)
{
  TListItem *newItem = (TListItem *)malloc(sizeof(TListItem));
  newItem->next = NULL;
  newItem->data = data;
  return newItem;
}

TListItemData *ExtractListItemData(TListItem *item)
{
  if (item != NULL)
    return item->data;
  else
    return NULL;
}

TListItem *DestroyListItem(TListItem *item, void (*FreeItem)(void *))
{
  if(item != NULL)
    {
      FreeItem(item->data);
      free(item);
      item = NULL;
    }
  return NULL;
}

BOOL ListExists(TListItem *head)
{
  if (head != NULL)
    return TRUE;
  else
    return FALSE;
}

TListItem *JoinListItem(TListItem *head, TListItem *joined)
{
  if (joined == NULL)
    {
      return head;
    }

  if (head == NULL)
    {
      head = joined;
    }
  else
    {
      ListTail(head)->next = joined;
    }
  return head;
}

TListItem *SearchListItemByPredicate(TListItem *head, void *param, void * (*Predicate)(void *, void *))
{
  TListItem *cur = head;
  while(cur)
    {
      if(Predicate(cur->data, param))
	return cur;
      cur = cur->next;
    }
  return NULL;
}

TListItem *ClearList(TListItem *head, void (*FreeItem)(void *))
{
  TListItem *cur = NULL;

  if(head == NULL)
    return head;

  cur = head;
  while(cur != NULL)
    {
      head = cur;
      cur = cur->next;
      head = DestroyListItem(head, FreeItem);
    }
  return head;
}

void PrintList(TListItem *head, FILE *stream, void (*PrintItem)(FILE *, void *))
{
  TListItem *cur = head;
  while(cur)
    {
      PrintItem(stream, cur->data);
      cur = cur->next;
    }
  if(head == NULL)
    fprintf(stream, "#");
}

void WriteList(TListItem *head, FILE *stream, void (*WriteItem)(FILE *, void *))
{
  TListItem *cur = head;
  while(cur)
    {
      WriteItem(stream, cur->data);
      cur = cur->next;
    }
}


void ProcessList(const TListItem *head, void* context, void (*Function)(TListItemData*, void*))
{
  TListItem *cur = head;
  while(cur)
    {
      Function(cur->data, context);
      cur = cur->next;
    }
}

int GetListLength(const TListItem *head)
{
  int length = 0;
  TListItem *cur = head;
  while(cur)
    {
      cur = cur->next;
      length++;
    }
  return length;
}
