#pragma once
#include <map>
#include <string>
#include <vector>

class ArgumentParser {
public:
  ArgumentParser(const std::vector<std::string> &argumentNames, int argc,
                 char **argv);

  const std::string& getArgumentValue(const std::string& name) const;
  bool parseBooleanArgument(const std::string& name) const;
private:
  using tStr = std::string;
  using tPair = std::pair<tStr, tStr>;
  tPair splitArgument(const tStr &basicString);

  void parseArguments(int argc, char **argv);

  std::map<tStr, tStr> m_parsedArguments;
};
