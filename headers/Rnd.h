#pragma once
#ifndef _RND_H_
#define _RND_H_ 1.0
//---------------------------------------------------------------------------------------------------------------------------------
/* 
���������� ��� �������� ��� �������� ����� ����� ����� � � ��������� ������. ������� ������� ��������� ����� � �����������
������������� � ������� ��������� ��� �� ���������. ��� ����� ��� �� 0 �� 100 ���������� �� ���� � ��� ����� � ��������� ������
�� 0 �� 1 ������������. ������������ ���������� ����� ����������� �����. ����� ���� ��� ������� ������� �������� ����
UUID(�� �������� ����� ������). ���� ���������� ������������ ����� ������������� ����������. ��� ������� ������������
������� ����� ��������� ��� ������������� ��� ���������� � ������� ������� SetMultithread � getMultithread �������������.
���� (u)int128 � float128 � ��� �� long double �� �������������� ��� ��� �� �� ������������ ���������� msbuild.
Attention! ����� ������������� ����������� �������� ������� ������� ReleaseRnd. ��� ������������ ������ ������.
*/
//---------------------------------------------------------------------------------------------------------------------------------
#include <cstdint>
#include <string>
#include <UUID.h>
#ifndef RND_EXPORT
#define RND_DLL_API __declspec(dllimport)
#else
#define RND_DLL_API __declspec(dllexport)
#endif
using real32_t = float;
using real64_t = double;
using real80_t = long double;
//using real128_t = float128;
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyRand{
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt8 { 
  public:
    virtual int8_t get() noexcept = 0;
    virtual int8_t get(const int8_t min, const int8_t max) noexcept = 0 ;
    virtual int8_t getRep(const int8_t min, const int8_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint8 { 
  public:
    virtual uint8_t get() noexcept = 0;
    virtual uint8_t get(const uint8_t min, const uint8_t max) noexcept = 0 ;
    virtual uint8_t getRep(const uint8_t min, const uint8_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt16 { 
  public:
    virtual int16_t get() noexcept = 0;
    virtual int16_t get(const int16_t min, const int16_t max) noexcept = 0 ;
    virtual int16_t getRep(const int16_t min, const int16_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint16 { 
  public:
    virtual uint16_t get() noexcept = 0;
    virtual uint16_t get(const uint16_t min, const uint16_t max) noexcept = 0 ;
    virtual uint16_t getRep(const uint16_t min, const uint16_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt { 
  public:
    virtual int32_t get() noexcept = 0;
    virtual int32_t get(const int32_t min, const int32_t max) noexcept = 0 ;
    virtual int32_t getRep(const int32_t min, const int32_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint{ 
  public:
    virtual uint32_t get() noexcept = 0;
    virtual uint32_t get(const uint32_t min, const uint32_t max) noexcept = 0;
    virtual uint32_t getRep(const uint32_t min, const uint32_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndLong { 
  public:
    virtual int64_t get() noexcept = 0;
    virtual int64_t get(const int64_t min, const int64_t max) noexcept = 0;
    virtual int64_t getRep(const int64_t min, const int64_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUlong { 
  public:
    virtual uint64_t get() noexcept = 0;
    virtual uint64_t get(const uint64_t min, const uint64_t max) noexcept = 0;
    virtual uint64_t getRep(const uint64_t min, const uint64_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndFlt { 
  public:
    virtual real32_t get() noexcept = 0;
    virtual real32_t get(const real32_t min, const real32_t max) noexcept = 0;
    virtual real32_t getRep(const real32_t min, const real32_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndDbl { 
  public:
    virtual real64_t get() noexcept = 0;
    virtual real64_t get(const real64_t min, const real64_t max) noexcept = 0;
    virtual real64_t getRep(const real64_t min, const real64_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  enum class EValType : uint8_t { Int8, Uint8, Int16, Uint16, Int, Uint, Long, Ulong, Flt, Dbl };
  //---------------------------------------------------------------------------------------------------------------------------------
  template<typename T>
  T *convertTo(void *ptr) {
    return reinterpret_cast<T*>(ptr);
  }
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API void SetMultithread(const bool _Is) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool getMultithread() noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API void *GetRnd(const EValType tp, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt8 *GetRnd(const int8_t min, const int8_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint8 *GetRnd(const uint8_t min, const uint8_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt16 *GetRnd(const int16_t min, const int16_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint16 *GetRnd(const uint16_t min, const uint16_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt *GetRnd(const int32_t min, const int32_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint *GetRnd(const uint32_t min, const uint32_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndLong *GetRnd(const int64_t min, const int64_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUlong *GetRnd(const uint64_t min, const uint64_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndFlt *GetRnd(const  real32_t min, const real32_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndDbl *GetRnd(const real64_t  min, const real64_t max, MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool ReleaseRnd(const MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
} // !namespace MyRand
#endif // !_RND_H_
//---------------------------------------------------------------------------------------------------------------------------------