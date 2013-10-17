#include <gtest/gtest.h>

#include <sys/time.h>
#include <stdio.h>

#include <putty/cell.hh>

using namespace Putty;

typedef unsigned long Character;

class CellMock : public Cell
{
public:
  CellMock()
    : Cell()
  {}

  CellMock(const std::wstring &characters, Attributes attr)
    : Cell(characters, attr)
  {}

  void set(const std::wstring &characters, Attributes attr)
  {
    Cell::set(characters, attr);
  }
};

TEST(PuttyCell, Construction)
{
  CellMock init_default;
  CellMock init_cell(L"a", 5678);
  ASSERT_EQ(L"a", init_cell.get_characters());
  ASSERT_EQ(5678, init_cell.get_attributes());

  CellMock copy(init_cell);
  ASSERT_EQ(L"a", copy.get_characters());
  ASSERT_EQ(5678, copy.get_attributes());

  CellMock assigned;
  CellMock &result = assigned = init_cell;
  ASSERT_EQ(&result, &assigned);
  ASSERT_EQ(L"a", assigned.get_characters());
  ASSERT_EQ(5678, assigned.get_attributes());
}

TEST(PuttyCell, ConstructionWithCombiningCharacters)
{
  std::wstring combining_characters = L"abc";
  CellMock init_cell(combining_characters, 5678);
  ASSERT_EQ(L"abc", init_cell.get_characters());
  ASSERT_EQ(5678, init_cell.get_attributes());

  CellMock copy(init_cell);
  ASSERT_EQ(L"abc", copy.get_characters());
  ASSERT_EQ(5678, copy.get_attributes());

  CellMock assigned;
  CellMock &result = assigned = init_cell;
  ASSERT_EQ(&result, &assigned);
  ASSERT_EQ(L"abc", assigned.get_characters());
  ASSERT_EQ(5678, assigned.get_attributes());
}


TEST(PuttyCell, Set)
{
  CellMock set_cell;
  set_cell.set(L"a", 5678);
  ASSERT_EQ(L"a", set_cell.get_characters());
  ASSERT_EQ(5678, set_cell.get_attributes());

  CellMock set_cell_with_combining;
  set_cell_with_combining.set(L"abc", 5678);
  ASSERT_EQ(L"abc", set_cell_with_combining.get_characters());
  ASSERT_EQ(5678, set_cell_with_combining.get_attributes());
}

TEST(PuttyCell, FlagAttributes)
{
  CellMock cell(L"", CellMock::NARROW | CellMock::BOLD | CellMock::REVERSE);
  ASSERT_TRUE(cell.narrow());
  ASSERT_FALSE(cell.wide());
  ASSERT_TRUE(cell.bold());
  ASSERT_FALSE(cell.under());
  ASSERT_TRUE(cell.reverse());
  ASSERT_FALSE(cell.blink());

  cell.set(L"", CellMock::WIDE | CellMock::UNDER | CellMock::BLINK);
  ASSERT_FALSE(cell.narrow());
  ASSERT_TRUE(cell.wide());
  ASSERT_FALSE(cell.bold());
  ASSERT_TRUE(cell.under());
  ASSERT_FALSE(cell.reverse());
  ASSERT_TRUE(cell.blink());
}

TEST(PuttyCell, Foreground)
{
  // Check XTerm foreground color with value=29
  CellMock cell(L"", (29) << CellMock::FgColorShift);
  ASSERT_EQ(29, cell.foreground_code());
  ASSERT_EQ(0, cell.background_code());
}

TEST(PuttyCell, Background)
{
  // Check XTerm background color with value=65
  CellMock cell(L"", (65) << CellMock::BgColorShift);
  ASSERT_EQ(0, cell.foreground_code());
  ASSERT_EQ(65, cell.background_code());
}
