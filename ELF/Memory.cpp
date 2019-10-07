//===- Memory.cpp ---------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include "Memory.h"
using namespace llvm;
using namespace plastic;

BumpPtrAllocator plastic::BAlloc;
StringSaver plastic::Saver{BAlloc};

std::vector<SpecificAllocBase *> plastic::SpecificAllocBase::Instances;

void plastic::freeArena() {
  for (SpecificAllocBase *Alloc : SpecificAllocBase::Instances)
    Alloc->reset();
  BAlloc.Reset();
}
