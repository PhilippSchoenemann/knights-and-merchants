#ifndef KNIGHTS_AND_MERCHANTS_IO_FILEIO_H
#define KNIGHTS_AND_MERCHANTS_IO_FILEIO_H

#include <string>
#include <Windows.h>

namespace knights_and_merchants::io
{
	class FileIo
	{
	public:
		explicit FileIo(const std::string & fileName);

		FileIo(const FileIo &) = delete;

		FileIo(FileIo && other) noexcept;

		FileIo & operator=(const FileIo &) = delete;

		FileIo & operator=(FileIo && other) noexcept;

		~FileIo() noexcept;

		void overwrite() noexcept;

		[[nodiscard]]
		size_t getFileSize() const noexcept;

		void read(void * buffer, size_t size) const;

		void write(const void * buffer, size_t size) const;

	private:
		void reset() noexcept;

		std::string fileName;
		HANDLE handle;
	};
}

#endif
