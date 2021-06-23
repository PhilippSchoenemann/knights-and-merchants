#ifndef KNIGHTS_AND_MERCHANTS_TEXT_LIB_H
#define KNIGHTS_AND_MERCHANTS_TEXT_LIB_H

#include <string>
#include <vector>
#include <numeric>

namespace knights_and_merchants::text
{
	using std::accumulate;
	using std::istream;
	using std::ostream;
	using std::string;
	using std::vector;

	/// <summary>
	/// Represents a managed collection of strings.
	/// </summary>
	class Lib
	{
		friend istream & operator>>(istream &, Lib &);
		friend ostream & operator<<(ostream &, const Lib &);

	public:

		/// <summary>
		/// Creates an empty library.
		/// </summary>
		Lib() noexcept = default;

		/// <summary>
		/// Loads an existing library.
		/// </summary>
		/// <param name="fileName">The path to the existing library file.</param>
		explicit Lib(const string & fileName);

		/// <summary>
		/// Gets the string count.
		/// </summary>
		/// <returns>The string count.</returns>
		[[nodiscard]]
		vector<string>::size_type getStringCount() const noexcept
		{
			return strings.size();
		}

		/// <summary>
		/// Gets the accumulated size of all strings.<br />
		/// For each string that is not empty, an additional null terminator is considered.
		/// </summary>
		/// <returns>The accumulated size of all strings.</returns>
		[[nodiscard]]
		string::size_type getTotalSize() const noexcept;

		/// <summary>
		/// Gets the i-th string.
		/// </summary>
		/// <param name="i">The index of the string to get.</param>
		/// <returns>The i-th string.</returns>
		[[nodiscard]]
		const string & at(const int i) const noexcept
		{
			return strings[i];
		}

		/// <summary>
		/// Gets the i-th string.
		/// </summary>
		/// <param name="i">The index of the string to get.</param>
		/// <returns>The i-th string.</returns>
		[[nodiscard]]
		const string & operator[](const int i) const noexcept
		{
			return at(i);
		}

		/// <summary>
		/// Appends a new string.
		/// </summary>
		/// <param name="str">The string to append.</param>
		/// <returns>The index of the appended string.</returns>
		int append(string && str);

		/// <summary>
		/// Appends a new string.
		/// </summary>
		/// <param name="str">The string to append.</param>
		/// <returns>The index of the appended string.</returns>
		int append(const string & str);

		/// <summary>
		/// Removes a string at the specified index.
		/// </summary>
		void removeAt(int i) noexcept;

		/// <summary>
		/// Removes all empty strings.
		/// </summary>
		void removeAllEmpty() noexcept;

		/// <summary>
		/// Adds a string.<br />
		/// (1) Replaces the first empty string.<br />
		/// (2) If there is no empty string, the string is appended.
		/// </summary>
		/// <param name="str">The string to be added.</param>
		/// <returns>The index of the string.</returns>
		int add(const string & str);

		/// <summary>
		/// Replaces the i-th string.
		/// </summary>
		/// <param name="i">The index of the string to be replaced.</param>
		/// <param name="str">The new string.</param>
		void replaceAt(int i, const string & str);

		/// <summary>
		/// Removes all strings.
		/// </summary>
		void clear() noexcept;

	private:

		/// <summary>
		/// Gets the index of the last string.
		/// </summary>
		/// <returns>The index of the last string.</returns>
		[[nodiscard]]
		int lastIndex() const noexcept
		{
			return static_cast<int>(getStringCount() - 1);
		}

		vector<string> strings;
	};

	istream & operator>>(istream &, Lib &);
	ostream & operator<<(ostream &, const Lib &);
}

#endif
