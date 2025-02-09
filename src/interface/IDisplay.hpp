#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

#include "interfaceConfig.hpp"

class IDisplay {
   public:

   virtual ~IDisplay() = default;

   virtual void changeUserState() = 0;
   
   virtual UserState getUserState() = 0;

   virtual void drawWindow() = 0;

   virtual void drawButtons() = 0;

};


#endif