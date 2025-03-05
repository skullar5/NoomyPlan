#include "authenticatesystem.h"
#include <iostream>  

AuthenticateSystem::AuthenticateSystem() {}
bool AuthenticateSystem::authenticateUser(const QString& userID) {
    std::cout << "🔍 Checking login for " << userID.toStdString() 
              << ". Failed attempts: " << failedAttempts[userID] << "/5" << std::endl;

    if (lockedAccounts[userID]) {
        std::cout << "🚫 Account " << userID.toStdString() << " is LOCKED! Cannot log in." << std::endl;
        return false;
    }

    if (!userExists(userID)) {
        std::cout << "❌ Invalid ID: No user found with ID " << userID.toStdString() << std::endl;
        
        failedAttempts[userID]++;
        std::cout << "⚠️ Failed attempt count: " << failedAttempts[userID] << "/5" << std::endl;

        if (failedAttempts[userID] >= 5) {
            lockAccount(userID);
        }
        return false;
    }

    if (users[userID]->login()) {
        std::cout << "Successful login for " << userID.toStdString() << std::endl;
        failedAttempts[userID] = 0;  // Reset failed attempts
        return true;
    }

    failedAttempts[userID]++;
    std::cout << "⚠️ Failed login attempt " << failedAttempts[userID] << "/5 for " 
              << userID.toStdString() << std::endl;

    if (failedAttempts[userID] >= 5) {
        lockAccount(userID);
    }

    return false;
}

void AuthenticateSystem::lockAccount(const QString& userID) {
    lockedAccounts[userID] = true;  
    failedAttempts[userID] = 5;      

    std::cout << "Account " << userID.toStdString() << " is now LOCKED for 1 minute! 🚨" << std::endl;

    QTimer::singleShot(60000, [this, userID]() {
        lockedAccounts[userID] = false;
        failedAttempts[userID] = 0; 
        std::cout << "Account " << userID.toStdString() << " is now UNLOCKED!" << std::endl;
    });
}


void AuthenticateSystem::logoutUser(const QString& userID) {
    if (users.find(userID) != users.end()) {
        users[userID]->logout();
    }
}

void AuthenticateSystem::addUser(const QString& userID, const QString& role) {
    users[userID] = new User(userID, role);
}

bool AuthenticateSystem::userExists(const QString& userID) {
    return users.find(userID) != users.end();
}

bool AuthenticateSystem::isAccountLocked(const QString& userID) {
    return lockedAccounts.find(userID) != lockedAccounts.end() && lockedAccounts[userID];
}
