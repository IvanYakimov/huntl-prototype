# ifndef __LIMIT_GENERATOR_HH__
# define __LIMIT_GENERATOR_HH__

# include <vector>
# include <string>

class LimitGenerator
{
public:
  LimitGenerator();
  void Run(int n);
private:
  std::vector<std::string> GenerateGrayArr(int);
};

# endif /* __LIMIT-GENERATOR_HH__ */
