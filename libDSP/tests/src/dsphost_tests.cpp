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

  GIVEN("DSPHost with registered and created modules")
  {
    using TestModules::EquationModule;
    using TestModules::NumberModule;
    using TestModules::TestRootModule;

    DSPHost host;
    host.registerModule("plus", [](auto h) { return new EquationModule([](float x, float y) { return x + y; }, h); });
    host.registerModule("minus", [](auto h) { return new EquationModule([](float x, float y) { return x - y; }, h); });
    host.registerModule("times", [](auto h) { return new EquationModule([](float x, float y) { return x * y; }, h); });
    host.registerModule("divide", [](auto h) { return new EquationModule([](float x, float y) { return x / y; }, h); });
    host.registerModule("number", [](auto h) { return new NumberModule(h); });

    auto rootModule = dynamic_cast<TestRootModule*>(host.createRootModule(new TestRootModule(&host)));

    auto B = dynamic_cast<TestModules::NumberModule*>(host.createModule("number"));
    auto C = dynamic_cast<TestModules::NumberModule*>(host.createModule("number"));

    auto rootIn = rootModule->findInput("IN");
    auto numberB = B->findOutput("OUT");
    auto numberC = C->findOutput("OUT");

    THEN("Inputs and Outputs can be found")
    {
      REQUIRE(rootIn);
      REQUIRE(numberB);
      REQUIRE(numberC);
    }

    WHEN("B outputs to root")
    {
      rootIn->connect(numberB);
      REQUIRE(rootIn->connectedTo() == numberB);

      THEN("root input can be cleared")
      {
        rootIn->clearInput();
        REQUIRE(rootIn->connectedTo() == nullptr);
      }

      THEN("number B to root on tick")
      {
        numberB->setSignal(1);
        REQUIRE(rootIn->getSignal() == 1);
        numberB->setSignal(0);
        REQUIRE(rootIn->getSignal() == 0);
      }
    }

    WHEN("B and C routed into plus")
    {
      auto plus = host.createModule("plus");
      auto x = plus->findInput("X");
      auto y = plus->findInput("Y");

      x->connect(numberB);
      y->connect(numberC);

      rootIn->connect(plus->findOutput("="));

      THEN("1 + 1 = 2")
      {
        numberB->setSignal(1);
        numberC->setSignal(1);
        host.tick();
        REQUIRE(rootIn->getSignal() == 2.0f);
      }

      THEN("-1 + 1 = 0")
      {
        numberB->setSignal(-1);
        numberC->setSignal(1);
        host.tick();
        REQUIRE(rootIn->getSignal() == 0.0f);
      }
    }
  }
}

/*
 *    Root <- A <-----plus<---Number
 *            |       ^
 *            \_______/
 */
SCENARIO("Feedback loop")
{
  using namespace TestModules;

  DSPHost host;
  auto root = host.createRootModule(new TestRootModule(&host));
  host.registerModule("number", [](auto h) { return new NumberModule(h); });
  host.registerModule("pass-through", [](auto h) { return new OneTickDelay(h); });
  host.registerModule("plus", [](auto h) { return new EquationModule([](float x, float y) { return x + y; }, h); });

  auto A = host.createModule("pass-through");
  auto plus = host.createModule("plus");
  auto number = dynamic_cast<NumberModule*>(host.createModule("number"));

  auto rootIn = root->findInput("IN");
  auto aOut = A->findOutput("OUT");
  auto aIn = A->findInput("IN");
  auto numberOut = number->findOutput("OUT");

  *rootIn << aOut;
  *aIn << plus->findOutput("=");
  *plus->findInput("X") << numberOut;
  *plus->findInput("Y") << aOut;

  THEN("tick order correct")
  {
    auto& order = host.getTickOrder();
    REQUIRE(order.size() == 4);
    REQUIRE(order[0] == number);
    REQUIRE(order[1] == plus);
    REQUIRE(order[2] == A);
    REQUIRE(order[3] == root);
  }

  THEN("root accumulates feedback on tick")
  {
    number->setValue(1);
    REQUIRE(rootIn->getSignal() == 0.0f);
    for(auto i = 1; i != 50; i++) {
      host.tick();
      REQUIRE(rootIn->getSignal() == static_cast<float>(i));
    }
  }
}