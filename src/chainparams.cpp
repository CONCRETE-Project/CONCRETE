// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "consensus/merkle.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <limits>

#include "chainparamsseeds.h"

std::string CDNSSeedData::getHost(uint64_t requiredServiceBits) const {
    //use default host for non-filter-capable seeds or if we use the default service bits (NODE_NETWORK)
    if (!supportsServiceBitsFiltering || requiredServiceBits == NODE_NETWORK)
        return host;

    return strprintf("x%x.%s", requiredServiceBits, host);
}

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 *  ---------------
 *  algorithm: quark
 *  pzTimestamp: 2020/04/30 CONCRETE by ZioFabry
 *  pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
 *  block version: 1
 *  bits: 504365040
 *  time: 1588281431
 *  merkle root hash: 038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a
 *  Searching for genesis hash...
 *  nonce: 327577
 *  genesis hash: 00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde
 **/
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "2020/04/30 CONCRETE by ZioFabry";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (      0, uint256S("00000f31de924cf332441aa9b2955c1131ff7bbe81295e17fc32d5db6f7ea5e7"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1587254218, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"))
    ;
    
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1587254218,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1587254218,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        /**
         *  ---------------
         *  algorithm: quark
         *  pzTimestamp: 2020/04/30 CONCRETE by ZioFabry
         *  pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
         *  block version: 1
         *  bits: 504365040
         *  time: 1588281431
         *  merkle root hash: 038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a
         *  Searching for genesis hash...
         *  nonce: 327577
         *  genesis hash: 00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde
         */
        genesis = CreateGenesisBlock(1588281431, 327577, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde"));
        assert(genesis.hashMerkleRoot     == uint256S("0x038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a"));

        consensus.fPowAllowMinDifficultyBlocks           = false;
        consensus.powLimit                               = ~UINT256_ZERO >> 20;    // CONCRETE starting difficulty is 1 / 2^12
        consensus.posLimitV1                             = ~UINT256_ZERO >> 24;
        consensus.posLimitV2                             = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks                     = 43200;                  // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations                = 6;                      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity                      = 100;
        consensus.nFutureTimeDriftPoW                    = 7200;
        consensus.nFutureTimeDriftPoS                    = 180;
        consensus.nMasternodeCountDrift                  = 20;                     // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut                           = 50000000 * COIN;
        consensus.nPoolMaxTransactions                   = 3;
        consensus.nProposalEstablishmentTime             = 60 * 60 * 24;           // must be at least a day old to make it into a budget
        consensus.nStakeMinAge                           = 60 * 60;
        consensus.nStakeMinDepth                         = 600;
        consensus.nTargetTimespan                        = 40 * 60;
        consensus.nTargetTimespanV2                      = 30 * 60;
        consensus.nTargetSpacing                         = 1 * 60;
        consensus.nTimeSlotLength                        = 15;

        consensus.nHalvingInterval                       = 525600;
        consensus.nInflationPerc                         = 0.14;
        consensus.nInflationPercAnnualDecrease           = 0.10;

        // spork keys
        consensus.strSporkPubKey                         = "04c6e933bb414a6a50e8302f3f599dd43acdd877eedc27ade9e0ea258fbc392aec4b56e3b8801b498c3259d1153032a900fe8c94d7be16572dc3146d776fbf01b5";
        consensus.strSporkPubKeyOld                      = "";
        consensus.nTime_EnforceNewSporkKey               = 0;
        consensus.nTime_RejectOldSporkKey                = 0;

        // height-based activations
        consensus.height_last_PoW                        = 1000;
        consensus.height_last_ZC_AccumCheckpoint         = 0;
        consensus.height_last_ZC_WrappedSerials          = 0;
        consensus.height_start_BIP65                     = 0;                      // Block v5
        consensus.height_start_InvalidUTXOsCheck         = 999999999;
        consensus.height_start_MessSignaturesV2          = 0;                      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1050;
        consensus.height_start_StakeModifierV2           = 1100;                   // Block v6
        consensus.height_start_TimeProtoV2               = 1200;                   // Block v7
        consensus.height_start_ZC                        = 1050;                   // Block v4
        consensus.height_start_ZC_InvalidSerials         = 999999999;
        consensus.height_start_ZC_PublicSpends           = 1300;
        consensus.height_start_ZC_SerialRangeCheck       = 999999999;
        consensus.height_start_ZC_SerialsV2              = 1400;
        consensus.height_ZC_RecalcAccumulators           = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus                             = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                                                           "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                                                           "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                                                           "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                                                           "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                                                           "31438167899885040445364023527381951378636564391212010397122822120720357";

        consensus.ZC_MaxPublicSpendsPerTx                = 637;             // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx                      = 7;               // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations                = 20;
        consensus.ZC_MinMintFee                          = 1 * CENT;
        consensus.ZC_MinStakeDepth                       = 200;
        consensus.ZC_TimeStart                           = 1587256775;      // 2020/04/19 @ 12:39am (UTC)
        consensus.ZC_WrappedSerialsSupply                = 0 * COIN;        // zerocoin supply at height_last_ZC_WrappedSerials

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0]                               = 0x8f;
        pchMessageStart[1]                               = 0xc5;
        pchMessageStart[2]                               = 0xfc;
        pchMessageStart[3]                               = 0xf0;
        nDefaultPort                                     = 32812;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("ziofabry.twt.it", "mainnet.concrete.seed.ziofabry.twt.it", true));     // Primary DNS Seeder from ZioFabry

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 28);        // Start with 'C' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 15);        // Start with '7' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);        // Start with 'S' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 45);        // Start with 'K' from https://en.bitcoin.it/wiki/List_of_address_prefixes

        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x04)(0x2E)(0x26)(0x35).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x04)(0x1E)(0x34)(0x2D).convert_to_container<std::vector<unsigned char> >();

        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x03)(0x5f).convert_to_container<std::vector<unsigned char> >();   // 0x8000035f

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        /**
         *  ---------------
         *  algorithm: quark
         *  pzTimestamp: 2020/04/30 CONCRETE by ZioFabry
         *  pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
         *  block version: 1
         *  bits: 504365040
         *  time: 1588281431
         *  merkle root hash: 038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a
         *  Searching for genesis hash...
         *  nonce: 327577
         *  genesis hash: 00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde
         */
        genesis = CreateGenesisBlock(1588281431, 327577, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde"));
        assert(genesis.hashMerkleRoot     == uint256S("0x038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a"));

        consensus.fPowAllowMinDifficultyBlocks           = true;
        consensus.powLimit                               = ~UINT256_ZERO >> 20;        // CONCRETE starting difficulty is 1 / 2^12
        consensus.posLimitV1                             = ~UINT256_ZERO >> 24;
        consensus.posLimitV2                             = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks                     = 144;                        // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations                = 3;                          // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity                      = 15;
        consensus.nFutureTimeDriftPoW                    = 7200;
        consensus.nFutureTimeDriftPoS                    = 180;
        consensus.nMasternodeCountDrift                  = 4;                          // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut                           = 43199500 * COIN;
        consensus.nPoolMaxTransactions                   = 2;
        consensus.nProposalEstablishmentTime             = 60 * 5;                     // at least 5 min old to make it into a budget
        consensus.nStakeMinAge                           = 60 * 60;
        consensus.nStakeMinDepth                         = 100;
        consensus.nTargetTimespan                        = 40 * 60;
        consensus.nTargetTimespanV2                      = 30 * 60;
        consensus.nTargetSpacing                         = 1 * 60;
        consensus.nTimeSlotLength                        = 15;

        consensus.nHalvingInterval                       = 525600;
        consensus.nInflationPerc                         = 0.14;
        consensus.nInflationPercAnnualDecrease           = 0.10;

        // spork keys
        consensus.strSporkPubKey                         = "04a81db419077aa2e5e2e00ec51e02749b5cbe2bb61a18959b2229485d4c8af0a9964bc6c7aa069e2391736c405cb40bb3c8fc7985a48204a8408e8c2db3b18da0";
        consensus.strSporkPubKeyOld                      = "";
        consensus.nTime_EnforceNewSporkKey               = 0;
        consensus.nTime_RejectOldSporkKey                = 0;

        // height based activations
        consensus.height_last_PoW                        = 1000;
        consensus.height_last_ZC_AccumCheckpoint         = 0;
        consensus.height_last_ZC_WrappedSerials          = 0;
        consensus.height_start_BIP65                     = 0;                      // Block v5
        consensus.height_start_InvalidUTXOsCheck         = 999999999;
        consensus.height_start_MessSignaturesV2          = 0;                      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1050;
        consensus.height_start_StakeModifierV2           = 1100;                   // Block v6
        consensus.height_start_TimeProtoV2               = 1200;                   // Block v7
        consensus.height_start_ZC                        = 1050;                   // Block v4
        consensus.height_start_ZC_InvalidSerials         = 999999999;
        consensus.height_start_ZC_PublicSpends           = 1300;
        consensus.height_start_ZC_SerialRangeCheck       = 999999999;
        consensus.height_start_ZC_SerialsV2              = 1400;
        consensus.height_ZC_RecalcAccumulators           = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus                             = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                                                           "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                                                           "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                                                           "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                                                           "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                                                           "31438167899885040445364023527381951378636564391212010397122822120720357";

        consensus.ZC_MaxPublicSpendsPerTx                = 637;             // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx                      = 7;               // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations                = 20;
        consensus.ZC_MinMintFee                          = 1 * CENT;
        consensus.ZC_MinStakeDepth                       = 200;
        consensus.ZC_TimeStart                           = 1587256775;      // 2020/04/19 @ 12:39am (UTC)
        consensus.ZC_WrappedSerialsSupply                = 0;               // WrappedSerials only on main net

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x44;
        pchMessageStart[1] = 0x77;
        pchMessageStart[2] = 0x64;
        pchMessageStart[3] = 0xbb;
        nDefaultPort = 32814;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("ziofabry.twt.it", "testnet.concrete.seed.ziofabry.twt.it", true));     // Primary DNS Seeder from ZioFabry

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 88);        // Start with 'c' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 18);        // Start with '8' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 125);       // Start with 's' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 108);       // Start with 'k' from https://en.bitcoin.it/wiki/List_of_address_prefixes

        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x2f)(0x2E)(0x26)(0x35).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x2f)(0x1E)(0x34)(0x2D).convert_to_container<std::vector<unsigned char> >();

        // Testnet concrete BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        /**
         *  ---------------
         *  algorithm: quark
         *  pzTimestamp: 2020/04/30 CONCRETE by ZioFabry
         *  pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
         *  block version: 1
         *  bits: 504365040
         *  time: 1588281431
         *  merkle root hash: 038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a
         *  Searching for genesis hash...
         *  nonce: 327577
         *  genesis hash: 00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde
         */
        genesis = CreateGenesisBlock(1588281431, 327577, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000f1ce413fdebc51a862283c5d992ceda41960e81aa09b979211468fcddde"));
        assert(genesis.hashMerkleRoot     == uint256S("0x038bb92b0d3d55cc2288cfed57135425058e29834e759a3e078486023ed8852a"));

        consensus.fPowAllowMinDifficultyBlocks           = true;
        consensus.powLimit                               = ~UINT256_ZERO >> 20;   // CONCRETE starting difficulty is 1 / 2^12
        consensus.posLimitV1                             = ~UINT256_ZERO >> 24;
        consensus.posLimitV2                             = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks                     = 144;                   // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations                = 3;                     // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity                      = 100;
        consensus.nFutureTimeDriftPoW                    = 7200;
        consensus.nFutureTimeDriftPoS                    = 180;
        consensus.nMasternodeCountDrift                  = 4;                     // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut                           = 43199500 * COIN;
        consensus.nPoolMaxTransactions                   = 2;
        consensus.nProposalEstablishmentTime             = 60 * 5;                // at least 5 min old to make it into a budget
        consensus.nStakeMinAge                           = 0;
        consensus.nStakeMinDepth                         = 2;
        consensus.nTargetTimespan                        = 40 * 60;
        consensus.nTargetTimespanV2                      = 30 * 60;
        consensus.nTargetSpacing                         = 1 * 60;
        consensus.nTimeSlotLength                        = 15;

        consensus.nHalvingInterval                       = 525600;
        consensus.nInflationPerc                         = 0.14;
        consensus.nInflationPercAnnualDecrease           = 0.10;

        /* 
            Spork Key for RegTest:
              "PublicKey": "040876108cf6439f3ee4b0b5938ed699464369506162791f5c9ce8730af8c1c71caf295bc9ea5dfc67a0294b16df272ff3ef1ba27141cda9ffdfd2320da6b0cd2c",
              "PrivateKey": "4dPeoAv1oeB2wVGEyi3L5umhEfkAryfCZh86NPunfSf7HHQmNWQ"
        */

        consensus.strSporkPubKey                         = "040876108cf6439f3ee4b0b5938ed699464369506162791f5c9ce8730af8c1c71caf295bc9ea5dfc67a0294b16df272ff3ef1ba27141cda9ffdfd2320da6b0cd2c";
        consensus.strSporkPubKeyOld                      = "";
        consensus.nTime_EnforceNewSporkKey               = 0;
        consensus.nTime_RejectOldSporkKey                = 0;

        consensus.height_last_PoW                        = 1000;
        consensus.height_last_ZC_AccumCheckpoint         = 0;
        consensus.height_last_ZC_WrappedSerials          = 0;
        consensus.height_start_BIP65                     = 0;                      // Block v5
        consensus.height_start_InvalidUTXOsCheck         = 999999999;
        consensus.height_start_MessSignaturesV2          = 0;                      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1050;
        consensus.height_start_StakeModifierV2           = 1100;                   // Block v6
        consensus.height_start_TimeProtoV2               = 1200;                   // Block v7
        consensus.height_start_ZC                        = 1050;                   // Block v4
        consensus.height_start_ZC_InvalidSerials         = 999999999;
        consensus.height_start_ZC_PublicSpends           = 1300;
        consensus.height_start_ZC_SerialRangeCheck       = 999999999;
        consensus.height_start_ZC_SerialsV2              = 1400;
        consensus.height_ZC_RecalcAccumulators           = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus                             = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                                                           "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                                                           "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                                                           "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                                                           "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                                                           "31438167899885040445364023527381951378636564391212010397122822120720357";
                                                           
        consensus.ZC_MaxPublicSpendsPerTx                = 637;                   // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx                      = 7;                     // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations                = 10;
        consensus.ZC_MinMintFee                          = 1 * CENT;
        consensus.ZC_MinStakeDepth                       = 10;
        consensus.ZC_TimeStart                           = 0;                     // not implemented on regtest
        consensus.ZC_WrappedSerialsSupply                = 0;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa0;
        pchMessageStart[1] = 0xd0;
        pchMessageStart[2] = 0x7f;
        pchMessageStart[3] = 0xab;
        nDefaultPort = 32816;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
