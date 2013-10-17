#include <gtest/gtest.h>

#include <putty/row.hh>
#include <putty/exception.hh>

using namespace Putty;

class RowMock : public Row
{
public:
  RowMock()
    : Row()
  {
  }

  void set_width(unsigned width)
  {
    Row::set_width(width);
  }

  void set_cell(unsigned col, const std::wstring &characters, Cell::Attributes attr)
  {
    Row::set_cell(col, characters, attr);
  }

  void set_attributes(Attributes attr)
  {
    Row::set_attributes(attr);
  }

  void clear()
  {
    Row::clear();
  }
};

TEST(PuttyRow, Construction)
{
  RowMock row;

  ASSERT_EQ(0, row.get_width());
  ASSERT_EQ(0, row.get_attributes());
}

TEST(PuttyRow, CopyConstructor)
{
  RowMock orig;
  orig.set_width(1);
  orig.set_cell(0, L"abc", 5678);
  orig.set_attributes(0x33);

  RowMock row(orig);
  ASSERT_EQ(L"abc", row.get_cell(0).get_characters());
  ASSERT_EQ(5678, row.get_cell(0).get_attributes());
  ASSERT_EQ(0x33, row.get_attributes());
}

TEST(PuttyRow, Assignment)
{
  RowMock orig;
  orig.set_width(1);
  orig.set_cell(0, L"abc", 5678);
  orig.set_attributes(0x33);

  RowMock row;
  RowMock &res = row = orig;
  ASSERT_EQ(&res, &row);
  ASSERT_EQ(L"abc", row.get_cell(0).get_characters());
  ASSERT_EQ(5678, row.get_cell(0).get_attributes());
  ASSERT_EQ(0x33, row.get_attributes());
}

TEST(PuttyRow, SetWidthInitial)
{
  RowMock row;
  row.set_width(1);

  ASSERT_EQ(1, row.get_width());
  ASSERT_EQ(L"", row.get_cell(0).get_characters());
}

TEST(PuttyRow, SetWidthBigger)
{
  RowMock row;
  row.set_width(1);

  row.set_cell(0, L"Hello", 5678);
  row.set_width(2);

  ASSERT_EQ(2, row.get_width());
  ASSERT_EQ(L"Hello", row.get_cell(0).get_characters());
  ASSERT_EQ(5678, row.get_cell(0).get_attributes());

  ASSERT_EQ(L"", row.get_cell(1).get_characters());
}

TEST(PuttyRow, SetWidthSmaller)
{
  RowMock row;
  row.set_width(2);

  row.set_cell(0, L"Hello", 5678);
  row.set_width(1);

  ASSERT_EQ(1, row.get_width());
  ASSERT_EQ(L"Hello", row.get_cell(0).get_characters());
  ASSERT_EQ(5678, row.get_cell(0).get_attributes());
}

TEST(PuttyRow, SetCell)
{
  RowMock row;
  row.set_width(1);
  row.set_cell(0, L"abc", 5678);

  ASSERT_EQ(L"abc", row.get_cell(0).get_characters());
  ASSERT_EQ(5678, row.get_cell(0).get_attributes());
}

TEST(PuttyRow, SetAttribute)
{
  RowMock row;
  row.set_attributes(0x33);

  ASSERT_EQ(Row::BOTTOM | Row::WRAPPED | Row::WRAPPED_WIDE, row.get_attributes());
  ASSERT_EQ(Row::BOTTOM, row.get_mode());
}

TEST(PuttyRow, Clear)
{
  RowMock row;
  row.set_width(1000);
  row.clear();

  ASSERT_EQ(0, row.get_width());
}

TEST(PuttyRow, SetWidthZero)
{
  RowMock row;
  row.set_width(100);
  row.set_width(0);

  ASSERT_EQ(0, row.get_width());

}

TEST(PuttyRow, AssignEmptyRow)
{
  RowMock orig;
  orig.set_attributes(0x33);

  RowMock copy(orig);

  ASSERT_EQ(0, copy.get_width());
  ASSERT_EQ(0x33, copy.get_attributes());
}
