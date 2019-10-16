#include "WelcomeHall.h"

WelcomeHall::WelcomeHall()
{
  m_server.config.port = 18700;
  m_server.config.address = "101.101.101.101";
  auto& welcomeHallEndPoint = m_server.endpoint["/welcome/"];

  welcomeHallEndPoint.on_message = [this](auto connection, auto message) mutable {
    auto str = message->string();
    std::cout << str << std::endl;
    onMessage(std::string(str));
  };

  welcomeHallEndPoint.on_open = [](auto connection) {
    std::cout << "Device connected from: " << connection->remote_endpoint().address().to_string() << std::endl;
  };

  m_thread = std::thread([&]() { m_server.start(); });

  m_pingThread = std::thread([&]() {
    for(auto& c : m_server.endpoint["/welcome/"].get_connections())
    {
      auto send_stream = std::make_shared<SimpleWeb::SocketServer<SimpleWeb::WS>::OutMessage>();
      *send_stream << "PING!";
      // connection->send is an asynchronous function
      c->send(send_stream, [](const SimpleWeb::error_code& ec) {
        if(ec)
        {
          std::cout << "Server: Error sending message. " <<
              // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
              "Error: " << ec << ", error message: " << ec.message() << std::endl;
        }
      });
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
  });
}

WelcomeHall::~WelcomeHall()
{
  if(m_pingThread.joinable())
    m_pingThread.join();

  m_server.stop();

  if(m_thread.joinable())
    m_thread.join();
  else
    m_thread.detach();
}

void WelcomeHall::onDeviceHello(const tCB& cb)
{
  m_deviceHelloCallbacks.emplace_back(cb);
}

void WelcomeHall::onMessage(const std::string& s)
{
  for(auto& cb : m_deviceHelloCallbacks)
  {
    cb(std::string(s));
  }
}
