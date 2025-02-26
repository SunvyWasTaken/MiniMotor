#pragma once

#ifdef MiniMotor_EXPORTS
#define MM_API __declspec(dllexport)
#define MM_EXPORT MM_API
#else
#define MM_API __declspec(dllimport)
#define MM_EXPORT
#endif // MiniMotor_EXPORTS

#define RET_CRTP(x, returnType) returnType x() { DerivedPtr tmp = static_cast<DerivedPtr>(this); return tmp->x(); }
#define RET_CONST_CRTP(x, returnType) returnType x() { const DerivedPtr tmp = static_cast<const DerivedPtr>(this); return tmp->x(); }
#define VAR_RET_CRTP(x, returnType) template <typename ...Args> returnType x(Args&&... args) { DerivedPtr tmp = static_cast<DerivedPtr>(this); return tmp->x(std::forward<Args>(args)...); }

#define CRTP(x) RET_CRTP(x, void)
#define CRTP_VAR(x) VAR_RET_CRTP(x, void)
