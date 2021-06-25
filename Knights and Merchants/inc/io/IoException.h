#ifndef KNIGHTS_AND_MERCHANTS_IO_IO_EXCEPTION_H
#define KNIGHTS_AND_MERCHANTS_IO_IO_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace knights_and_merchants::io
{
	/// <summary>
	/// An exception to address IO problems.
	/// </summary>
	class IoException final : public std::runtime_error
	{
	public:

		/// <summary>
		/// Creates an IoException without a message.
		/// </summary>
		IoException() noexcept
			: std::runtime_error { nullptr } { }

		/// <summary>
		/// Creates an IoException with a message.
		/// </summary>
		/// <param name="message">The message of the exception.</param>
		explicit IoException(const std::string & message) noexcept
			: runtime_error { message } { }
	};
}

#endif
