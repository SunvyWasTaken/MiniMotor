// Copyright Shimmer Studios : All rights reserved.

#pragma once

#define MAKE_STATE(StateName) struct MM_API StateName {};

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
