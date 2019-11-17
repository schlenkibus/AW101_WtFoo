#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>

template <class UserData> class DragWidgetProxy : public Wt::WImage {
public:
  DragWidgetProxy(UserData *data, const char *url)
      : Wt::WImage{url}, m_data{data} {};
  UserData *m_data;
};

template <class UserData> class DragWidget : public Wt::WContainerWidget {
public:
  DragWidget(UserData *data, const char *url, const char *smallurl,
             const char *mimetype) {
    m_image = addWidget(std::make_unique<DragWidgetProxy<UserData>>(data, url));
    auto dragImage = addWidget(std::make_unique<Wt::WImage>(smallurl));
    m_image->setDraggable(mimetype, dragImage, true);
  }

protected:
  Wt::WImage *getImageElement() { return m_image; }

  Wt::WImage *m_image;
};
