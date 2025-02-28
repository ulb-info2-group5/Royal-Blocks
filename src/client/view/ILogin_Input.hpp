#ifndef ILOGIN_INPUT_HPP
#define ILOGIN_INPUT_HPP

class ILogin_Input {
  protected:
    virtual void displayWindow() = 0;

  public:
    virtual ~ILogin_Input() = default;
};

#endif