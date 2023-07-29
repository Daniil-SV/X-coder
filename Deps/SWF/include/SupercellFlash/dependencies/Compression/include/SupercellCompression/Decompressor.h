#pragma once

#include <string>

#include "SupercellCompression/Signature.h"
#include "SupercellBytestream.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace sc
{
	class Decompressor
	{
	public:
		/**
		 * Decompress file and then store it in cache, without need to decompress in the future.
		 */
		static bool decompress(const fs::path& filepath, fs::path& outFilepath);

		/**
		 * Decompress file from stream.
		 */
		static bool decompress(Bytestream& inStream, Bytestream& outStream);

		/**
		 * Decompress assets like .csv or other compressed assets
		 */
		static void commonDecompress(Bytestream& inStream, Bytestream& outStream);

	private:
		static bool getHeader(Bytestream& inputSteam, CompressionSignature& signature, std::vector<uint8_t>& hash);
		static void commonDecompress(Bytestream& inStream, Bytestream& outStream, CompressionSignature signature);
	};
}
