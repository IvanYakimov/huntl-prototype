#ifndef PARAM_VALUE_H_
#define PARAM_VALUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "list.h"

typedef enum
  {
    VT_NUMBER,
    VT_MIN,
    VT_MAX,
    VT_DEFVAL
  }TValueType;

typedef struct
{
  LIST_ITEM_DATA_HEADER
  TValueType type;
  int value;
}TValue;

// TValue *CreateValue(int value);
TValue *CreateIntValue(int value);
TValue *CreateMinValue();
TValue *CreateMaxValue();
TValue *CreateDefValue();
void FreeValue(void *param);
void PrintValue(FILE *stream, void *param_value);

typedef struct
{
  FILE* stream;
  int listLength;
  int index;
}TParamValueContext;

TParamValueContext* InitParamValueContext(FILE* stream, int listLength);
void FreeParamValueContext(TParamValueContext* context);
void GenerateParamValue(TListItemData* paramValue, void* paramContext);

typedef struct
{
  FILE* stream;
}TOutValueContext;

TOutValueContext* InitOutValueContext(FILE* stream);
void FreeOutValueContext(TOutValueContext* context);
void GenerateOutValue(TListItemData* outValue, void* outContext);



#endif /* PARAM_VALUE_H_ */
