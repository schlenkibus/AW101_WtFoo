#include "tests/catchwrapper.cpp"
#include "libDSP/include/DSPHost.h"
#include "MockedModules.h"
#include "TestHelper.h"

SCENARIO("DSPHost can register, create and remove modules")
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

          THEN("both modules can be found")
          {
            REQUIRE(delay1 == host.findModuleByUuid(delay1->getUuid()));
            REQUIRE(delay2 == host.findModuleByUuid(delay2->getUuid()));
          }
          THEN("either module can be removed")
          {
            SECTION("remove 1")
            {
              TestHelper::removeModule(&host, delay1);
              REQUIRE(host.findModuleByUuid(delay2->getUuid()));
            }
            SECTION("remove 2")
            {
              TestHelper::removeModule(&host, delay2);
              REQUIRE(host.findModuleByUuid(delay1->getUuid()));
            }
          }
        }
      }
    }
  }

  GIVEN("DSPHost with registered modules")
  {
    DSPHost host;
    host.registerModule("delay", [](auto h) { return new TestModules::OneTickDelay(h); });

    WHEN("delay modules are created")
    {
      auto A = host.createModule("delay");
      auto B = host.createModule("delay");
      auto C = host.createModule("delay");

      auto aOut = A->findOutput("OUT");
      auto bIN = B->findInput("IN");
      auto cIN = C->findInput("IN");

      THEN("A outputs to B")
      {
        bIN->connect(aOut);
        REQUIRE(bIN->connectedTo() == aOut);

        THEN("A can be removed")
        {
          TestHelper::removeModule(&host, A);
          REQUIRE(bIN->connectedTo() == nullptr);
        }

        THEN("B can be cleared")
        {
          B->clearInputs(bIN);
          REQUIRE(bIN->connectedTo() == nullptr);
        }

        THEN("B can be removed")
        {
          TestHelper::removeModule(&host, B);
        }
      }

      THEN("A outputs to B and C")
      {
        bIN->connect(aOut);
        cIN->connect(aOut);
        REQUIRE(bIN->connectedTo() == aOut);
        REQUIRE(cIN->connectedTo() == aOut);

        THEN("host can tick")
        {
          host.tick();
        }

        THEN("A can be removed")
        {
          TestHelper::removeModule(&host, A);
          REQUIRE(bIN->connectedTo() == nullptr);
          REQUIRE(cIN->connectedTo() == nullptr);
        }

      }
    }
  }
}