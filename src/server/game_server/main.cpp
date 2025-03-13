#include "game_mode/game_mode.hpp"
#include "game_server.hpp"
#include "tetromino/tetromino.hpp"

#include <iostream>
#include <fstream>


#include "../../common/bindings/authentication.hpp"
#include "../../common/bindings/authentication_response.hpp"
#include "../../common/bindings/message.hpp"
#include "../../common/bindings/registration.hpp"
#include "../../common/bindings/registration_response.hpp"
#include "../../common/bindings/binding_type.hpp"


#include "../../common/bindings/create_game.hpp"
#include "../../common/bindings/join_game.hpp"
#include "../../common/bindings/in_game/big_drop.hpp"
#include "../../common/bindings/in_game/buy_bonus.hpp"
#include "../../common/bindings/in_game/big_drop.hpp"
#include "../../common/bindings/in_game/big_drop.hpp"
#include "../../common/bindings/in_game/big_drop.hpp"
#include "../../common/bindings/in_game/move_active.hpp"


int main() {
    // GameServer gameServer{GameMode::Dual, {0, 1}};

    // for (int i = 0; i < 200; i++) {
    //     gameServer.enqueueBinding(0, bindings::BigDrop{}.to_json().dump());
    // }

    // -----------------------------
    // gameServer.enqueueBinding(1, bindings::BigDrop{}.to_json().dump());
    //
    // gameServer.enqueueBinding(1,
    // bindings::SelectTarget{2}.to_json().dump());
    //
    // gameServer.enqueueBinding(
    //     1, bindings::MoveActive{TetrominoMove::Right}.to_json().dump());
    // -----------------------------

    // gameServer.run();
    bindings::Authentication authenticationLeo{"leo", "leo"};
    bindings::Authentication authenticationQuentin{"quentin", "1234"};
    bindings::CreateGame createGame{GameMode::Dual, 2};
    bindings::JoinGame joinGame{GameMode::Dual};


    //in game 
    bindings::BigDrop bigdrop;
    bindings::BuyBonus buibonus;
    bindings::MoveActive moveactive;

    std::ofstream myfile;
    myfile.open("example.txt");
    std::cout << myfile.is_open() << std::endl;
    myfile << authenticationLeo.to_json().dump() + "\n";
    myfile << authenticationQuentin.to_json().dump() + "\n";
    myfile << createGame.to_json().dump() + "\n"; 
    myfile << joinGame.to_json().dump() + "\n";
    myfile << bigdrop.to_json().dump() + "\n";
    myfile << moveactive.to_json().dump() + "\n";
    myfile << buibonus.to_json().dump() + "\n";

    myfile.close();

    


}
