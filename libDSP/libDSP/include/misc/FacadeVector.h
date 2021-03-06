#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include <cassert>

template <typename T> class FacadeVector
{
 public:
  const std::vector<T*>& getData() const
  {
    return dataPtrs;
  }

  void remove(T* t)
  {
    erase_if(dataPtrs, [=](auto o) { return o == t; });
    data.remove_if([=](auto& o) { return o.get() == t; });
    assert(data.size() == dataPtrs.size());
  }

  typename std::vector<T*>::iterator begin()
  {
    return dataPtrs.begin();
  }

  typename std::vector<T*>::iterator end()
  {
    return dataPtrs.end();
  }

  typename std::vector<T*>::const_iterator begin() const
  {
    return dataPtrs.cbegin();
  }

  typename std::vector<T*>::const_iterator end() const
  {
    return dataPtrs.cend();
  }

  template <typename tPredicate> const T* find(const tPredicate& p) const
  {
    for(auto i : dataPtrs)
    {
      if(p(i))
        return i;
    }
    return nullptr;
  }

  template <typename tPredicate> T* find(const tPredicate& p)
  {
    for(auto i : dataPtrs)
    {
      if(p(i))
        return i;
    }
    return nullptr;
  }

  template <typename... tArgs> T* emplace_front(tArgs... args)
  {
    data.emplace_front(std::make_unique<T>(args...));
    auto ptr = data.begin()->get();
    dataPtrs.emplace_back(ptr);

    assert(data.size() == dataPtrs.size());

    return ptr;
  }

  T* emplace_front(T* ptr)
  {
    data.emplace_front(ptr);
    auto p = data.begin()->get();
    dataPtrs.emplace_back(ptr);

    assert(data.size() == dataPtrs.size());

    return p;
  }

  T* emplace_front(std::unique_ptr<T>&& uniquePtr)
  {
    data.emplace_front(std::move(uniquePtr));
    auto ptr = data.begin()->get();
    dataPtrs.emplace_back(ptr);

    assert(data.size() == dataPtrs.size());

    return ptr;
  }

  T* emplace_back(std::unique_ptr<T>&& uniquePtr)
  {
    data.emplace_back(std::move(uniquePtr));
    auto ptr = data.rbegin()->get();
    dataPtrs.emplace_back(ptr);

    assert(data.size() == dataPtrs.size());

    return ptr;
  }

  template <typename... tArgs> T* emplace_back(tArgs... args)
  {
    data.emplace_back(std::make_unique<T>(args...));
    auto ptr = data.rbegin()->get();
    dataPtrs.emplace_back(ptr);

    assert(data.size() == dataPtrs.size());

    return ptr;
  }

  T* emplace_back(T* t)
  {
    data.emplace_back(t);
    auto ptr = data.rbegin()->get();
    dataPtrs.emplace_back(ptr);

    assert(data.size() == dataPtrs.size());

    return ptr;
  }

 private:
  template <typename tPredicate> void erase_if(std::vector<T*>& v, const tPredicate& p)
  {
    v.erase(std::remove_if(v.begin(), v.end(), p));
  }

  std::vector<T*> dataPtrs;
  std::list<std::unique_ptr<T>> data;
};