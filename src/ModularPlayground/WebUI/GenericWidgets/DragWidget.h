#pragma once
#include <Wt/WImage.h>
#include <Wt/WContainerWidget.h>

template <class UserData>
class DragWidgetProxy : public Wt::WImage
{
public:
  DragWidgetProxy(UserData * data, const char* url) : Wt::WImage{url}, m_data{data} {};
  UserData* m_data;
};

template<class UserData>
class DragWidget : public Wt::WContainerWidget {
public:
  DragWidget(UserData* data, const char *url, const char *smallurl, const char *mimetype) {
    auto proxy = addWidget(std::make_unique<DragWidgetProxy<UserData>>(data, url));
    auto dragImage = addWidget(std::make_unique<Wt::WImage>(smallurl));
    proxy->setDraggable(mimetype, dragImage, true);
  }
};
