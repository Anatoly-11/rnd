#include <Rnd.h>
#include <random>
#include <map>
#include <chrono>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
mutex mtx;
//-------------------------------------------------------------------------------------------------------------------------------
static bool isMultiThread = true;
//-------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API void MyRand::SetMultithread(const bool _Is) noexcept {
  isMultiThread = _Is;
}
//-------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API bool MyRand::getMultithread() noexcept {
  return isMultiThread;
}
//---------------------------------------------------------------------------------------------------------------------------------
template <typename T> requires is_integral_v<T>
class RndIntImpl {
  RndIntImpl(const RndIntImpl &) = delete;
  RndIntImpl(RndIntImpl &&) = delete;
  RndIntImpl &operator=(const RndIntImpl &) = delete;
  RndIntImpl &&operator=(RndIntImpl &&) = delete;
private:
  mt19937_64 engine;
  uniform_int_distribution<T> distr;
  int count;

  void inc() {
    if(isMultiThread) {
      lock_guard<mutex> grd(mtx);
    }
    count++;
    if(count > 32) {
      count %= 32;
      engine.seed(chrono::system_clock::now().time_since_epoch().count() / 100ull);
    }
  }

protected:

  RndIntImpl(): engine{mt19937_64{random_device{}()}}, distr{1, 100}, count{0} {}
  RndIntImpl(const T _min, const T _max): engine{mt19937_64{random_device{}()}}, distr{_min, _max}, count{0} {}

  T get() noexcept {
    return distr(engine);
  }

  T get(const T _min, const T _max) noexcept {
    inc();
    uniform_int_distribution<T> dd{_min, _max};
    return dd(engine);
  }

  T getRep(const T _min, const T _max) noexcept {
    if(isMultiThread) {
      unique_lock<mutex> grd(mtx);
      count = 0;
      distr = uniform_int_distribution<T>(_min, _max);
      grd.unlock();
    } else {
      count = 0;
      distr = uniform_int_distribution<T>(_min, _max);
    }
    return distr(engine);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
template <typename T> requires is_floating_point_v<T>
class RndRealImpl {
  RndRealImpl(const RndRealImpl &) = delete;
  RndRealImpl(RndRealImpl &&) = delete;
  RndRealImpl &operator=(const RndRealImpl &) = delete;
  RndRealImpl &&operator=(RndRealImpl &&) = delete;
private:
  mt19937_64 engine;
  uniform_real_distribution<T> distr;
  int count;
  
  void inc() {
    if(isMultiThread) {
      lock_guard<mutex> grd(mtx);
    }
    count++;
    if(count > 32) {
      count %= 32;
      engine.seed(chrono::system_clock::now().time_since_epoch().count() / 100ull);
    }
  }

protected:
  RndRealImpl(): engine{mt19937_64{random_device{}()}}, distr{0.0, 1.0}, count{0} {}

  RndRealImpl(const T _min, const T _max): engine{mt19937_64{random_device{}()}}, distr{_min, _max}, count{0} {}

  T get() noexcept {
    inc();
    return distr(engine);
  }

  T get(const T _min, const T _max) noexcept {
    inc();
    uniform_real_distribution<T> dd{_min, _max};
    return dd(engine);
  }

  T getRep(const T _min, const T _max) noexcept {
    if(isMultiThread) {
      unique_lock<mutex> grd(mtx);
      count = 0;
      distr = uniform_real_distribution<T>(_min, _max);
      grd.unlock();
    } else {
      count = 0;
      distr = uniform_real_distribution<T>(_min, _max);
    }
    return distr(engine);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt8 : public MyRand :: IRndInt8, public RndIntImpl<int16_t> {
public:
  RndInt8() : RndIntImpl<int16_t>() {}

  RndInt8(const int8_t min, const int8_t max) : RndIntImpl<int16_t>(min, max) {}

  virtual int8_t get() noexcept  override {
    return RndIntImpl<int16_t>::get();
  }

  virtual int8_t get(const int8_t min, const int8_t max) noexcept  override {
    return RndIntImpl<int16_t>::get(min, max);
  }

  virtual int8_t getRep(const int8_t min, const int8_t max) noexcept  override {
    return RndIntImpl<int16_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint8 : public MyRand ::IRndUint8, public RndIntImpl<uint16_t> {
public:
  RndUint8() : RndIntImpl<uint16_t>() {}

  RndUint8(const uint8_t min, const uint8_t max) : RndIntImpl<uint16_t>(min, max) {}

  virtual uint8_t get() noexcept  override {
    return RndIntImpl<uint16_t>::get();
  }

  virtual uint8_t get(const uint8_t min, const uint8_t max) noexcept  override {
    return RndIntImpl<uint16_t>::get(min, max);
  }

  virtual uint8_t getRep(const uint8_t min, const uint8_t max) noexcept  override {
    return RndIntImpl<uint16_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt16 : public MyRand :: IRndInt16, public RndIntImpl<int16_t> {
public:
  RndInt16() : RndIntImpl<int16_t>() {}

  RndInt16(const int16_t min, const int16_t max) : RndIntImpl<int16_t>(min, max) {}

  virtual int16_t get() noexcept  override {
    return RndIntImpl<int16_t>::get();
  }

  virtual int16_t get(const int16_t min, const int16_t max) noexcept  override {
    return RndIntImpl<int16_t>::get(min, max);
  }

  virtual int16_t getRep(const int16_t min, const int16_t max) noexcept  override {
    return RndIntImpl<int16_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint16 : public MyRand::IRndUint16, public RndIntImpl<uint16_t> {
public:
  RndUint16() : RndIntImpl<uint16_t>() {}

  RndUint16(const uint16_t min, const uint16_t max) : RndIntImpl<uint16_t>(min, max) {}

  virtual uint16_t get() noexcept  override {
    return RndIntImpl<uint16_t>::get();
  }

  virtual uint16_t get(const uint16_t min, const uint16_t max) noexcept  override {
    return RndIntImpl<uint16_t>::get(min, max);
  }

  virtual uint16_t getRep(const uint16_t min, const uint16_t max) noexcept  override {
    return RndIntImpl<uint16_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt : public MyRand :: IRndInt, public RndIntImpl<int32_t> {
public:
  RndInt() : RndIntImpl<int32_t>() {}

  RndInt(const int32_t min, const int32_t max) : RndIntImpl<int32_t>(min, max) {}

  virtual int32_t get() noexcept  override {
    return RndIntImpl<int32_t>::get();
  }

  virtual int32_t get(const int32_t min, const int32_t max) noexcept  override {
    return RndIntImpl<int32_t>::get(min, max);
  }

  virtual int32_t getRep(const int32_t min, const int32_t max) noexcept  override {
    return RndIntImpl<int32_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint : public MyRand :: IRndUint, public RndIntImpl<uint32_t> {
public:
  RndUint() : RndIntImpl<uint32_t>() {}

  RndUint(const uint32_t min, const uint32_t max) : RndIntImpl<uint32_t>(min, max) {}

  virtual uint32_t get() noexcept  override {
    return RndIntImpl<uint32_t>::get();
  }

  virtual uint32_t get(const uint32_t min, const uint32_t max) noexcept  override {
    return RndIntImpl<uint32_t>::get(min, max);
  }

  virtual uint32_t getRep(const uint32_t min, const uint32_t max) noexcept  override {
    return RndIntImpl<uint32_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndLong : public MyRand :: IRndLong, public RndIntImpl<int64_t> {
public:
  RndLong() : RndIntImpl<int64_t>() {}

  RndLong(const int64_t min, const int64_t max) : RndIntImpl<int64_t>(min, max) {}

  virtual int64_t get() noexcept  override {
    return RndIntImpl<int64_t>::get();
  }

  virtual int64_t get(const int64_t min, const int64_t max) noexcept  override {
    return RndIntImpl<int64_t>::get(min, max);
  }

  virtual int64_t getRep(const int64_t min, const int64_t max) noexcept  override {
    return RndIntImpl<int64_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUlong : public MyRand :: IRndUlong, public RndIntImpl<uint64_t> {
public:
  RndUlong() : RndIntImpl<uint64_t>() {}

  RndUlong(const uint64_t min, const uint64_t max) : RndIntImpl<uint64_t>(min, max) {}

  virtual uint64_t get() noexcept  override {
    return RndIntImpl<uint64_t>::get();
  }

  virtual uint64_t get(const uint64_t min, const uint64_t max) noexcept  override {
    return RndIntImpl<uint64_t>::get(min, max);
  }

  virtual uint64_t getRep(const uint64_t min, const uint64_t max) noexcept  override {
    return RndIntImpl<uint64_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndFlt : public MyRand :: IRndFlt, public  RndRealImpl<real32_t> {
public:
  RndFlt() : RndRealImpl<real32_t>() {}
  RndFlt(const real32_t min, const real32_t max) : RndRealImpl<real32_t>(min, max) {}

  virtual real32_t get() noexcept  override {
    return RndRealImpl<real32_t>::get();
  }

  virtual real32_t get(const real32_t min, const real32_t max) noexcept  override {
    return RndRealImpl<real32_t>::get(min, max);
  }

  virtual real32_t getRep(const real32_t min, const real32_t max) noexcept  override {
    return RndRealImpl<real32_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndDbl : public MyRand :: IRndDbl, public  RndRealImpl<real64_t> {
public:
  RndDbl() : RndRealImpl<real64_t>() {}
  RndDbl(const real64_t min, const real64_t max) : RndRealImpl<real64_t>(min, max) {}

  virtual real64_t get() noexcept  override {
    return RndRealImpl<real64_t>::get();
  }

  virtual real64_t get(const real64_t min, const real64_t max) noexcept  override {
    return RndRealImpl<real64_t>::get(min, max);
  }

  virtual real64_t getRep(const real64_t min, const real64_t max) noexcept  override {
    return RndRealImpl<real64_t>::getRep(min, max);
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
struct RndData {
  void *ptr;
  MyRand::EValType tp;
  RndData(const void *_ptr, const MyRand::EValType _tp): ptr(const_cast<void *>(_ptr)), tp(_tp) {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
static map<MyUuid::UUID, RndData> genRnd;
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<void *, MyUuid::UUID>  MyRand::GetRnd(const EValType tp) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  MyUuid::UUID uid;
  if(isMultiThread) {
    grd.lock();
  }
  void *rnd = (tp == EValType::Int8 ? (void*)(new RndInt8) :
    tp == EValType::Uint8 ? (void*)(new RndUint8) :
    tp == EValType::Int16 ? (void*)(new RndUint16) :
    tp == EValType::Uint16 ? (void*)(new RndUint16) :
    tp == EValType::Int ? (void*)(new RndInt) :
    tp == EValType::Uint ? (void*)(new RndUint) :
    tp == EValType::Long ? (void*)(new RndLong) :
    tp == EValType::Ulong ? (void*)(new RndUlong) :
    tp == EValType::Flt ? (void*)(new RndFlt) :
    tp == EValType::Dbl ? (void*)(new RndDbl) : nullptr);
  if(isMultiThread) {
    grd.unlock();
  }
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndInt8*, MyUuid::UUID> MyRand::GetRnd(const int8_t min, const int8_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndInt8 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt8(min, max);
    grd.unlock();
  } else 
    rnd = new RndInt8(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Int8)));
    grd.unlock();
  } else 
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Int8)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndUint8*, MyUuid::UUID> MyRand::GetRnd(const uint8_t min, const uint8_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint8 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint8(min, max);
    grd.unlock();
  } else
    rnd = new RndUint8(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint8)));
    grd.unlock();
  } else
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint8)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndInt16*, MyUuid::UUID> MyRand::GetRnd(const int16_t min, const int16_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndInt16 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt16(min, max);
    grd.unlock();
  } else
    rnd = new RndInt16(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint16)));
    grd.unlock();
  } else
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint16)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API  std::tuple<MyRand::IRndUint16*, MyUuid::UUID> MyRand::GetRnd(const uint16_t min, const uint16_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint16 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint16(min, max);
    grd.unlock();
  } else 
    rnd = new RndUint16(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint16)));
    grd.unlock();
  } else 
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint16)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndInt*, MyUuid::UUID> MyRand::GetRnd(const int32_t min, const int32_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndInt *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt(min, max);
    grd.unlock();
  } else 
    rnd = new RndInt(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Int)));
    grd.unlock();
  } else 
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Int)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndUint*, MyUuid::UUID> MyRand::GetRnd(const uint32_t min, const uint32_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint(min, max);
    grd.unlock();
  } else 
    rnd = new RndUint(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint)));
    grd.unlock();
  } else 
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Uint)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndLong*, MyUuid::UUID> MyRand::GetRnd(const int64_t min, const int64_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndLong *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndLong(min, max);
    grd.unlock();
  } else 
    rnd = new RndLong(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Long)));
    grd.unlock();
  } else
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Long)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndUlong*, MyUuid::UUID> MyRand::GetRnd(const uint64_t min, const uint64_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUlong *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUlong(min, max);
    grd.unlock();
  } else
    rnd = new RndUlong(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Ulong)));
    grd.unlock();
  } else 
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Ulong)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndFlt*, MyUuid::UUID> MyRand::GetRnd(const real32_t min, const real32_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndFlt *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndFlt(min, max);
    grd.unlock();
  } else
    rnd = new RndFlt(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Flt)));
    grd.unlock();
  } else
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Flt)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API std::tuple<MyRand::IRndDbl*, MyUuid::UUID> MyRand::GetRnd(const real64_t min, const real64_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndDbl *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndDbl(min, max);
    grd.unlock();
  } else
    rnd = new RndDbl(min, max);
  MyUuid::UUID uid = MyUuid::getUUID();
  if(isMultiThread) {
    grd.lock();
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Dbl)));
    grd.unlock();
  } else
    genRnd.insert(pair(uid, RndData(rnd, MyRand::EValType::Dbl)));
  return {rnd, uid};
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API bool MyRand::ReleaseRnd(const MyUuid::UUID &_gid)  noexcept {
  if(isMultiThread) {
    lock_guard<mutex> grd(mtx);
  }
  auto it = genRnd.find(_gid);
  if(it != end(genRnd)) {
    void *rnd = it->second.ptr;
    switch(it->second.tp) {
    case MyRand::EValType::Int8:
      delete convertTo<RndInt8>(rnd);
      break;
    case MyRand::EValType::Uint8:
      delete convertTo<RndUint8>(rnd);
      break;
    case MyRand::EValType::Int16:
      delete convertTo<RndInt16>(rnd);
      break;
    case MyRand::EValType::Uint16:
      delete convertTo<RndUint16>(rnd);
      break;
    case MyRand::EValType::Int:
      delete convertTo<RndInt>(rnd);
      break;
    case MyRand::EValType::Uint:
      delete convertTo<RndUint>(rnd);
      break;
    case MyRand::EValType::Long:
      delete convertTo<RndLong>(rnd);
      break;
    case MyRand::EValType::Ulong:
      delete convertTo<RndUlong>(rnd);
      break;
    case MyRand::EValType::Flt:
      delete convertTo<RndFlt>(rnd);
      break;
    case MyRand::EValType::Dbl:
      delete convertTo<RndDbl>(rnd);
      break;
    default:
      return false;
    }
    genRnd.erase(_gid);
    MyUuid::releaseUUID(_gid);
    return true;
  } 
  return false;
}
//---------------------------------------------------------------------------------------------------------------------------------