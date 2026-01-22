#include "threewaydialog.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCoreApplication>

ThreeWayDialog::ThreeWayDialog(QWidget* parent) :
	QDialog(parent)
{
	setupUi();
	connectSignals();
}

ThreeWayDialog::Result ThreeWayDialog::getResult() const
{
	return result;
}

void ThreeWayDialog::setupUi()
{
    setWindowTitle(QCoreApplication::translate("ThreeWayDialog", "Warning"));

    auto* label = new QLabel(QCoreApplication::translate("ThreeWayDialog", "Actions"), this);
    auto* buttonA = new QPushButton(QCoreApplication::translate("ThreeWayDialog", "Save and quit"), this);
    auto* buttonB = new QPushButton(QCoreApplication::translate("ThreeWayDialog", "Quit without saving"), this);
    auto* buttonC = new QPushButton(QCoreApplication::translate("ThreeWayDialog", "Cancel"), this);
    buttonA->setStyleSheet("padding: 8px 8px;");
    buttonB->setStyleSheet("padding: 8px 8px;");
    buttonC->setStyleSheet("padding: 8px 8px;");

    auto* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonA);
    buttonLayout->addWidget(buttonB);
    buttonLayout->addWidget(buttonC);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addLayout(buttonLayout);

    // Store signals locally so they connect to this
    connect(buttonA, &QPushButton::clicked, this, [this]() {
        result = OptionA;
        accept();
        });
    connect(buttonB, &QPushButton::clicked, this, [this]() {
        result = OptionB;
        accept();
        });
    connect(buttonC, &QPushButton::clicked, this, [this]() {
        result = OptionC;
        accept();
        });
}

void ThreeWayDialog::connectSignals()
{
}
