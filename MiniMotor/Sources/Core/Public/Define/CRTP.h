// Copyright Shimmer Studios : All rights reserved.

#pragma once

#define CRTP_RETURN_Impl(derivedType, returnType, func_name) returnType func_name() { derivedType* tmp = static_cast<derivedType*>(this); return tmp->func_name(); }
#define CRTP_RETURN_ARGS_Impl(derivedType, returnType, func_name) template<typename ...Args> returnType func_name(Args&& ...args) { derivedType* tmp = static_cast<derivedType*>(this); return tmp->func_name(std::forward<Args>(args)...); }

#define CRTP(func_name) CRTP_RETURN_Impl(Derived, void, func_name)
#define CRTP_Params(func_name) CRTP_RETURN_ARGS_Impl(Derived, void, func_name)
#define CRTP_ret(returnType, func_name) CRTP_RETURN_Impl(Derived, returnType, func_name)
#define CRTP_Params_ret(returnType, func_name) CRTP_RETURN_ARGS_Impl(Derived, returnType, func_name)

