#include <gtest/gtest.h>

#include "io/FileIo.h"
#include "io/IoException.h"

using knights_and_merchants::io::FileIo;
using knights_and_merchants::io::IoException;

TEST(FileIoTests, abort_if_the_file_name_is_invalid)
{
	EXPECT_THROW(const FileIo sut { "" }, IoException);
}
