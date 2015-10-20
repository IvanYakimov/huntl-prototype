/*
STM-Solver API.
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

# include "solver.hh"

namespace SOLVER
{
  using std::string;
  using std::stringstream;
  using std::ostream;
  using std::cout;
  using std::endl;
  using std::map;
  using std::set;
  using std::list;
  using std::vector;
  using std::transform;
  using std::pair;
  using namespace CVC4;

  ostream &operator<<(ostream &stream, VarList &varList)
  {
    for (VarList::iterator i = varList.begin ();
	 i != varList.end (); i++)
      cout << *i << endl;
    return stream;
  }

  ostream &operator<<(ostream &stream, Solution &solution)
  {
    for (Solution::iterator i = solution.begin();
	 i != solution.end(); i++)
      {
	stream << i->first << ": ";
	stream << i->second;
	stream << endl;
      }
    return stream;
  }

  ostream &operator<<(ostream &stream, SolutionSet &solutionSet)
  {
    for (SolutionSet::iterator i = solutionSet.begin();
	 i != solutionSet.end(); i++)
      {
	Solution solution = *i;
	stream << solution;
      }
    return stream;
  }

  void Solver::GenerateTestCases( SolutionSet solutionSet,
				  std::list <std::string> paramList )
  {
    // GO AROUND THE SOLUTION SET:
    // For each solution in given solution set
    for (SolutionSet::iterator solution_ptr = solutionSet.begin();
	 solution_ptr != solutionSet.end(); solution_ptr++)
      {
	// GO AROUND THE PARAMETER LIST:
	// For each parameter in formal param list of function
	for (list <string>::iterator param_ptr = paramList.begin ();
	     param_ptr != paramList.end (); /*param_ptr++ placed below*/)
	  {
	    // GENERATE VALUE:
	    // If parameter belongs to the solution ...
	    if (solution_ptr->find (*param_ptr) != solution_ptr->end ())
	      {
		// ... generate number:
		cout << (*solution_ptr)[*param_ptr];
	      }
	    // Else ...
	    else
	      {
		// ... generate special symbol:
		cout << "_";
	      }

	    // Handle comma separation
	    if (++param_ptr != paramList.end ())
	      cout << ", ";
	    else
	      cout << " ";

	    /*
	    // For each value in the current solution of given solution set
	    for (Solution::iterator value_ptr = solution_ptr->begin();
		 value_ptr != solution_ptr->end(); )
	      {
		cout << value_ptr->second;
		if (++value_ptr != solution_ptr->end())
		  cout << ", ";
	      }
	    */
	  }
	cout << " => ?;" << endl;
      }	  
  }

  //--------------------------------------------------
  // Engine

  SolutionSet Solver::GetSolutionSet(Expr formula)
  {
    SolutionSet solutionSet;

    // 0. Generate Symbol Table

    // 1. Obtain true-branch solution
    solutionSet.push_back( GetSolution(formula) );

    // 2. Obtain false-branch solution (negated formula)
    Expr negated = NegateFormula(formula);
    solutionSet.push_back( GetSolution(negated) );
    
    return solutionSet;
  }

  Expr Solver::NegateFormula(Expr formula)
  {
    return formula.notExpr();
  }

  Solution Solver::GetSolution( Expr formula )
  {
    Solution solution;
    // Push user context
    smtEngine->push();
    
    try
      {
	// Assert formula (its solution should be finded)
	smtEngine->assertFormula(formula);
	// Check formula satisfiability
	if ( (smtEngine->checkSat(formula)).isSat() != Result::SAT )
	  return solution;

	// Generate variable list
	VarList varList;
	GenerateVarList( formula, varList );

	// For each x in variable list getValue(x)
	for ( VarList::iterator var = varList.begin();
	     var != varList.end(); var++ )
	  {
	    solution[var->toString()] = GetValue(*var);
	  }
      }
    catch ( CVC4::Exception &e )
      {
	cout << e.toString();
	// cout << "// error: can't find predicate solution" << endl;
      }
    catch (...)
      {
	cout << "// error: unrecognized" << endl;
      }
    
    // Pop user context
    smtEngine->pop();
    
    return solution;
  }

  int Solver::GetValue(Expr symbol)
  {  
    // comment: at the moment of code writing implementatin the
    // getConst<CVC4::Integer> function wasn't found
    Rational value = smtEngine->getValue(symbol).getConst<Rational>();
    // We assume that the value has no denominator
    Integer numerator = value.getNumerator();
    long solution = numerator.getLong();
    
    return (int) solution;
  }

  void Solver::GenerateVarList( Expr expr, VarList &varList )
  {
    switch (expr.getKind ())
      {
	// Binary Operators:
	// Arithmetical 
      case kind::PLUS:
      case kind::MINUS:
      case kind::MULT:
      case kind::INTS_DIVISION_TOTAL:
      case kind::INTS_MODULUS_TOTAL:
	// Logical:
      case kind::AND:
      case kind::OR:
	// Comparision:
      case kind::EQUAL:
	//case kind::DISTINCT:
      case kind::LT:
      case kind::LEQ:
      case kind::GT:
      case kind::GEQ:
	GenerateVarList (expr[0], varList);
	GenerateVarList (expr[1], varList);
	break;
	// Unary Operators:
      case kind::NOT:
	GenerateVarList (expr[0], varList);
	break;
	// Variables and constants:
      case kind::VARIABLE:
	if (std::find (varList.begin (), varList.end (), expr)
	    == varList.end () )
	  varList.push_back (expr);
	break;
      default:
	// nothing
	break;
      }
    return;
  }

  /************************************************************/
  // Solver

  Solver::Solver()
  {
    smtEngine = new SmtEngine(&exprManager);
    // ??? Set "Non-linear integer arithmetic with uninterpreted sort and function symbols." logic:
    // This line causes the bug:
    // "SmtEngine: turning off produce-models because unsupported for nonlinear arith
    // Cannot get value when produce-models options is off.Cannot get value when produce-models options is off.f:"
    // smtEngine->setLogic("UFNIA");
    smtEngine->setOption("incremental", SExpr("true"));
    smtEngine->setOption("produce-models", SExpr("true"));
    smtEngine->setOption("rewrite-divk", SExpr("true"));
    symbolTable.pushScope();
  }

  Solver::~Solver()
  {
    symbolTable.popScope();
    if (smtEngine)
      delete smtEngine;
  }

  //--------------------------------------------------
  // Arithmetical expressions

  Expr Solver::CreatePlusExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::PLUS, left, right);
  }

  Expr Solver::CreateMinusExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::MINUS, left, right);
  }

  Expr Solver::CreateMultExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::MULT, left, right);
  }

  Expr Solver::CreateDivExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::INTS_DIVISION_TOTAL, left, right);
  }

  Expr Solver::CreateModExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::INTS_MODULUS_TOTAL, left, right);
  }
  
  //--------------------------------------------------
  // Logical Operators
  Expr Solver::CreateAndExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::AND, left, right);
  }

  Expr Solver::CreateOrExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::OR, left, right);
  }

  Expr Solver::CreateNotExpr(Expr expr)
  {
    return exprManager.mkExpr(kind::NOT, expr);
  }

  //--------------------------------------------------
  // Comparision expressions

  Expr Solver::CreateEqualExpr(Expr left, Expr right)
  {
    return exprManager.mkExpr(kind::EQUAL, left, right);
  }

  Expr Solver::CreateNotEqualExpr(Expr left, Expr right)
  {
    //return exprManager.mkExpr(kind::DISTINCT, left, right);
    Expr lt = CreateLessExpr(left, right);
    Expr gt = CreateGreaterExpr(left, right);
    Expr eq = CreateEqualExpr(left, right);
    return exprManager.mkExpr(kind::OR, lt, gt);
  }

  Expr Solver::CreateLessExpr(CVC4::Expr left, CVC4::Expr right)
  {
    return exprManager.mkExpr(kind::LT, left, right);
  }

  Expr Solver::CreateLessOrEqualExpr(CVC4::Expr left, CVC4::Expr right)
  {
    return exprManager.mkExpr(kind::LEQ, left, right);
  }

  Expr Solver::CreateGreaterExpr(CVC4::Expr left, CVC4::Expr right)
  {
    return exprManager.mkExpr(kind::GT, left, right);
  }

  Expr Solver::CreateGreaterOrEqualExpr(CVC4::Expr left,
					CVC4::Expr right)
  {
    return exprManager.mkExpr(kind::GEQ, left, right);
  }

  //--------------------------------------------------
  // Variables and constants

  Expr Solver::CreateVarExpr(string varName)
  {
    Expr varExpr;
    if (symbolTable.isBound (varName) )
      {
	// variable already exists
	varExpr = symbolTable.lookup (varName);
      }
    else
      {
	// this is a new one
	varExpr = exprManager.mkVar (varName,
				     exprManager.integerType ());
	symbolTable.bind (varName, varExpr);
      }
    return varExpr;
  }

  Expr Solver::CreateConstExpr(int value)
  {
    return exprManager.mkConst(Rational(value));
  }

  //--

};
