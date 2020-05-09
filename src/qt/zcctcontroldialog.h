// Copyright (c) 2017-2020 The PIVX Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZCCTCONTROLDIALOG_H
#define ZCCTCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zcct/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZCctControlDialog;
}

class CZCctControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZCctControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZCctControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZCctControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZCctControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZCctControlDialog(QWidget *parent);
    ~ZCctControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZCctControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZCctControlWidgetItem;

private Q_SLOTS:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZCCTCONTROLDIALOG_H
