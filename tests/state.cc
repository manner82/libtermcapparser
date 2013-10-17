#include <gtest/gtest.h>

#include <putty/state.hh>
#include <putty/exception.hh>

using namespace Putty;

#define ABS(x) ((x) > 0 ? (x) : -(x))

class StateMock : public State
{
public:
  StateMock()
    : State()
  {}

  void set_cell(unsigned row, unsigned col, const std::wstring &characters, Cell::Attributes attr)
  { State::set_cell(row, col, characters, attr); }

  void resize(unsigned width, unsigned height, unsigned buffer_size)
  { State::resize(width, height, buffer_size); }

  void set_palette(const Palette &palette)
  { State::set_palette(palette); }
};

class TestState : public ::testing::Test
{
public:
  void SetUp()
  {
    palette.set_color(1, 2, 3, 4);

    state = new StateMock();
    state->resize(1024, 768, 128);
    state->set_palette(palette);

    for (int row = -128; row != state->get_height(); ++row)
      {
        for (unsigned col = 0; col != state->get_width(); ++col)
          {
            std::wstring characters;
            characters.push_back( (ABS(row) << 16) | col );
            state->set_cell(row, col, characters, (col << 16) | ABS(row));
          }
      }
  }

  void TearDown()
  {
    delete state;
  }

  StateMock *state;
  Palette palette;
};

TEST_F(TestState, Width)
{
  ASSERT_EQ(1024, state->get_width());
}

TEST_F(TestState, Height)
{
  ASSERT_EQ(768, state->get_height());
}

TEST_F(TestState, BufferSize)
{
  ASSERT_EQ(128, state->get_buffer_size());
}

TEST_F(TestState, GetCell)
{
  for (int row = -128; row != state->get_height(); ++row)
    {
      for (unsigned col = 0; col != state->get_width(); ++col)
        {
          const Cell &cell = state->get_cell(row, col);
          ASSERT_EQ((ABS(row) << 16) | col, cell.get_characters()[0]) << "Invalid cell character in row " << row << " column " << col;
          ASSERT_EQ(((col << 16) | ABS(row)) & Cell::ValidMask, cell.get_attributes()) << "Invalid cell attribute in row " << row << " column " << col;
        }
    }
}

TEST_F(TestState, GetRow)
{
  for (int row = -128; row != state->get_height(); ++row)
    {
      const Row &termrow = state->get_row(row);
      for (unsigned col = 0; col != state->get_width(); ++col)
        {
          const Cell &cell = termrow.get_cell(col);
          ASSERT_EQ((ABS(row) << 16) | col, cell.get_characters()[0]) << "Invalid cell character in row " << row << " column " << col;
          ASSERT_EQ(((col << 16) | ABS(row)) & Cell::ValidMask, cell.get_attributes()) << "Invalid cell attribute in row " << row << " column " << col;
        }
    }
}

TEST_F(TestState, GetPalette)
{
  const Palette &pal = state->get_palette();

  ASSERT_EQ("#020304", pal.lookup(1).as_hex());
}

TEST_F(TestState, ResizeBigger)
{
  int old_height = state->get_height();
  int old_width = state->get_width();
  int old_buffer_size = state->get_buffer_size();

  state->resize(2048, 1024, 256);

  for (int row = -old_buffer_size; row != old_height; ++row)
    {
      const Row &termrow = state->get_row(row);
      for (unsigned col = 0; col != old_width; ++col)
        {
          const Cell &cell = termrow.get_cell(col);
          ASSERT_EQ((ABS(row) << 16) | col, cell.get_characters()[0]) << "Invalid cell character in row " << row << " column " << col;
          ASSERT_EQ(((col << 16) | ABS(row)) & Cell::ValidMask, cell.get_attributes()) << "Invalid cell attribute in row " << row << " column " << col;
        }
    }
}

TEST_F(TestState, ResizeSmaller)
{
  state->resize(512, 128, 16);

  for (int row = -16; row != state->get_height(); ++row)
    {
      const Row &termrow = state->get_row(row);
      for (unsigned col = 0; col != state->get_width(); ++col)
        {
          const Cell &cell = termrow.get_cell(col);
          ASSERT_EQ((ABS(row) << 16) | col, cell.get_characters()[0]) << "Invalid cell character in row " << row << " column " << col;
          ASSERT_EQ(((col << 16) | ABS(row)) & Cell::ValidMask, cell.get_attributes()) << "Invalid cell attribute in row " << row << " column " << col;
        }
    }
}
