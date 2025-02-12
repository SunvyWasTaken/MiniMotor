#pragma once

template <typename ...Ts>
struct Typelist
{ };

template <typename T, typename T2>
struct TypeIndex
{
};

template <typename T, typename ...Ts>
struct TypeIndex<T, Typelist<T, Ts...>>
{
	static constexpr int value = 0;
};

template <typename T, typename T2, typename ...Ts>
struct TypeIndex<T, Typelist<T2, Ts...>>
{
	static constexpr int value = 1 + TypeIndex<T, Typelist<Ts...>>::value;
};

template <int i, typename ...Ts>
struct GetTypeAtIndex
{ };

template <typename T, typename ...Ts>
struct GetTypeAtIndex<0, Typelist<T, Ts...>>
{
	using value = T;
};

template <int i, typename T, typename ...Ts>
struct GetTypeAtIndex<i, Typelist<T, Ts...>>
{
	using value = typename GetTypeAtIndex<i - 1, Typelist<Ts...>>::value;
};

template <typename T>
struct TypelistSize
{ };

template <typename T, typename ...Ts>
struct TypelistSize<Typelist<T, Ts...>>
{
	static constexpr int value = 1 + TypelistSize<Typelist<Ts...>>::value;
};

template <typename T>
struct TypelistSize<Typelist<T>>
{
	static constexpr int value = 1;
};
