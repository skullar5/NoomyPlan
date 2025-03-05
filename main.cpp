#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include "loginpage.h"
#include "authenticatesystem.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Business Management System");
        resize(800, 600);

        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QTabWidget *tabWidget = new QTabWidget(centralWidget);

        QWidget *dashboardPage = new QWidget();
        QWidget *financialsPage = new QWidget();
        QWidget *inventoryPage = new QWidget();
        QWidget *budgetPage = new QWidget();

        tabWidget->addTab(dashboardPage, "Dashboard");
        tabWidget->addTab(financialsPage, "Financials");
        tabWidget->addTab(inventoryPage, "Inventory");
        tabWidget->addTab(budgetPage, "Budget Page");

        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        layout->addWidget(tabWidget);
        centralWidget->setLayout(layout);

        QLabel *dashboardLabel = new QLabel("", dashboardPage);
        QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardPage);
        dashboardLayout->addWidget(dashboardLabel);
        dashboardPage->setLayout(dashboardLayout);

        QLabel *financialsLabel = new QLabel("", financialsPage);
        QVBoxLayout *financialsLayout = new QVBoxLayout(financialsPage);
        financialsLayout->addWidget(financialsLabel);
        financialsPage->setLayout(financialsLayout);

        QLabel *inventoryLabel = new QLabel("", inventoryPage);
        QVBoxLayout *inventoryLayout = new QVBoxLayout(inventoryPage);
        inventoryLayout->addWidget(inventoryLabel);
        inventoryPage->setLayout(inventoryLayout);

        QLabel *budgetLabel = new QLabel("", budgetPage);
        QVBoxLayout *budgetLayout = new QVBoxLayout(budgetPage);
        budgetLayout->addWidget(budgetLabel);
        budgetPage->setLayout(budgetLayout);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AuthenticateSystem authSystem;
    MainWindow mainWindow;  

    LoginPage loginPage(&authSystem, &mainWindow);
    loginPage.show();  

    return app.exec();
}
