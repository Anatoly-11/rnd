/* Модуль тестов для проверки работы модуля rnd с использованием модуля uuid(см описани и тесты к нему)
*/
#include <iostream>
#include <string>
#include <UUID.h>
#include <Rnd.h>
//include test headers modules 
//#define MANUAL_RUN
#ifndef MANUAL_RUN
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include <vector>
#include <algorithm>
#include <cstdint>
//#else 
//#include <boost/io/quoted.hpp>
#endif
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef MANUAL_RUN
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstInt8) { 
  MyUuid::UUID uid;
  int8_t vmin = -50, vmax = 110;
  MyRand::IRndInt8 *rnd = MyRand::GetRnd(vmin, vmax, uid);
  vector<int8_t> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstInt) { 
  MyUuid::UUID uid;
  int vmin = 0, vmax = 100;
  MyRand::IRndInt *rnd = MyRand::GetRnd(vmin, vmax, uid);
  vector<int> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstULL) { 
  MyUuid::UUID uid;
  uint64_t vmin = 0, vmax = 2300;
  MyRand::IRndUlong *rnd = MyRand::GetRnd(vmin, vmax, uid);
  vector<uint64_t> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstFlt) { 
  MyUuid::UUID uid;
  float vmin = -5.920f, vmax = 23.45f;
  MyRand::IRndFlt *rnd = MyRand::GetRnd(vmin, vmax, uid);
  vector<float> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstDbl) { 
  MyUuid::UUID uid;
  double vmin = -528.828, vmax = 2339.929;
  MyRand::IRndDbl *rnd = MyRand::GetRnd(vmin, vmax, uid);
  vector<double> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  int res = 0;
  #ifdef MANUAL_RUN
  //some manual code
  #else
  testing::InitGoogleTest(&argc, argv);
  //testing::InitGoogleMock(&argc, argv);
  res = RUN_ALL_TESTS();
  #endif
  system("pause>nul");
  return res;
}
//---------------------------------------------------------------------------------------------------------------------------------