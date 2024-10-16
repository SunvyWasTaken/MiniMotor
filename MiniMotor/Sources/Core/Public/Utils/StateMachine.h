// Copyright Shimmer Studios : All rights reserved.

#pragma once

#define MAKE_STATE(StateName) struct MM_API StateName {};

#define MAKE_STATE_MACHINE(StateMachineName, ...) using StateMachineName = std::variant<__VA_ARGS__>;

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
