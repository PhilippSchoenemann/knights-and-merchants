#include <gtest/gtest.h>

#include "io/FileIO.h"
#include "io/IoException.h"

using knights_and_merchants::io::FileIo;
using knights_and_merchants::io::IoException;

TEST(suiteFileIO, throw_if_file_name_is_invalid)
{
	EXPECT_THROW(FileIo sut { "" }, IoException);
}
