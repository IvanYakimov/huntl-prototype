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

#include "scanner.h"

void lprint(char* token, char* type, int line)
{
  printf("token: %s\t type: %s\t line: %d\n", token, type, line);
}

void lerror(char* text, int line)
{
  printf("error in:\"%s\" line: %d\n", text, line);
}

BOOL scan(char* filename, FILE* *scanner_in, int (*scanner)(void))
{
  FILE* infile; /* Структура для входного файла. */
  /* Проверка на правильность запуска лексического анализатора
   * из командной строки.*/

  /* Первый параметр командной строки – имя входного файла */
  infile = fopen(filename, "r");
  if (NULL == infile)
    {
      printf("Can't open file: %s\n", filename);
      return FALSE;
    }
  *scanner_in = infile;
  scanner();
  fclose(infile);
  return TRUE;
}
