#ifndef GLOBAL_SCOPE_H_
#define GLOBAL_SCOPE_H_

#include <stdio.h>
#include "definitions.h"
#include "list.h"
#include "suite.h"

#define TARGET_FILE_HEADER		"target.h"
#define TARGET_FILE_SOURCE		"target.c"

/* Доступ к глобальным переменным: */
const TListItem* GetFunctionList();
void SetFunctionList(TListItem *header);

const TListItem* GetTestSuiteList();
void SetTestSuiteList(TListItem *header);

BOOL OpenOutputFile(char *fileName);
const FILE* GetOutputFile();
BOOL CloseOutputFile();

void InitGlobalScope();
void ClearGlobalScope();

void FatalError(char *s, ...);
void Error(char *s, ...);

#endif /* GLOBAL_SCOPE_H_ */
