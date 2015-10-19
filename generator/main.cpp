# include <iostream>
# include "kernel.hh"

int main (int argc, char *argv[])
{
  int res = 0;
  Kernel kernel;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      kernel.trace_parsing = true;
    else if (argv[i] == std::string ("-s"))
      kernel.trace_scanning = true;
    else if (argv[i] == std::string ("-m"))
      kernel.min_max_generation = true;
    else if (!kernel.parse (argv[i]))
      /*parse*/;
    else
      res = 1;
  return res;
}
