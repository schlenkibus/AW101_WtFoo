#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(const std::vector<std::string> &argumentNames,
                               int argc, char **argv) {
  parseArguments(argc, argv);
  for (auto &arg : argumentNames) {
    auto it = m_parsedArguments.find(arg);
    if (it == m_parsedArguments.end())
      throw std::runtime_error("Argument: " + arg + " missing!");
  }
}

ArgumentParser::tPair ArgumentParser::splitArgument(const tStr &basicString) {
  auto delim = basicString.find('=');
  if (delim < basicString.length()) {
    auto key = basicString.substr(0, delim);
    while (key.front() == '-') {
      key = key.substr(1);
    }
    auto value = basicString.substr(delim + 1);
    return std::make_pair(key, value);
  }
  throw std::runtime_error("Argument ill-formed: " + basicString);
}

void ArgumentParser::parseArguments(int argc, char **argv) {
  for (auto i = 1; i < argc; i++) {
    m_parsedArguments.emplace(splitArgument(argv[i]));
  }
}
const std::string &ArgumentParser::getArgumentValue(const std::string &name) const {
  auto it = m_parsedArguments.find(name);
  if(it != m_parsedArguments.end())
    return it->second;
  throw std::runtime_error{"Argument was not parsed!"};
}
