#pragma once

#include "SupercellFlash/objects/DisplayObject.h"
#include "SupercellFlash/Tags.h"

#include <cstdint>
#include <memory>

using namespace std;

namespace sc
{
	class SupercellSWF;

	class MovieClipModifier : public DisplayObject
	{
	public:
		enum class Type : uint8_t
		{
			Mask = TAG_MOVIE_CLIP_MODIFIER,
			Masked,
			Unmasked,
		};

		MovieClipModifier* load(SupercellSWF* swf, uint8_t tag);
		void save(SupercellSWF* swf);

	public:
		Type type() { return m_type; };
		void type(Type type) { m_type = type; }

	private:
		Type m_type = Type::Mask;

		uint8_t getTag();
	};

	typedef std::shared_ptr<MovieClipModifier> pMovieClipModifier;
}
