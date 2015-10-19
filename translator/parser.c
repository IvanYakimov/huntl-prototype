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

#include "parser.h"

#include <string.h>

BOOL parse(char* filename, int (*parser)(void))
{
  if (strcmp(filename, "-") == 0)
    ;
  else if (freopen(filename, "r", stdin) == NULL)
    {
      fprintf(stderr, "can't reopen stdin");
      return FALSE;
    }
  parser();
  return TRUE;
}
