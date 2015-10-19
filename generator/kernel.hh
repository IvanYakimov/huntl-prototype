# ifndef KERNEL_HH
# define KERNEL_HH
# include <string>
# include <map>
# include <cvc4/cvc4.h>
# include "parser.hh"
# include "solver.hh"
# include "limit-generator.hh"

// Tell Flex the lexer’s prototype ...
# define YY_DECL \
yy::Parser::symbol_type yylex (Kernel& driver)
// ... and declare it for the parser’s sake.
YY_DECL;
// Conducting the whole scanning and parsing of Calc++.
class Kernel
{
public:
  Kernel ();
  virtual ~Kernel ();

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  
  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  
  // Whether parser traces should be generated.
  bool trace_parsing;

  // 
  bool min_max_generation;

  //
  bool if_stmt_exists;
  
  // Function data
  std::string functionName;
  SOLVER::SolutionSet solutionSet;
  std::list <std::string> paramList;
  
  // Solver;
  SOLVER::Solver solver;
  LimitGenerator limitGenerator;

  void GenerateTestHeader();
  void GenerateTestCases();
  void GenerateLimits();

  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
};
#endif // ! KERNEL_HH
