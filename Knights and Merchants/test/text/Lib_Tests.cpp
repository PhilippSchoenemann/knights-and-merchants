#include <fstream>

#include <gtest/gtest.h>

#include "text/Lib.h"

using knights_and_merchants::text::Lib;

TEST(LibTests, a_new_created_lib_is_empty)
{
	const Lib sut { };

	EXPECT_EQ(sut.getStringCount(), 0);
	EXPECT_EQ(sut.getTotalSize(), 0);
}

TEST(LibTests, a_cleared_lib_is_empty)
{
	// Arrange
	Lib sut { };

	sut.append("First");
	sut.append("Second");
	sut.append("Third");

	// Act
	sut.clear();

	// Assert
	EXPECT_EQ(sut.getStringCount(), 0);
	EXPECT_EQ(sut.getTotalSize(), 0);
}

TEST(LibTests, remove_all_empty_strings)
{
	// Arrange
	Lib sut { };

	sut.append("First");
	sut.append("");
	sut.append("");
	sut.append("Second");
	sut.append("");
	sut.append("Third");
	sut.append("");
	sut.append("");

	// Act
	sut.removeAllEmpty();

	// Assert
	EXPECT_EQ(sut.getStringCount(), 3);
	EXPECT_EQ(sut.getTotalSize(), 19);
	EXPECT_STREQ(sut[0].c_str(), "First");
	EXPECT_STREQ(sut[1].c_str(), "Second");
	EXPECT_STREQ(sut[2].c_str(), "Third");
}

TEST(LibTests, if_there_are_enough_empty_strings_added_strings_should_not_be_appended)
{
	// Arrange
	Lib sut { };

	sut.append("First");
	sut.append("");
	sut.append("Second");
	sut.append("Third");
	sut.append("");

	// Act
	const auto index1 = sut.add("New");
	const auto index2 = sut.add("String");

	// Assert
	EXPECT_EQ(sut.getStringCount(), 5);
	EXPECT_EQ(sut.getTotalSize(), 30);
	EXPECT_STREQ(sut[index1].c_str(), "New");
	EXPECT_STREQ(sut[index2].c_str(), "String");
}

TEST(LibTests, add_an_empty_string)
{
	Lib sut { };

	sut.append("");

	EXPECT_EQ(sut.getStringCount(), 1);
	EXPECT_EQ(sut.getTotalSize(), 0);
}

TEST(LibTests, add_a_string)
{
	Lib sut { };

	const auto index = sut.append("Test");

	EXPECT_EQ(sut.getStringCount(), 1);
	EXPECT_EQ(sut.getTotalSize(), 5);
	EXPECT_STREQ(sut.at(index).c_str(), "Test");
}

TEST(LibTests, remove_string)
{
	// Arrange
	Lib sut { };

	sut.append("First");
	const auto index = sut.append("Second");
	sut.append("Third");

	// Act
	sut.removeAt(index);

	// Assert
	EXPECT_EQ(sut.getStringCount(), 2);
	EXPECT_EQ(sut.getTotalSize(), 12);
	EXPECT_STREQ(sut.at(index).c_str(), "Third");
}

TEST(LibTests, replace_an_empty_string_with_non_empty_string)
{
	Lib sut { };

	const auto index = sut.append("");
	sut.replaceAt(index, "Test");

	EXPECT_EQ(sut.getStringCount(), 1);
	EXPECT_EQ(sut.getTotalSize(), 5);
	EXPECT_STREQ(sut.at(index).c_str(), "Test");
}

TEST(LibTests, replace_non_empty_string_with_an_empty_string)
{
	Lib sut { };

	const auto index = sut.append("Test");
	sut.replaceAt(index, "");

	EXPECT_EQ(sut.getStringCount(), 1);
	EXPECT_EQ(sut.getTotalSize(), 0);
	EXPECT_STREQ(sut.at(index).c_str(), "");
}

TEST(LibTests, replace_non_empty_string_with_non_empty_string)
{
	Lib sut { };

	const auto index = sut.append("Test");
	sut.replaceAt(index, "Changed");

	EXPECT_EQ(sut.getStringCount(), 1);
	EXPECT_EQ(sut.getTotalSize(), 8);
	EXPECT_STREQ(sut.at(index).c_str(), "Changed");
}

TEST(LibTests, read_kam_setupLib)
{
	const Lib sut { "./data/misc/setup.lib" };

	EXPECT_EQ(sut.getStringCount(), 400);
	EXPECT_EQ(sut.getTotalSize(), 16748);
	EXPECT_STREQ(sut.at(0).c_str(), "unused");
	EXPECT_STREQ(sut.at(363).c_str(), "              Mission 14\r|\r|We have arrived at last bastion of our enemy. They have brougth the rest of their armies together and barricaded themselves into their final retreat, northeast from here. Due to the freezing cold, the river is partly frozen, and offers us a possibility of surprising our opposition. Defeat the remaining enemy troops, so that peace can return to our land!");
	EXPECT_STREQ(sut.at(399).c_str(), "");
}
