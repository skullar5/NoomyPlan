#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "authenticatesystem.h"

class LoginPage : public QMainWindow {
private:
    QLineEdit *idInput;
    QPushButton *loginButton;
    QPushButton *signupButton;
    QLabel *statusLabel;
    AuthenticateSystem *authSystem;
    QMainWindow *mainWindow;

public:
    explicit LoginPage(AuthenticateSystem *auth, QMainWindow *mainWin, QWidget *parent = nullptr);

private:
    void handleLogin();
    void handleSignup();
};

#endif 
