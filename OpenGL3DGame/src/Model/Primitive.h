#pragma once

namespace OG3D
{
	class Primitive
	{
	public:
		virtual const unsigned int GetVerticesCount() const = 0;
		virtual const unsigned int GetIndicesCount() const = 0;
		virtual const float* GetVertices() const = 0;
		virtual const unsigned int* GetIndices() const = 0;

	protected:
		Primitive() = default;
		virtual ~Primitive() = default;
	};
}