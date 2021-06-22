#ifndef KNIGHTS_AND_MERCHANTS_IO_IOEXCEPTION_H
#define KNIGHTS_AND_MERCHANTS_IO_IOEXCEPTION_H

#include <stdexcept>
#include <string>

namespace knights_and_merchants::io
{
	using std::runtime_error;
	using std::string;

	/// <summary>
	/// An exception to address IO problems.
	/// </summary>
	class IoException final : public runtime_error
	{
	public:

		/// <summary>
		/// Creates an IoException without a message.
		/// </summary>
		IoException() noexcept
			: runtime_error { nullptr } { }

		/// <summary>
		/// Creates an IoException with a message.
		/// </summary>
		/// <param name="message">The message of the exception.</param>
		explicit IoException(const string & message) noexcept
			: runtime_error { message } { }
	};
}

#endif
