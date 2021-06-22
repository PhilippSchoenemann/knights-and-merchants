#include "io/FileIo.h"
#include "io/IoException.h"

namespace knights_and_merchants::io
{
	FileIo::FileIo(const std::string & fileName)
		: fileName { fileName }, handle { CreateFile(fileName.c_str(), GENERIC_WRITE | GENERIC_READ, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) }
	{
		if (handle == INVALID_HANDLE_VALUE)
			throw IoException("Can not open the specified file!");
	}

	FileIo::FileIo(FileIo && other) noexcept
		: fileName(std::move(other.fileName)), handle(other.handle) { }

	FileIo & FileIo::operator=(FileIo && other) noexcept
	{
		if (this == &other)
			return *this;

		fileName = std::move(other.fileName);
		handle = other.handle;

		return *this;
	}

	FileIo::~FileIo() noexcept
	{
		const auto fileSize = getFileSize();

		CloseHandle(handle);

		if (fileSize == 0)
			DeleteFile(fileName.c_str());

		reset();
	}

	void FileIo::reset() noexcept
	{
		fileName.clear();
		handle = nullptr;
	}

	void FileIo::read(void * const buffer, const size_t size) const
	{
		DWORD numberOfBytesRead;
		if (ReadFile(handle, buffer, static_cast<DWORD>(size), &numberOfBytesRead, nullptr) == FALSE)
			throw IoException("Can not read the file!");
	}

	void FileIo::write(const void * const buffer, const size_t size) const
	{
		DWORD numberOfBytesWritten;
		if (WriteFile(handle, buffer, static_cast<DWORD>(size), &numberOfBytesWritten, nullptr) == FALSE)
			throw IoException("Can not write the file!");
	}

	void FileIo::overwrite() noexcept
	{
		CloseHandle(handle);
		handle = CreateFile(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	}

	size_t FileIo::getFileSize() const noexcept
	{
		const auto fileSize = GetFileSize(handle, nullptr);
		return fileSize != INVALID_FILE_SIZE ? static_cast<size_t>(fileSize) : 0;
	}
}
