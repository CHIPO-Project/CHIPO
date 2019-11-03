// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The CHIPO developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

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
                // CHIPODevs - RELEASE CHANGE - Checkpoints, timestamp of last checkpoint, total nr. of transactions
                (       0,       uint256("00000d6a63eb633e56ce5f7b1bd3a0f2126e500d2bd65affda33c775920acb88"))
                
                
        ;

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        0, // * UNIX timestamp of last checkpoint block
        0,       // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
                (       0, uint256("000003bdafaf3aa717d2ffe487af95ce6c92204eadbb6385d02aae69254ded67"))
        ;        // First PoW block
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        0,
        0,
        0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000bfd7b376c469fd66c0121df4f9b368a46a9afe3f685fa0454bbc521e090"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xd7;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0xb3;
        vAlertPubKey = ParseHex("");

        nDefaultPort = 32181;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // CHIPO starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;       // Halving interval
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nCurrentHeaderVersion = 3;              //Block headers BIP66
        nMinerThreads = 0;                      // Obsolete (**TODO**)
        nTargetTimespan = 1 * 60;               // CHIPO: 1 minute
        nTargetSpacing = 1 * 60;                // CHIPO: 1 minute
        nMaturity = 110;                         // Block maturity
        nMasternodeCountDrift = 5;
        nMaxMoneyOut = 120000000 * COIN;        // Large number effectively unlimited. Will deprecate TODO
        nMasternodeCollateral = 10000;          // Masternode Collateral requirement
        /** Height or Time Based Activations **/
        nLastPOWBlockOffset = 99;               // never PoS
        nModifierUpdateBlock = 1100;            // Modify block on height
        nZerocoinStartHeight = std::numeric_limits<int>::max();         // DISABLED FOR NOW TODO Zerocoin start height
        nZerocoinStartTime = 4102444799;        // off 2099/12/31 not supported.
        nBlockEnforceSerialRange = 1;           // Enforce serial range starting this block
        nBlockRecalculateAccumulators = std::numeric_limits<int>::max(); // Trigger a recalculation of accumulators
        nBlockFirstFraudulent = std::numeric_limits<int>::max();           // 1110; //First block that bad serials emerged (currently we do not have any) *** TODO ***
        nBlockLastGoodCheckpoint = std::numeric_limits<int>::max();        // Last valid accumulator checkpoint (currently we do not have any) *** TODO ***
        nBlockEnforceInvalidUTXO = 5;        // Start enforcing the invalid UTXO's

        const char* pszTimestamp = "Chorus Con Shikoku tournament, 6 groups go to the national tournament";

        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04461ffb5f4fdaf2b5a5cd3b4f821eae1bbb0149f94a3ffcebcd299c188cad1788e2381bfb055e48c864e292e5b262049299f0fb2cb554f06d68d9d55faca19dda") << OP_CHECKSIG;

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1; // do not change.
        genesis.nTime = 1567328400;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 710558;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("00000d6a63eb633e56ce5f7b1bd3a0f2126e500d2bd65affda33c775920acb88"));
        assert(genesis.hashMerkleRoot == uint256("0b6b159b80a35e75edda1c14990e203c611d9c9e5defc91285011f366eae2dce"));

        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("seed1.hashseeds.net","seed1.hashseeds.net"));
        vSeeds.push_back(CDNSSeedData("seed2.seedhash.net","seed2.seedhash.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); //C
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13); //6
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 156);

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x1F)(0x8F)(0x61).convert_to_container<std::vector<unsigned char> >(); //smcp
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x03)(0xE1)(0x2F)(0xA5).convert_to_container<std::vector<unsigned char> >(); //pmcp
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0xb5).convert_to_container<std::vector<unsigned char> >(); // No.437

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04211c8582a02756e24a08002e41c66a46059453a6ca30e361c3f1575e568d4acae95aeaf6d528cb1ebaeeb1ece19fff5ec11fadc744be0fd76a2ff8c1f53b08";
        strObfuscationPoolDummyAddress = "MgvN4Uzgtdd9R8fH12APsSNUTnrcjN9eH6";
        nStartMasternodePayments = 1530342535; //30.06 2018

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
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

        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0x33;
        pchMessageStart[3] = 0xd7;
        vAlertPubKey = ParseHex("04d63cf1a277ded9ae68547dd1abaad0790406a85219541b5acaa6e6224c541c41a64d11a0af53dd1156a74cba3bfd047b0506168d72b663c3a9493240f2dcffdc");

        nDefaultPort = 42281;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CHIPO: 1 min
        nTargetSpacing = 1 * 60;  // CHIPO: 1 min
        nLastPOWBlockOffset = 3;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000000 * COIN;
        nZerocoinStartHeight = 250;
        nZerocoinStartTime = 4102444799; // Saturday, Jan 1, 2019 00:00:00 AM (GMT)
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 1500; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 891737; //First block that bad serials emerged (currently we do not have any) *** TODO ***
        nBlockLastGoodCheckpoint = 1001; //Last valid accumulator checkpoint (currently we do not have any) *** TODO ***
        nBlockEnforceInvalidUTXO = 1600; //Start enforcing the invalid UTXO's

        genesis.nTime = 1567414800;
        genesis.nNonce = 569911;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000003bdafaf3aa717d2ffe487af95ce6c92204eadbb6385d02aae69254ded67"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed1.hashseeds.net","seed1.hashseeds.net"));
        vSeeds.push_back(CDNSSeedData("seed2.seedhash.net","seed2.seedhash.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);//T
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 3);//2
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 194);

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x22)(0x11)(0xC2).convert_to_container<std::vector<unsigned char> >();//stcp
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x03)(0xE3)(0xB2)(0x06).convert_to_container<std::vector<unsigned char> >();//ptcp
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        // we enable for test purpose low dif mining on main
        nPoolMaxTransactions = 2;
        strSporkKey = "0483f4691596f9728bbb1b382981b0d4c50805489b115164035815e3da68c49fbecea348c8ea6b08858604376ad73ead4cc54390d80cade8fc9c16602ec07b99a4";
        strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 1510272000;
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

        pchMessageStart[0] = 0xa6;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0xd1;

        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // CHIPO: 1 day
        nTargetSpacing = 1 * 60;        // CHIPO: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1567479600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 3071713;
       
        nDefaultPort = 13380;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("00000bfd7b376c469fd66c0121df4f9b368a46a9afe3f685fa0454bbc521e090"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

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
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
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
