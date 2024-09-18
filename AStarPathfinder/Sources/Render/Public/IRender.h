#pragma once

#define CRTP_CALL(type, func_name) void func_name() { type* tmp = static_cast<type*>(this); tmp->func_name(); }
#define CRTP_CALL_OneParam(type, func_name, Param1Type) void func_name(Param1Type Param1) { type* tmp = static_cast<type*>(this); tmp->func_name(Param1); }

#define CRTP_CALL_ret(type, ret_type, func_name) ret_type func_name() { type* tmp = static_cast<type*>(this); return tmp->func_name(); }

#define CRTP_CALL_type(func_name) CRTP_CALL(type, func_name)
#define CRTP_CALL_type_OneParam(func_name, Param1Type) CRTP_CALL_OneParam(type, func_name, Param1Type)

#define CRTP_CALL_ret_type(returnType, func_name) CRTP_CALL_ret(type, returnType, func_name)

template <typename type>
class IDraw
{
public:

	CRTP_CALL_type(Init)
		CRTP_CALL_type(Draw)
		CRTP_CALL_ret_type(bool, IsWindowOpen)
		CRTP_CALL_type_OneParam(BufferFrame, class IEntity*)
		CRTP_CALL_type(ClearWindow)
		CRTP_CALL_type(CloseWindow)

	class IWorld* World = nullptr;
};
