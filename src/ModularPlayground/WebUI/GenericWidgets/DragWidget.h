#pragma once
#include <Wt/WImage.h>

template<class UserData>
class DragWidget : public Wt::WImage {
protected:
  DragWidget(UserData* data, const char *url, const char *smallurl, const char *mimetype) : Wt::WImage{url} {
    m_dragImage = std::make_unique<Wt::WImage>(smallurl);
    m_dragImage->setMargin(-15, Wt::Side::Left | Wt::Side::Top);
    setDraggable(mimetype, m_dragImage.get(), true);
    m_userData = data;
  }
public:
  UserData* getUserData() {
    return m_userData;
  }
private:
  UserData* m_userData;
  std::unique_ptr<Wt::WImage> m_dragImage;
};
