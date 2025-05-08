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

/**
 * @class AccountService
 *
 * @brief Instance to manipulate all the operations on the database concerning the creation, the changement
 * on a user's account and its associated ranking score.
 */
class AccountService {
    private :
        std::shared_ptr<AccountManager> accountManager_;
        bool checkCredentials(bindings::Authentication authentication);
    public : 
        AccountService(std::shared_ptr<AccountManager> & accountManager);
        ~AccountService() = default;

        /**
        * @brief Receives a binding to create an account on the database
        * and returns the response of the operation on the database
        *
        * @param registration the binding
        *
        * @return a binding with the success or not to create the new account
        */
        bindings::RegistrationResponse attemptCreateAccount(bindings::Registration registration);

        /**
        * @brief Receives a binding to authenticate to an account on the database
        * and returns the response of the operation on the database
        *
        * @param  authentication the binding with the account's information
        * @param  isThisUserAlreadyIn function to check if the account is not already connected
        *
        * @return a binding with the success or not to connect to the account wished
        */
        bindings::AuthenticationResponse authenticationAttempt(bindings::Authentication authentication, IsThisUserAlready isThisUserAlready );

        /**
        * @brief Retruns the success or not of the operation to change the username
        * of a specific account
        * 
        * @param userID userID of the concerning account for the changement
        * @param changeUsername binding with the changement's information
        * @param UpdateUsers function to do this operation on the database manager
        *
        * @return a binding with the success of not to change the username of the account
        */
        bindings::ChangeUsernameResponse attemptChangeUsername(UserID userID, bindings::ChangeUsername changeUsername, UpdateUsers updateUsers ); 


        /**
        * @brief change password of an account on the database
        *
        * @param userID userID of the concerning account
        * @param changePassword binding with the changement's information
        *
        */
        void changePassword(UserID userID , bindings::ChangePassword changePassword);

        /**
        * @brief change the score associated to an account on the database
        *
        * @param userID userID of the concerning account
        * @param score value of the new score
        *
        */
        void updateScore(UserID userID , int score );


        /**
        * @brief returns a shared pointer to the database manager
        */
        std::shared_ptr<AccountManager>& getAccountManager();

        /**
        * @brief returns the username of a given userID 
        */ 
        std::string getUsername(UserID userID);

        /**
        * @brief returns the userID of a given username
        */ 
        UserID getUserID(std::string username);

        /**
        * @brief returns a vector representing the global ranking on the database
        */ 
        std::vector<std::pair<std::string, size_t>> getRanking() const;
        
        


};

#endif 