#pragma once

namespace Sunset
{
	namespace ShaderDataType
	{
		 struct Float{}; struct Float2{}; struct Float3{}; struct Float4{}; struct Mat3{}; struct Mat4{}; struct Int{}; struct Int2{}; struct Int3{}; struct Int4{}; struct Bool{};
		 using Type = std::variant<Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool>;
	};

	struct BufferElement
	{
		BufferElement(ShaderDataType::Type type = ShaderDataType::Bool(), const std::string& name = "", bool normalized = false);

		uint32_t GetComponentCount() const;

		std::string Name;
		ShaderDataType::Type Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
	};

	class BufferLayout
	{
		using BufferElements = std::vector<BufferElement>;
	public:
		BufferLayout();

		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline uint32_t GetStride() const { return m_Stride; }
		inline const BufferElements& GetElements() const { return m_Elements; }

		BufferElements::iterator begin() { return m_Elements.begin(); }
		BufferElements::iterator end() { return m_Elements.end(); }
		BufferElements::const_iterator begin() const { return m_Elements.begin(); }
		BufferElements::const_iterator end() const { return m_Elements.end(); }

	private:

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		BufferElements m_Elements;
		uint32_t m_Stride;
	};
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		static VertexBuffer* Create(float* vertices, size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer();
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, size_t count);
	};
}
