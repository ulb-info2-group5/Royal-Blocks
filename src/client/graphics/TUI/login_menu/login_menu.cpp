#include "login_menu.hpp"

#include <string>

#include "../../../core/controller/controller.hpp"
#include "../main_tui.hpp"

#include "../ftxui_config/ftxui_config.hpp"
#include "../login_input/login_input.hpp"

namespace TUI {

    // ### constructor ###
    LoginMenu::LoginMenu(MainTui &mainTui, Controller &controller)
        : mainTui_(mainTui), controller_(controller),
          loginInput_{mainTui_, controller_, std::string(LOGIN_INPUT_TITLE),
                      LoginType::LOGIN},
          registerInput_{mainTui_, controller_,
                         std::string(REGISTER_INPUT_TITLE),
                         LoginType::REGISTER},
          showIpPortMenu_(false) {
        loginInput_.addInstruction(LOGIN_INSTRUCTIONS);
        registerInput_.addInstruction(REGISTER_INSTRUCTIONS);

        loginState_ = Login::NONE;

        if (controller_.isConnected()) {
            connectionMessage_ = STR_CONNECTION_SUCCESS;
        } else {
            connectionMessage_ = STR_NO_CONNECTED;
        }

        createButtonsInputs();
    }

    // ### protected methods ###

    void LoginMenu::createButtonsInputs() {
        buttonRegister_ = ftxui::Button(
            std::string(STR_REGISTER),
            [&] {
                if (registerInput_.render() == LoginState::SUBMIT) {
                    loginInput_.addMessage(LOGIN_MESSAGE);
                    if (loginInput_.render() == LoginState::SUBMIT) {
                        loginState_ = Login::LOGGED;
                    }
                }
                mainTui_.stopRender();
            }, GlobalButtonStyle());

        buttonLogin_ = ftxui::Button(
            std::string(STR_LOGIN),
            [&] {
                if (loginInput_.render() == LoginState::SUBMIT) {
                    loginState_ = Login::LOGGED;
                }
                mainTui_.stopRender();
            }, GlobalButtonStyle());

        buttonExit_ = ftxui::Button(
            std::string(STR_EXIT),
            [&] {
                loginState_ = Login::EXIT;
                mainTui_.stopRender();
            }, GlobalButtonStyle());

        buttonChooseIpPort_ = ftxui::Button(
            std::string(STR_CHOOSE_IP_PORT),
            [&] {
                selectedMenuIndex_ = 1;
            },GlobalButtonStyle());

        buttonBack_ = ftxui::Button(
            std::string(STR_BACK),
            [&] {
                selectedMenuIndex_ = 0;
            }, GlobalButtonStyle());

        buttonConnect_ = ftxui::Button(
            std::string(STR_CONNECT_TO_SERVER),
            [&] {
                checkConnection();
            }, GlobalButtonStyle());

        ipInput_ = ftxui::Input(&ip_, std::string(STR_IP));
        ipInput_ = ftxui::CatchEvent(ipInput_, [&](const ftxui::Event& event) {
            if (event == ftxui::Event::Return) {
                if (!ip_.empty() && !port_.empty()) {
                    checkConnection();
                }
                return true;
            }
            return false;
        });
        
        portInput_ = ftxui::Input(&port_, std::string(STR_PORT));
        portInput_ = ftxui::CatchEvent(portInput_, [&](const ftxui::Event& event) {
            if (event == ftxui::Event::Return) {
                if (!ip_.empty() && !port_.empty()) {
                    checkConnection();
                }
                return true;
            }
            return false;
        });
    }

    void LoginMenu::displayWindow() {
        mainMenu_ = ftxui::Container::Vertical({
            buttonRegister_,
            buttonLogin_,
            buttonChooseIpPort_,
            buttonExit_,
        });
        
        ipPortMenu_ = ftxui::Container::Vertical({
            ipInput_,
            portInput_,
            buttonConnect_,
            buttonBack_,
        });
        
        tabContainer_ = ftxui::Container::Tab(
            {mainMenu_, ipPortMenu_},
            &selectedMenuIndex_
        );
        

        displayWindow_ = ftxui::Renderer(tabContainer_,
            [&] {
                if (selectedMenuIndex_ == 0) {
                    return ftxui::vbox({
                                ftxui::text(std::string(STR_LOGIN_MENU))
                                   | ftxui::bold | ftxui::center
                                   | ftxui::bgcolor(ftxui::Color::Black),
                                ftxui::separator(),
                                ftxui::text(std::string(STR_INSTRUCTION_LOGIN))
                                   | ftxui::center
                                   | ftxui::bgcolor(ftxui::Color::Black),
                                ftxui::separator(),
                                coloredConnectionMessage()
                                      | ftxui::center
                                      | ftxui::bgcolor(ftxui::Color::Black),
                                ftxui::separator(),
                                buttonRegister_->Render()
                                   | ftxui::bgcolor(ftxui::Color::Black),
                                buttonLogin_->Render()
                                   | ftxui::bgcolor(ftxui::Color::Black),
                                buttonChooseIpPort_->Render()
                                   | ftxui::bgcolor(ftxui::Color::Black),
                                ftxui::separator(),
                                buttonExit_->Render()
                                   | ftxui::bgcolor(ftxui::Color::Black),
                           })
                           | ftxui::borderHeavy | ftxui::center
                           | ftxui::bgcolor(ftxui::Color::Black);
                }
    
                // IP/Port menu
                std::vector<ftxui::Element> elements = {
                    ftxui::text(std::string(STR_CHOOSE_IP_PORT))
                        | ftxui::bold | ftxui::center
                        | ftxui::bgcolor(ftxui::Color::Black),
                    ftxui::separator(),
                    ipInput_->Render() | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
                    portInput_->Render() | ftxui::center | ftxui::bgcolor(ftxui::Color::Black),
                };
                
                if (!errorConnectionMessage_.empty()) {
                    elements.push_back(ftxui::separator());
                    elements.push_back(
                        ftxui::paragraph(errorConnectionMessage_) 
                        | ftxui::color(ftxui::Color::Red)
                    );
                }

                if (!errorPortMessage_.empty()) {
                    elements.push_back(ftxui::separator());
                    elements.push_back(
                        ftxui::paragraph(errorPortMessage_) 
                        | ftxui::color(ftxui::Color::Red)
                    );
                }
                
                elements.push_back(ftxui::separator());
                elements.push_back(buttonConnect_->Render() | ftxui::bgcolor(ftxui::Color::Black));
                elements.push_back(buttonBack_->Render() | ftxui::bgcolor(ftxui::Color::Black));
                
                return ftxui::vbox(std::move(elements))
                    | ftxui::borderHeavy | ftxui::center | ftxui::bgcolor(ftxui::Color::Black);
            });
    }

    ftxui::Element LoginMenu::coloredConnectionMessage() const {
        if (connectionMessage_ == STR_CONNECTION_SUCCESS) {
            return ftxui::text(connectionMessage_ + " with IP address : " +
                   std::string(controller_.getServerIp()) + " and Port : " +
                   std::to_string(controller_.getServerPort()))
                   | ftxui::center
                   | ftxui::color(ftxui::Color::Green)
                   | ftxui::bold;
        }
    
        
        return ftxui::paragraph(connectionMessage_ + "\nCurrent IP address : " +
                   std::string(controller_.getServerIp()) + " and Port : " +
                   std::to_string(controller_.getServerPort()) + " are being used.")
                | ftxui::color(ftxui::Color::Red)
                | ftxui::bold;
    }
    

    void LoginMenu::checkConnection() {
        if (ip_.empty() || port_.empty()) {
            errorConnectionMessage_ = STR_CONNECTION_FAILED;
            connectionMessage_ = STR_NO_CONNECTED;
            errorPortMessage_ = std::string(STR_PORT_INVALID) + "\nCurrent IP address : " +
                   std::string(controller_.getServerIp()) + " and Port : " +
                   std::to_string(controller_.getServerPort()) + " are being used.";
            return;
        }

        int portInt = 0;
        try {
            portInt = std::stoi(port_);
        } catch (...) {
            errorConnectionMessage_ = STR_CONNECTION_FAILED;
            connectionMessage_ = STR_NO_CONNECTED;
            errorPortMessage_ = std::string(STR_PORT_INVALID) + "\nCurrent IP address : " +
                   std::string(controller_.getServerIp()) + " and Port : " +
                   std::to_string(controller_.getServerPort()) + " are being used.";
            return;
        }
        if (portInt < 1 || portInt > std::numeric_limits<uint16_t>::max()) {
            errorConnectionMessage_ = STR_CONNECTION_FAILED;
            connectionMessage_ = STR_NO_CONNECTED;
            errorPortMessage_ = std::string(STR_PORT_INVALID) + "\nCurrent IP address : " +
                   std::string(controller_.getServerIp()) + " and Port : " +
                   std::to_string(controller_.getServerPort()) + " are being used.";
            return;
        }

        errorPortMessage_.clear();

        config::ServerInfo serverInfo;
        serverInfo.ip = ip_;
        serverInfo.port = static_cast<uint16_t>(portInt);
        controller_.setServerInfo(serverInfo);

        std::thread waitThread([&]() {
            const int maxWaitTimeMs = 2000;
            const int checkIntervalMs = 100;
            int waited = 0;
            while (!controller_.isConnected() && waited < maxWaitTimeMs) {
                std::this_thread::sleep_for(std::chrono::milliseconds(checkIntervalMs));
                waited += checkIntervalMs;
            }
        });
        waitThread.join();
        if (controller_.isConnected()) {
            connectionMessage_ = STR_CONNECTION_SUCCESS;
            errorConnectionMessage_.clear();
            selectedMenuIndex_ = 0; 
            return;
        }

        connectionMessage_ = STR_NO_CONNECTED;
        errorConnectionMessage_ = STR_CONNECTION_FAILED;
    }

    void LoginMenu::updateConnectedMessage() {
        if (controller_.isConnected()) {
            errorConnectionMessage_.clear();
            connectionMessage_ = STR_CONNECTION_SUCCESS;
        } else {
            connectionMessage_ = STR_NO_CONNECTED;
            errorConnectionMessage_ = STR_CONNECTION_FAILED;
        }
    }

    // ### public methods ###
    LoginResult LoginMenu::render() {
        ip_ = std::string(controller_.getServerIp());
        port_ = std::to_string(controller_.getServerPort());
        
        loginState_ = Login::NONE;

        std::thread checkConnectionThread([&]() {
            while (loginState_ == Login::NONE) {
                updateConnectedMessage();
                mainTui_.forceRefresh(UpdateType::OTHER);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });

        displayWindow();

        while (loginState_ == Login::NONE) {
            mainTui_.render(displayWindow_);
        }

        if (checkConnectionThread.joinable()) {
            checkConnectionThread.join();
        }

        if (loginState_ == Login::EXIT) {
            return LoginResult::EXIT;
        }

        return LoginResult::SUCCESS;
    }

} // namespace TUI
