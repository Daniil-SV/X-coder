#pragma once

#include <vector>
#include <cstring>

#include "SupercellBytestream/base/Endian.h"

namespace sc
{
	class BytestreamBase
	{
	protected:
		virtual size_t _read(void* data, size_t dataSize) = 0;
		virtual size_t _write(const void* data, size_t dataSize) = 0;

	public:
		virtual ~BytestreamBase() {};

		virtual uint32_t tell() = 0;
		virtual void seek(uint32_t pos) = 0;

		virtual uint32_t size() = 0;

		virtual void close() = 0;

		bool eof()
		{
			return size() <= tell();
		};

		void skip(uint32_t length)
		{
			if (length + tell() > size())
				seek(size());
			else
				seek(tell() + length);
		}

		size_t read(void* data, size_t dataSize) {
			if (!closed && !eof()) {
				return _read(data, dataSize);
			} else {
				return 0;
			}
		};

		size_t write(const void* data, size_t dataSize) {
			if (!closed) {
				return _write(data, dataSize);
			} else {
				return 0;
			}
		};

	protected:
		bool closed = false;
	};
}