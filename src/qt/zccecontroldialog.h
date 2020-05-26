// Copyright (c) 2017-2020 The PIVX Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZCCECONTROLDIALOG_H
#define ZCCECONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zcce/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZCceControlDialog;
}

class CZCceControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZCceControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZCceControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZCceControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZCceControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZCceControlDialog(QWidget *parent);
    ~ZCceControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZCceControlDialog *ui;
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
    friend class CZCceControlWidgetItem;

private Q_SLOTS:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZCCECONTROLDIALOG_H
