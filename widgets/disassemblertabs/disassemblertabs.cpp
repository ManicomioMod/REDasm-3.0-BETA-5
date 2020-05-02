#include "disassemblertabs.h"
#include "disassemblertabbutton.h"
#include "../hooks/disassemblerhooks.h"
#include "../hooks/icommandtab.h"
#include "../redasmfonts.h"
#include <QTabBar>

DisassemblerTabs::DisassemblerTabs(QWidget *parent) : QTabWidget(parent)
{
    this->setTabBarAutoHide(true);
    this->setMovable(true);

    connect(this, &DisassemblerTabs::currentChanged, this, &DisassemblerTabs::onTabChanged);
}

int DisassemblerTabs::tabHeight() const { return 25; }

void DisassemblerTabs::tabInserted(int index)
{
    this->setTabText(index, QString());
    this->tabBar()->setTabButton(index, QTabBar::LeftSide, new DisassemblerTabButton(this->widget(index), this));

    QPushButton* btnclose = new QPushButton();
    btnclose->setFlat(true);
    btnclose->setIcon(FA_ICON(0xf00d));

    this->tabBar()->setTabButton(index, QTabBar::RightSide, btnclose);
    connect(btnclose, &QPushButton::clicked, this, &DisassemblerTabs::onCloseClicked);

    QTabWidget::tabInserted(index);
}

void DisassemblerTabs::onTabChanged(int index)
{
    QWidget* w = this->widget(index);
    DisassemblerHooks::instance()->enableCommands(w);
    DisassemblerHooks::instance()->updateCommandStates(w);
}

void DisassemblerTabs::onCloseClicked()
{
    auto* sender = static_cast<QPushButton*>(this->sender());

    for(int i = 0; i < this->tabBar()->count(); i++)
    {
        if(this->tabBar()->tabButton(i, QTabBar::RightSide) != sender) continue;

        this->removeTab(i);
        break;
    }
}