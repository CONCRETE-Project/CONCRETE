// Copyright (c) 2019 The PIVX Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COLDSTAKINGWIDGET_H
#define COLDSTAKINGWIDGET_H

#include "qt/concrete/pwidget.h"
#include "qt/concrete/furabstractlistitemdelegate.h"
#include "qt/concrete/txviewholder.h"
#include "qt/concrete/tooltipmenu.h"
#include "qt/concrete/sendmultirow.h"
#include "qt/concrete/coldstakingmodel.h"
#include "qt/concrete/contactsdropdown.h"
#include "qt/concrete/addressholder.h"
#include "transactiontablemodel.h"
#include "addresstablemodel.h"
#include "addressfilterproxymodel.h"
#include "coincontroldialog.h"

#include <QAction>
#include <QLabel>
#include <QWidget>
#include <QSpacerItem>
#include <atomic>

class CONCRETEGUI;
class WalletModel;
class CSDelegationHolder;

namespace Ui {
class ColdStakingWidget;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class ColdStakingWidget : public PWidget
{
    Q_OBJECT

public:
    explicit ColdStakingWidget(CONCRETEGUI* parent);
    ~ColdStakingWidget();

    void loadWalletModel() override;
    void run(int type) override;
    void onError(QString error, int type) override;

public Q_SLOTS:
    void walletSynced(bool sync);

private Q_SLOTS:
    void changeTheme(bool isLightTheme, QString &theme) override;
    void handleAddressClicked(const QModelIndex &index);
    void handleMyColdAddressClicked(const QModelIndex &rIndex);
    void onCoinControlClicked();
    void onColdStakeClicked();
    void updateDisplayUnit();
    void showList(bool show);
    void onSendClicked();
    void onDelegateSelected(bool delegate);
    void onEditClicked();
    void onDeleteClicked();
    void onCopyClicked();
    void onCopyOwnerClicked();
    void onAddressCopyClicked();
    void onAddressEditClicked();
    void onTxArrived(const QString& hash, const bool& isCoinStake, const bool& isCSAnyType);
    void onContactsClicked(bool ownerAdd);
    void clearAll();
    void onLabelClicked();
    void onMyStakingAddressesClicked();
    void onDelegationsRefreshed();
    void onSortChanged(int idx);
    void onSortOrderChanged(int idx);

private:
    Ui::ColdStakingWidget *ui = nullptr;
    FurAbstractListItemDelegate *delegate = nullptr;
    FurAbstractListItemDelegate *addressDelegate = nullptr;
    TransactionTableModel* txModel = nullptr;
    AddressHolder* addressHolder = nullptr;
    AddressTableModel* addressTableModel = nullptr;
    AddressFilterProxyModel *addressesFilter = nullptr;
    ColdStakingModel* csModel = nullptr;
    CSDelegationHolder *txHolder = nullptr;
    CoinControlDialog *coinControlDialog = nullptr;
    QAction *btnOwnerContact = nullptr;
    QSpacerItem *spacerDiv = nullptr;

    bool isInDelegation = true;
    bool isStakingAddressListVisible = false;

    ContactsDropdown *menuContacts = nullptr;
    TooltipMenu* menu = nullptr;
    TooltipMenu* menuAddresses = nullptr;
    SendMultiRow *sendMultiRow = nullptr;
    bool isShowingDialog = false;
    bool isChainSync = false;

    bool isContactOwnerSelected;
    int64_t lastRefreshTime = 0;
    std::atomic<bool> isLoading;

    // Cached index
    QModelIndex index;
    QModelIndex addressIndex;

    // Cached sort type and order
    AddressTableModel::ColumnIndex sortType = AddressTableModel::Label;
    Qt::SortOrder sortOrder = Qt::AscendingOrder;

    int nDisplayUnit;

    void showAddressGenerationDialog(bool isPaymentRequest);
    void onContactsClicked();
    void tryRefreshDelegations();
    bool refreshDelegations();
    void onLabelClicked(QString dialogTitle, const QModelIndex &index, const bool& isMyColdStakingAddresses);
    void updateStakingTotalLabel();
    void sortAddresses();
};

#endif // COLDSTAKINGWIDGET_H
