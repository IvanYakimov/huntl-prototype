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

#include "value.h"

TValue *CreateIntValue(int value)
{
  TValue *result = (TValue *)malloc(sizeof(TValue));
  result->type = VT_NUMBER;
  result->value = value;
  return result;
}

TValue *CreateMinValue()
{
  TValue *result = (TValue *)malloc(sizeof(TValue));
  result->type = VT_MIN;
  return result;
}

TValue *CreateMaxValue()
{
  TValue *result = (TValue *)malloc(sizeof(TValue));
  result->type = VT_MAX;
  return result;
}

TValue *CreateDefValue()
{
  TValue *result = (TValue *)malloc(sizeof(TValue));
  result->type = VT_DEFVAL;
  return result;
}

void FreeValue(void *item)
{
  TValue *param = (TValue *)item;
  if (param)
    free(param);
}

void PrintValue(FILE *stream, void *item)
{
  TValue *param = (TValue *)item;
  if (param)
    fprintf(stream, "%d\t", param->value);
}

TParamValueContext* InitParamValueContext(FILE* stream, int listLength)
{
  TParamValueContext* context = (TParamValueContext *) malloc( sizeof(TParamValueContext) );
  context->stream = stream;
  context->listLength = listLength;
  context->index = 0;
  return context;
}

void FreeParamValueContext(TParamValueContext* context)
{
  if (context)
    {
      free(context);
    }
}

void GenerateParamValue(TListItemData* paramData, void* paramContext)
{
  TParamValueContext *context = (TParamValueContext *) paramContext;
  TValue *paramValue = (TValue *) paramData;
  switch (paramValue->type)
    {
    case VT_NUMBER:
      fprintf(context->stream, "%d", paramValue->value);
      break;
    case VT_MIN:
      fprintf(context->stream, "INT_MIN");
      break;
    case VT_MAX:
      fprintf(context->stream, "INT_MAX");
      break;
    case VT_DEFVAL:
      fprintf(context->stream, "%d", 0);
      break;
    }
  if (++context->index < context->listLength)
    fprintf(context->stream, ", ");
}

TOutValueContext* InitOutValueContext(FILE* stream)
{
  TOutValueContext* context = (TOutValueContext *) malloc (sizeof (TOutValueContext) );
  context->stream = stream;
  return context;
}

void FreeOutValueContext(TOutValueContext* context)
{
  if (context)
    free( context );
}

void GenerateOutValue(TListItemData* data, void* outContext)
{
  TValue* value = (TValue *) data;
  TOutValueContext* context = (TOutValueContext *) outContext;
  switch (value->type)
    {
    case VT_NUMBER:
      fprintf(context->stream, "%d", value->value);
      break;
    case VT_MIN:
      fprintf( context->stream, "INT_MIN");
      break;
    case VT_MAX:
      fprintf( context->stream, "INT_MAX");
      break;
    case VT_DEFVAL:
      fprintf( context->stream, "%d", 0);
      break;
    }
}


























