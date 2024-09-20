
#pragma once

#define CRTP_CALL_Impl(type, func_name) void func_name() { type* tmp = static_cast<type*>(this); tmp->func_name(); }
#define CRTP_CALL_OneParam_Impl(type, func_name, Param1Type) void func_name(Param1Type Param1) { type* tmp = static_cast<type*>(this); tmp->func_name(Param1); }
#define CRTP_CALL_TwoParam_Impl(type, func_name, Param1Type, Param2Type) void func_name(Param1Type Param1, Param2Type Param2) { type* tmp = static_cast<type*>(this); tmp->func_name(Param1, Param2); }

#define CRTP_CALL_ret_Impl(type, ret_type, func_name) ret_type func_name() { type* tmp = static_cast<type*>(this); return tmp->func_name(); }

#define CRTP_CALL(func_name) CRTP_CALL_Impl(Derived, func_name)
#define CRTP_CALL_OneParam(func_name, Param1Type) CRTP_CALL_OneParam_Impl(Derived, func_name, Param1Type)
#define CRTP_CALL_TwoParam(func_name, Param1Type, Param2Type) CRTP_CALL_TwoParam_Impl(Derived, func_name, Param1Type, Param2Type)

#define CRTP_CALL_ret(returnType, func_name) CRTP_CALL_ret_Impl(Derived, returnType, func_name)

#define CRTP_CALL_Variadic(crtpType, func_name, ...) \
template <typename ...types> \
void func_name(types... args) { crtpType* tmp = static_cast<crtpType*>(this); tmp->func_name(args...); }
