#pragma once

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "io/SWFStream.h"

#include "SupercellFlash/objects/Shape.h"
#include "SupercellFlash/objects/MovieClip.h"
#include "SupercellFlash/objects/TextField.h"
#include "SupercellFlash/objects/MovieClipModifier.h"
#include "SupercellFlash/objects/ExportName.h"
#include "SupercellFlash/texture/SWFTexture.h"

#include "SupercellFlash/transformation/MatrixBank.h"

#include "SupercellFlash/Tags.h"

#define MULTIRES_DEFAULT_SUFFIX "_highres"
#define LOWRES_DEFAULT_SUFFIX "_lowres"

using namespace std;

#include <filesystem>
namespace fs = filesystem;

namespace sc
{
	class SupercellSWF
	{
	public:
		std::vector<pExportName> exports;
		vector<pMatrixBank> matrixBanks;

		std::vector<pSWFTexture> textures;
		std::vector<pShape> shapes;
		std::vector<pMovieClip> movieClips;
		std::vector<pTextField> textFields;
		std::vector<pMovieClipModifier> movieClipModifiers;

	public:
		void load(const fs::path& filePath);
		bool loadInternal(const fs::path& filepath, bool isTexture);

		void save(const fs::path& filepath, CompressionSignature signature);

		SWFStream stream;

	public:
		bool useExternalTexture() { return m_useExternalTexture; }

		bool useMultiResTexture() { return m_useMultiResTexture; }
		bool useLowResTexture() { return m_useLowResTexture; }

		std::string multiResFileSuffix() { return m_multiResFileSuffix; }
		std::string lowResFileSuffix() { return m_lowResFileSuffix; }

		bool usePrecisionMatrices() { return m_usePrecisionMatrices; }

	public:
		void useExternalTexture(bool status) { m_useExternalTexture = status; }

		void useMultiResTexture(bool status) { m_useMultiResTexture = status; }
		void useLowResTexture(bool status) { m_useLowResTexture = status; }

		void multiResFileSuffix(std::string postfix) { m_multiResFileSuffix = postfix; }
		void lowResFileSuffix(std::string postfix) { m_lowResFileSuffix = postfix; }

		void usePrecisionMatrices(bool status) { m_usePrecisionMatrices = status; }

	private:
		bool loadTags();

		void saveInternal();
		void saveTags(
			uint16_t shapeCount,
			uint16_t movieClipsCount,
			uint16_t texturesCount,
			uint16_t textFieldsCount
		);

		void initMatrixBank(uint16_t matricesCount, uint16_t colorTransformsCount);

	private:
		bool m_useExternalTexture = false;
		bool m_useMultiResTexture = false;

		bool m_useLowResTexture = true;

		bool m_usePrecisionMatrices = false;

		std::string m_multiResFileSuffix = MULTIRES_DEFAULT_SUFFIX;
		std::string m_lowResFileSuffix = LOWRES_DEFAULT_SUFFIX;
	};
}
