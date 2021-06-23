#include <algorithm>
#include <fstream>

#include "text/Lib.h"
#include "io/IoException.h"

using std::ifstream;
using std::ios;
using std::remove_if;

using knights_and_merchants::io::IoException;

namespace knights_and_merchants::text
{
	Lib::Lib(const string & fileName)
	{
		ifstream stream { fileName, ios::binary };

		if (!stream.is_open())
			throw IoException("Unable to open file!");

		stream >> *this;
	}

	string::size_type Lib::getTotalSize() const noexcept
    {
		return accumulate(strings.cbegin(), strings.cend(), 0, [] (auto sum, const auto & str)
		{
			if (!str.empty())
				sum += str.length() + sizeof '\0';

			return sum;
		});
	}

	int Lib::append(const string & str)
	{
		strings.emplace_back(str);
		return lastIndex();
	}

	int Lib::append(string && str)
	{
		strings.emplace_back(move(str));
		return lastIndex();
	}

	void Lib::replaceAt(const int i, const string & str)
	{
		strings[i] = str;
	}

	void Lib::clear() noexcept
    {
		strings.clear();
	}

	void Lib::removeAt(const int i) noexcept
    {
		strings.erase(strings.cbegin() + i);
	}

	void Lib::removeAllEmpty() noexcept
    {
		strings.erase(
			remove_if(strings.begin(), strings.end(), [] (const auto & str)
			{
				return str.empty();
			}),
			strings.end()
		);
	}

	int Lib::add(const string & str)
	{
		const auto it = find(strings.begin(), strings.end(), "");

		if (it == strings.end())
			return append(str);

		*it = str;
		return static_cast<int>(it - strings.begin());
	}

	istream & operator>>(istream & stream, Lib & instance)
	{
		uint16_t stringCount;
		stream.read(reinterpret_cast<char *>(&stringCount), sizeof stringCount);

		uint32_t textSize;
		stream.read(reinterpret_cast<char *>(&textSize), sizeof textSize);

		auto * offsets = new uint16_t[stringCount];
		stream.read(reinterpret_cast<char *>(offsets), stringCount * sizeof(uint16_t));

		for (auto i = 0; i < stringCount; ++i) {
			const auto offset = offsets[i];

			if (offset == UINT16_MAX)
				instance.append("");
			else {
				std::string str;
				std::getline(stream, str, '\0');

				instance.append(str);
			}
		}

		delete[] offsets;
		return stream;
	}

	ostream & operator<<(ostream & stream, const Lib & instance)
	{
		auto stringCount = static_cast<uint16_t>(instance.getStringCount());
		stream.write(reinterpret_cast<const char *>(&stringCount), sizeof stringCount);

		auto totalSize = static_cast<uint32_t>(instance.getTotalSize());
		stream.write(reinterpret_cast<const char *>(&totalSize), sizeof totalSize);

		uint16_t offset = 0;
		for (const auto & str : instance.strings) {
			if (str.empty()) {
				stream.put(-1).put(-1);
			} else {
				stream.write(reinterpret_cast<const char *>(&offset), sizeof offset);
				offset += str.length() + sizeof '\0';
			}
		}

		for (const auto & str : instance.strings)
			if (!str.empty())
				stream << str << '\0';

		return stream;
	}
}
