#include "loginpage.h"

LoginPage::LoginPage(AuthenticateSystem *auth, QMainWindow *mainWin, QWidget *parent) 
    : QMainWindow(parent), authSystem(auth), mainWindow(mainWin) {
    setWindowTitle("Login - Business Management System");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *titleLabel = new QLabel("Business Management System - Login");
    idInput = new QLineEdit();
    idInput->setPlaceholderText("Enter your ID");
    loginButton = new QPushButton("Login");
    signupButton = new QPushButton("Sign Up");
    statusLabel = new QLabel("");

    layout->addWidget(titleLabel);
    layout->addWidget(idInput);
    layout->addWidget(loginButton);
    layout->addWidget(signupButton);
    layout->addWidget(statusLabel);

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::handleLogin);
    connect(signupButton, &QPushButton::clicked, this, &LoginPage::handleSignup);
}

void LoginPage::handleLogin() {
    QString id = idInput->text().trimmed();
    std::cout << "Attempting login for user: " << id.toStdString() << std::endl;

 
    if (authSystem->isAccountLocked(id)) {
        statusLabel->setText("Account is locked! Try again in 1 minute.");
        std::cout << "UI Message: Account " << id.toStdString() << " is locked! Attempts Blocked." << std::endl;
        return;
    }

    if (!authSystem->userExists(id)) {
        statusLabel->setText("Invalid ID!");
        return;
    }

    if (authSystem->authenticateUser(id)) {
        statusLabel->setText("Login successful!");
        mainWindow->show();
        this->close();
    } else {
        statusLabel->setText("Incorrect login. Try again.");
    }
}


void LoginPage::handleSignup() {
    QString id = idInput->text().trimmed();

    if (id.isEmpty()) {
        statusLabel->setText("ID cannot be empty.");
        return;
    }

    if (authSystem->isAccountLocked(id)) {  
        statusLabel->setText("Account is locked! You cannot create an account right now.");
        std::cout << "Cannot sign up - Account " << id.toStdString() << " is locked!" << std::endl;
        return;
    }

    if (authSystem->userExists(id)) {  
        statusLabel->setText("User already exists!");
        return;
    }

    authSystem->addUser(id, "User");
    statusLabel->setText("Account created successfully! Please log in.");
}

