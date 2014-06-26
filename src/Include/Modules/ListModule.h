#ifndef T_LISTMODULE_H
#define T_LISTMODULE_H

#include "Module.h"
#include "Objects/BooleanObject.h"

/*
 * var a = [List init]
 * [a append: 2]
 *
 * if(instance->IsCModule()){
 *  Module::CallMethod(instance, funcName);
 * }
 */

#define BIND_METH_F(func, instance, size)                                      \
  make_pair(std::bind(&func, instance, _1), size)
#define BIND_INIT_F(func, size) make_pair(std::bind(&func, _1), size)

class ListModule;
typedef std::shared_ptr<ListModule> SListModule;

using namespace std::placeholders;
class ListModule : public Module {
private:
  std::vector<SObject> container_;
  // TODO, could be a generic template
  class ListIterator : public Module {
  public:
    std::vector<SObject>::iterator it_;
    std::vector<SObject> *list_;
    bool new_ = true;
    ListIterator(std::vector<SObject> *list) : Module("ListIterator") {
      list_ = list;
      MapStrFunc initMap = { { "get", BIND_METH_F(ListIterator::get, this, 0) },
                             { "next",
                               BIND_METH_F(ListIterator::next, this, 0) } };
      setFuncMap(initMap);
      setInstance();
    }
    SObject get(const VecSObject &obj) { return *it_; }
    SObject next(const VecSObject &obj) {
      /*
       * This is needed as when an iterator is used, we expect a next call
       * followed by a get call the next call is necessary at the start because
       * we don't know if we are ready for a get as the list may have nothing in
       * it.
       */
      if (new_) {
        new_ = !new_;
        it_ = list_->begin();
      } else {
        it_++;
      }

      if (it_ == list_->end()) {
        return BooleanObject::FALSE;
      }
      return BooleanObject::TRUE;
    }
  };

public:
  ListModule();
  static SObject init(const VecSObject &obj);
  static SObject initInternal();
  static SObject fromStringArray(int count, char *arr[]);
  SObject append(const VecSObject &obj);
  SObject count(const VecSObject &obj);
  SObject get(const VecSObject &obj);
  SObject reverse(const VecSObject &obj);
  SObject insert(const VecSObject &obj);
  SObject getIterator(const VecSObject &obj);
};

#endif
