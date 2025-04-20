#ifndef ACCOUNT_SERVICE_HPP
#define ACCOUNT_SERVICE_HPP


#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include "../database/account_manager/account_manager.hpp"

#include "../../common/types/types.hpp"
#include "../../common/bindings/authentication.hpp"
#include "../../common/bindings/authentication.hpp"
#include "../../common/bindings/authentication_response.hpp"
#include "../../common/bindings/registration.hpp"
#include "../../common/bindings/registration_response.hpp"
#include "../../common/bindings/user.hpp"
#include "../../common/bindings/change_password.hpp"
#include "../../common/bindings/change_username.hpp"
#include "../../common/bindings/change_username_response.hpp"

using IsThisUserAlready  = std::function<bool(UserID)>;
using UpdateUsers = std::function<void(UserID)>;


class AccountService {
    private :
        std::shared_ptr<AccountManager> accountManager_;
        bool checkCredentials(bindings::Authentication authentication);
    public : 
        AccountService(std::shared_ptr<AccountManager> & accountManager);
        ~AccountService() = default;
        bindings::RegistrationResponse attemptCreateAccount(bindings::Registration registration);
        bindings::AuthenticationResponse authenticationAttempt(bindings::Authentication authentication, IsThisUserAlready isThisUserAlready );
        bindings::ChangeUsernameResponse attemptChangeUsername(UserID userID, bindings::ChangeUsername changeUsername, UpdateUsers updateUsers ); 
        void changePassword(UserID userID , bindings::ChangePassword changePassword);

        void updateScore(UserID userID , int score );

        std::shared_ptr<AccountManager>& getAccountManager();
        std::string getUsername(UserID userID);
        UserID getUserID(std::string username);
        std::vector<std::pair<std::string, size_t>> getRanking() const;
        
        


};

#endif 