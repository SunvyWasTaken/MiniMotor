
#pragma once

template <typename... Types>
struct Typelist {};

/************************************************************************/
/* GetIndex																*/
/************************************************************************/

template <typename T, typename Typelist>
struct GetTypelistIndex;

template <typename T>
struct GetTypelistIndex<T, Typelist<>>
{
	static const int value = -1;
};

template <typename T, typename... Types>
struct GetTypelistIndex<T, Typelist<T, Types...>>
{
	static const int value = 0;
};

template <typename T, typename First, typename... Rest>
struct GetTypelistIndex<T, Typelist<First, Rest...>>
{
	static const int value = 1 + GetTypelistIndex<T, Typelist<Rest...>>::value;
};
