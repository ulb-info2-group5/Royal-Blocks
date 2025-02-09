#include <ftxui/component/component.hpp> // Pour FTXUI
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>
#include <iostream>

using namespace ftxui;

class ScreenManager {
public:
    ScreenManager() : screen(ScreenInteractive::TerminalOutput()) {}
    void SetComponent(Component component) {
        main_component = component;
    }
    void Run() {
        screen.Loop(main_component);
    }
    void Exit() {
        screen.Exit();
    }

private:
    ScreenInteractive screen;
    Component main_component;
};

class ButtonUi {
public:
    ButtonUi(const std::string& label, std::function<void()> on_click) {
        button = Button(label, on_click);
    }
    Component GetComponent() { return button; }
private:
    Component button;
};

class TextUi {
public:
    TextUi(const std::string& texts) {
        text_content = texts;
        text_component = Renderer([this] { return text(text_content) | center; });
    }
    Component GetComponent() { return text_component; }
private:
    std::string text_content;
    Component text_component;
};

class InputUi {
public:
    InputUi(std::string& content, const std::string& placeholder) {
        input = Input(&content, placeholder);
    }
    Component GetComponent() { return input; }
private:
    Component input;
};

class MenuUi {
public:
    MenuUi(const std::vector<std::string>& entries, int& selected) {
        menu = Menu(&entries, &selected);
    }
    Component GetComponent() { return menu; }
private:
    Component menu;
};

class LayoutManager {
public:
    LayoutManager(std::vector<Component> components) {
        layout = Container::Vertical(components);
    }
    Component GetComponent() { return layout; }
private:
    Component layout;
};

int main() {
    ScreenManager screenManager;
    std::string input_content;
    int selected = 0;

    ButtonUi button("Click Me", [] { std::cout << "Bouton pressé !\n"; });
    TextUi text("Bienvenue dans FTXUI");
    InputUi input(input_content, "Entrez du texte...");
    MenuUi menu({"Option 1", "Option 2", "Option 3", "Option 4"}, selected);
    
    ButtonUi exit_button("Quitter", [&] { screenManager.Exit(); });
    TextUi instructions("Utilisez les flèches pour naviguer et appuyez sur Entrée pour valider.");
    
    LayoutManager layout({instructions.GetComponent(), text.GetComponent(), input.GetComponent(), menu.GetComponent(), button.GetComponent(), exit_button.GetComponent()});
    
    screenManager.SetComponent(layout.GetComponent());
    screenManager.Run();
    
    return 0;
}