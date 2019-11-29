#pragma once
#include <list>
#include <vector>
#include <algorithm>

template <typename T> class FacadeVector
{
 public:
  const std::vector<T*>& getData() const
  {
    return dataPtrs;
  }

  void remove(T* t)
  {
    data.remove_if([=](auto& o) { return o.get() == t; });
    erase_if(dataPtrs, [=](auto o) { return o == t; });
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

  T* emplace_front(std::unique_ptr<T>&& uniquePtr)
  {
    data.emplace_front(std::move(uniquePtr));
    auto ptr = data.begin()->get();
    dataPtrs.emplace_back(ptr);
    return ptr;
  }


  T* emplace_back(std::unique_ptr<T>&& uniquePtr)
  {
    data.emplace_back(std::move(uniquePtr));
    auto ptr = data.rbegin()->get();
    dataPtrs.emplace_back(ptr);
    return ptr;
  }

  template <typename... tArgs> T* emplace_back(tArgs... args)
  {
    data.emplace_back(std::make_unique<T>(args...));
    auto ptr = data.rbegin()->get();
    dataPtrs.emplace_back(ptr);
    return ptr;
  }

  T* emplace_back(T* t)
  {
    data.emplace_back(t);
    auto ptr = data.rbegin()->get();
    dataPtrs.emplace_back(ptr);
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