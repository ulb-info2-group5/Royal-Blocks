#include "account_service.hpp"

#include <bcrypt.h>
#include <iostream>

// ======== class account service ======== 

// == private ==
bool AccountService::checkCredentials(bindings::Authentication authentication){

    if (!accountManager_->checkUsernameExists(authentication.nickname)) {
        std::cout << "Invalid username" << std::endl;
        return false;
    }
    std::string storedPasswordHash = accountManager_->getUserPasswordHash(authentication.nickname);
    if (!bcrypt::validatePassword(authentication.password, storedPasswordHash)) {
        std::cout << "Invalid password" << std::endl;
        return false;
    }

    return true;
}


// == public ==
AccountService::AccountService(std::shared_ptr<AccountManager> & accountManager) : 
    accountManager_(accountManager) {

}

bindings::RegistrationResponse AccountService::attemptCreateAccount(bindings::Registration registration){
    std::string hash = bcrypt::generateHash(registration.password);
    CreateAccountStatus status = accountManager_->createAccount(registration.nickname, hash);
    return (status == CreateAccountStatus::SUCCESS ) ? bindings::RegistrationResponse{true} : bindings::RegistrationResponse{false};
}

bindings::AuthenticationResponse AccountService::authenticationAttempt(bindings::Authentication authentication, IsThisUserAlready isThisUserAlready ){

    return (checkCredentials(authentication) && 
    !(isThisUserAlready(accountManager_->getUserId(authentication.nickname))))
                       ? bindings::AuthenticationResponse{true}
                       : bindings::AuthenticationResponse{false};

}

void AccountService::changePassword(UserID userID , bindings::ChangePassword changePassword){
    std::string hash = bcrypt::generateHash(changePassword.password);
    accountManager_->updatePassword(userID, hash);
}

bindings::ChangeUsernameResponse AccountService::attemptChangeUsername(UserID userID, bindings::ChangeUsername changeUsername, UpdateUsers updateUsers){
    if ( accountManager_->updateUsername(userID, changeUsername.username)){
        updateUsers(userID);
        return bindings::ChangeUsernameResponse{true};
    }else {
        return bindings::ChangeUsernameResponse{false};
    }
}