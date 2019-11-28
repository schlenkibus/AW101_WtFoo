#include "tests/catchwrapper.cpp"
#include "libDSP/include/DSPHost.h"
#include "MockedModules.h"

SCENARIO("DSPHost can register and create modules")
{
  GIVEN("empty DSPHost")
  {
    DSPHost host;
    REQUIRE(host.getAvailableModules().empty());

    WHEN("some Module Factory is registered")
    {
      host.registerModule("delay", [](auto h) { return new TestModules::OneTickDelay(h); });

      THEN("module is available")
      {
        REQUIRE_FALSE(host.getAvailableModules().empty());
        REQUIRE(host.getAvailableModules().front() == "delay");
      }
      THEN("module can be created")
      {
        REQUIRE(host.createModule("delay"));
      }

      WHEN("module was created")
      {
        auto delay1 = host.createModule("delay");
        REQUIRE(delay1);

        THEN("module can be found")
        {
          REQUIRE(delay1 == host.findModuleByUuid(delay1->getUuid()));
        }
        THEN("module can be removed")
        {
          host.removeModule(delay1);
        }
        THEN("second module can be created")
        {
          REQUIRE(host.createModule("delay"));
        }

        WHEN("second module was created")
        {
          auto delay2 = host.createModule("delay");
          REQUIRE(delay2);

          THEN("both modules can be found")
          {
            REQUIRE(delay1 == host.findModuleByUuid(delay1->getUuid()));
            REQUIRE(delay2 == host.findModuleByUuid(delay2->getUuid()));
          }
          THEN("either module can be removed")
          {
            SECTION("remove 1")
            {
              auto delay1UUID = delay1->getUuid();
              host.removeModule(delay1);
              REQUIRE(host.findModuleByUuid(delay1UUID) == nullptr);
            }
            SECTION("remove 2")
            {
              auto delay2UUID = delay2->getUuid();
              host.removeModule(delay2);
              REQUIRE(host.findModuleByUuid(delay2UUID) == nullptr);
            }
          }
        }
      }
    }
  }
}