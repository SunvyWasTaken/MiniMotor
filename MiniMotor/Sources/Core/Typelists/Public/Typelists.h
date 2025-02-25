#pragma once

#include <variant>

template <typename ...Ts>
struct Overloaded : Ts...
{
	using Ts::operator()...;
};

template <class ...Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

template <typename ...Ts>
struct Typelist
{ };

/************************************************************************/
/* TypeIndex															*/
/************************************************************************/

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

template <typename T, typename ...Ts>
struct TypeIndex<T, std::variant<T, Ts...>>
{
	static constexpr int value = 0;
};

template <typename T, typename T2, typename ...Ts>
struct TypeIndex<T, std::variant<T2, Ts...>>
{
	static constexpr int value = 1 + TypeIndex<T, std::variant<Ts...>>::value;
};

/************************************************************************/
/* Get Type at Index													*/
/************************************************************************/

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

/************************************************************************/
/* Type Size List														*/
/************************************************************************/

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

/************************************************************************/
/* Typelist Adder														*/
/************************************************************************/

template <typename T1, typename T2>
struct TypeAdder
{ };

template <typename ...Ts, typename ...Tss>
struct TypeAdder<Typelist<Ts...>, Typelist<Tss...>>
{
	using value = typename Typelist<Ts..., Tss...>;
};
