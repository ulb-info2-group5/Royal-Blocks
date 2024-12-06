#ifndef GRID_CELL_HPP
#define GRID_CELL_HPP

#include <optional>

class GridCell {
  private:
    bool isEmpty_ = true;
    std::optional<unsigned> colorId_ = std::nullopt;

  public:
    virtual bool isEmpty() const;

    virtual unsigned getColorId() const;

    virtual void setColorId(unsigned colorId);

    virtual void setEmpty();
};

#endif
