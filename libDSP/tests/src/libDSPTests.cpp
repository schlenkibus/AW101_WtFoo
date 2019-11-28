#define CATCH_CONFIG_RUNNER
#include <libDSP/include/DSPHost.h>
#include "tests/catchwrapper.cpp"

int main(int argc, char** argv)
{
  return Catch::Session().run(argc, argv);
}
