// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include <variant>

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

/************************************************************************/
/* TypelistSize															*/
/************************************************************************/

template <typename Typelist>
struct GetSizelist;

template <>
struct GetSizelist<Typelist<>>
{
	static const int value = 0;
};

template <typename T, typename... Types>
struct GetSizelist<Typelist<T, Types...>>
{
	static const int value = 1 + GetSizelist<Typelist<Types...>>::value;
};

/************************************************************************/
/* CheckIfTypeIsInList													*/
/************************************************************************/

template <typename T, typename Typelist>
struct IsTypeInList;

template <typename T>
struct IsTypeInList<T, Typelist<>>
{
	static const bool value = false;
};

template <typename T, typename... Types>
struct IsTypeInList<T, Typelist<T, Types...>>
{
	static const bool value = true;
};

template <typename T, typename First, typename... Rest>
struct IsTypeInList<T, Typelist<First, Rest...>>
{
	static const bool value = IsTypeInList<T, Typelist<Rest...>>::value;
};

template <typename T, typename Typelist>
struct IsTypeInVariant;

template <typename T>
struct IsTypeInVariant<T, std::variant<>>
{
	static const bool value = false;
};

template <typename T, typename... Types>
struct IsTypeInVariant<T, std::variant<T, Types...>>
{
	static const bool value = true;
};

template <typename T, typename First, typename... Rest>
struct IsTypeInVariant<T, std::variant<First, Rest...>>
{
	static const bool value = IsTypeInVariant<T, std::variant<Rest...>>::value;
};
