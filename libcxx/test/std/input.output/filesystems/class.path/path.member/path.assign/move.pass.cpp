//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03

// <filesystem>

// class path

// path& operator=(path&&) noexcept

#include "filesystem_include.hpp"
#include <type_traits>
#include <cassert>

#include "test_macros.h"
#include "count_new.hpp"


int main() {
  using namespace fs;
  static_assert(std::is_nothrow_move_assignable<path>::value, "");
  assert(globalMemCounter.checkOutstandingNewEq(0));
  const std::string s("we really really really really really really really "
                      "really really long string so that we allocate");
  assert(globalMemCounter.checkOutstandingNewEq(1));
  path p(s);
  {
    DisableAllocationGuard g;
    path p2;
    path& pref = (p2 = std::move(p));
    assert(p2.native() == s);
    assert(p.native() != s); // Testing moved from state
    assert(&pref == &p2);
  }
}
