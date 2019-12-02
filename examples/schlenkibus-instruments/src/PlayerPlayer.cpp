#include "PlayerPlayer.h"
#include <functional>

class RisingEdgeDetection : public DSPNode
{
 public:
  template <typename tCallback>
  explicit RisingEdgeDetection(DSPInputNode* in, const tCallback& cb)
      : in { in }
      , cb { cb }
  {
    last = in->getSignal();
  }

  void tick() override
  {
    auto current = in->getSignal();

    if(current > 0.0 && last == 0.0)
    {
      cb();
    }

    last = current;
  }

  DSPInputNode* getIn() const
  {
    return in;
  }

 private:
  float last;
  std::function<void(void)> cb;
  DSPInputNode* in;
};

PlayerPlayer::PlayerPlayer(DSPHost* host)
    : DSPModule(host)
{
  createOutput("OUT");
  createInput("PLAY");
  createInput("STOP");
  playTrigger = std::make_unique<RisingEdgeDetection>(findInput("PLAY"), [this]() { start(); });
  resetTrigger = std::make_unique<RisingEdgeDetection>(findInput("STOP"), [this]() { stop(); });
}

void PlayerPlayer::tickInternals()
{
  playTrigger->tick();
  resetTrigger->tick();

  auto signal = 0.0f;
  if(m_currentFile)
  {
    auto index = static_cast<int>(m_head);
    if(index + 1 == m_currentFile->getRightSamples().size())
      stop();
    else
      m_head += m_phaseinc;

    signal = m_currentFile->getRightSamples()[index];
  }

  findOutput("OUT")->setSignal(signal);
}

void PlayerPlayer::stop()
{
  m_phaseinc = 0.0;
}

void PlayerPlayer::start()
{
  m_head = 0;
  m_phaseinc = 1.0;
}

void PlayerPlayer::loadTrack(const File* file)
{
  m_currentFile = &SoundStorage::get().getSound(file->getAbsoulutePath());
}

const char* PlayerPlayer::getTypeName() const
{
  return "player-player";
}
