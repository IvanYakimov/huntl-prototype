# ifndef __SOLVER_H__
# define __SOLVER_H__

# include <string>
# include <cvc4/cvc4.h>
# include <map>
# include <set>
# include <vector>
# include <stack>
# include <algorithm>
# include <iostream>
# include <string>
# include <list>

namespace SOLVER
{
// SMT solver
  typedef std::map<std::string, int> Solution;
  typedef std::list<Solution> SolutionSet;
  typedef std::list <CVC4::Expr> VarList;
  
  std::ostream &operator<<( std::ostream&, Solution& );
  std::ostream &operator<<( std::ostream&, SolutionSet& );
  std::ostream &operator<<( std::ostream&, VarList& );
    
  class Solver
  {
    friend class SolverVerifier;    
    
  public:
    Solver();
    ~Solver();

    SolutionSet GetSolutionSet( CVC4::Expr );

    void GenerateTestCases( SolutionSet, std::list <std::string> );

    // Arithmetical expressions 
    CVC4::Expr CreatePlusExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateMinusExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateMultExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateDivExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateModExpr(CVC4::Expr left, CVC4::Expr right);

    // Logical Operators
    CVC4::Expr CreateAndExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateOrExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateNotExpr(CVC4::Expr expr);

    // Comparision expressionsn
    CVC4::Expr CreateEqualExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateNotEqualExpr(CVC4::Expr, CVC4::Expr);
    CVC4::Expr CreateLessExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateLessOrEqualExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateGreaterExpr(CVC4::Expr left, CVC4::Expr right);
    CVC4::Expr CreateGreaterOrEqualExpr(CVC4::Expr left, CVC4::Expr right);

    // 
    CVC4::Expr CreateVarExpr( std::string );
    CVC4::Expr CreateConstExpr( int );


    //todo: private:
    CVC4::ExprManager exprManager;
    CVC4::SmtEngine *smtEngine;
    CVC4::SymbolTable symbolTable;

    int GetValue( CVC4::Expr );
    Solution GetSolution( CVC4::Expr );
    CVC4::Expr NegateFormula( CVC4::Expr );

    void GenerateVarList( CVC4::Expr, VarList& );
  };
};

# endif /* __SOLVER_H__ */
