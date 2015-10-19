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

#include "program.h"

int main(int argc, char* argv[])
{
  char fileName[BUFSIZ];
  if (argc != 2)
    FatalError("incorrect number of arguments, expected file name");
  strcpy (fileName, argv[1]);
  InitGlobalScope();

  if (!parse(fileName, dtl_parse))
    FatalError("can't parse input file");

#ifdef STD_OUT
  GenerateFile(stdout);
#else
  GenerateFile(GetOutputFile());
  CloseOutputFile();
#endif
	
  ClearGlobalScope();
  return EXIT_SUCCESS;
}
