// Copyright (c) 2020 The PIVX Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CONCRETE_LEGACY_ZPOS_H
#define CONCRETE_LEGACY_ZPOS_H

#include "stakeinput.h"
#include "main.h"
#include "txdb.h"

class CLegacyZCctStake : public CStakeInput
{
private:
    uint32_t nChecksum;
    libzerocoin::CoinDenomination denom;
    uint256 hashSerial;

public:
    CLegacyZCctStake() {}

    explicit CLegacyZCctStake(const libzerocoin::CoinSpend& spend);
    bool InitFromTxIn(const CTxIn& txin) override;
    bool IsZCCT() const override { return true; }
    uint32_t GetChecksum() const { return nChecksum; }
    CBlockIndex* GetIndexFrom() override;
    CAmount GetValue() const override;
    CDataStream GetUniqueness() const override;
    bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = UINT256_ZERO) override { return false; /* creation disabled */}
    bool CreateTxOuts(CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) override { return false; /* creation disabled */}
    bool GetTxFrom(CTransaction& tx) const override { return false; /* not available */ }
    bool GetTxOutFrom(CTxOut& out) const override { return false; /* not available */ }
    virtual bool ContextCheck(int nHeight, uint32_t nTime) override;
};

#endif //CONCRETE_LEGACY_ZPOS_H
