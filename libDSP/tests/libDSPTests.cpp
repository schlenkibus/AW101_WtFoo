#define CATCH_CONFIG_RUNNER
#include <libDSP/include/DSPHost.h>
#include "catchwrapper.cpp"

TEST_CASE("Init") {
  REQUIRE(true);
  REQUIRE(true);
}

TEST_CASE("DSPHost init") {
  DSPHost host{};
  REQUIRE(&host);
}

int main(int argc, char** argv)
{
  return Catch::Session().run(argc, argv);
}
