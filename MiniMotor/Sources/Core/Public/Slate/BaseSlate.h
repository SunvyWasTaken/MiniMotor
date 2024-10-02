
#pragma once

#include "CoreMinimal.h"
#include "Events/Events.h"

namespace Padding
{
	struct MM_API TopLeft {};
	struct MM_API Left {};
	struct MM_API BottomLeft {};
	struct MM_API TopRight {};
	struct MM_API Right {};
	struct MM_API BottomRight {};
	struct MM_API Top {};
	struct MM_API Bottom {};
	struct MM_API Center {};
}

using namespace Padding;

using PaddingType = std::variant<TopLeft, Left, BottomLeft, TopRight, Right, BottomRight, Top, Bottom, Center>;

class MM_API Slate
{
public:
	Slate()
		: m_Size({ 0, 0 })
		, m_Position({ 0, 0 })
	{}
	virtual ~Slate() = default;

	virtual void Update()
	{

	};

	template <typename eventType>
	bool OnEvent(const eventType& event)
	{
		static_assert(IsTypeInList<eventType, AllKeyEvents>::value, "Unsupported type event given to OnEvent");
		return false;
	}

	Slate& SetPosition(const IVec2& position)
	{
		m_Position = position;
		return *this;
	}

	Slate& SetSize(const IVec2& size)
	{
		m_Size = size;
		return *this;
	}

	template <typename paddingType>
	Slate& SetPadding()
	{
		static_assert(IsTypeInVariant<paddingType, PaddingType>::value, "Padding type not supported");
		m_Padding = paddingType();
		return *this;
	}

	PaddingType GetPadding() const { return m_Padding; }

	IVec2* GetPosition() { return &m_Position; }

	IVec2* GetSize() { return &m_Size; }

private:
	IVec2 m_Size;
	IVec2 m_Position;
	PaddingType m_Padding;
};

class MM_EXPORT SText : public Slate
{
public:
	SText()
		: Slate()
		, m_Text("")
	{}
	std::string m_Text;
};

class MM_EXPORT SButton : public Slate
{
public:
	SButton()
		: Slate()
		, m_Text("")
	{}
	std::string m_Text;

	template <typename type, typename ...Args>
	Slate& BindOnPressed(type* target, void(type::* func)(Args...))
	{
		m_OnPressed = std::bind(func, target);
		return *this;
	}

	template <typename ...Args>
	void OnPressed(Args... args)
	{
		m_OnPressed(std::forward<Args>(args)...);
	}

private:
	std::function<void()> m_OnPressed;
};

class MM_EXPORT SEditableText : public Slate
{
public:
	SEditableText()
		: Slate()
		, m_Text("")
	{}
	std::string m_Text;
	char m_Buffer[32];
};

class MM_EXPORT SContainer : public Slate
{
public:
	Slate& AddChild(Slate* slate)
	{
		m_Children.push_back(slate);
		return *this;
	}
	std::vector<Slate*> m_Children;
};
