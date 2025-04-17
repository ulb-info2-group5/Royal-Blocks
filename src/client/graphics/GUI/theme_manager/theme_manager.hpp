#ifndef THEME_MANAGER_HPP
#define THEME_MANAGER_HPP

#include <QWidget>


namespace GUI {

    class ThemeManager : public QWidget {
      Q_OBJECT
      
      private:
        /*
         * @brief Setup the Theme Manager Gui
         */
        void setup();       

      public:
        ThemeManager(QWidget *parent = nullptr);

        ~ThemeManager() = default;

      signals:
        /*
         * @brief Signal emitted when the user click on the back button
         */
        void backToMainMenu();

        /*
         * @brief Signal emitted when the user click on the dark theme button
         */
        void applyDarkTheme();

        /*
         * @brief Signal emitted when the user click on the light theme button
         */
        void applyLightTheme();
    };
}

#endif // THEME_MANAGER_HPP