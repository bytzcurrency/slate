// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018 The SLATE developers
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
        (       0,	uint256("00000feb03167c4a4fa9f2bafcaea0e9f7e5646330e13c69e7ffa2dce58ace44") ) // Genesis block       
        (       1,  uint256("000002f68dbbf1fcfacb8f0b4e64083efdd2f07a906728ee068d573ffa5bcb4e") ) // First mined block
        (      25,  uint256("0000016f6d9c834f269f07e624feb02ba725e3d954017549afde932c8f6d6dc7") ) // Zerocoin enabled
        (      60,  uint256("00000039aca457e0dd2287e0fd636f1998e6b2774a64e8c18fa853776ec309c8") ) // Zerocoin V2 enabled
        (     200,  uint256("000000078d815b257737d227d50e22f2486fd3ded21c5c0bca347a410c71bd26") ) // Switch PoW-PoS
        (     201,  uint256("5542cf20a79e2658f45fc5385cc431035efae3980985254e01a08d930408bc52") ) // Switch PoW-PoS
        (     202,  uint256("016023220b7e1578f923a126dddecbf345d8004734afb52636f60954ba116d21") ) // Switch PoW-PoS
        (     300,  uint256("0cddd447eebbc7bd9f158bdc25eb1b290ab2b6f54ae77b07229c8da7b1999d99") ) //
        (     700,  uint256("eac3327ace445de2f39a6209b3a778d370a7e6d676c254d82e3d1c8de272559b") ) // tx=1230 time=1526558980
        (   67000,  uint256("727101d555687b91ed9740f3301048f3cfe5e5062babe491f2120ea7173b7234") ) // Add 3 premine blocks after this one
        (   69713,  uint256("097a4a371b031eea8d26384a15e894dc60fcb7cd8304f62ab35c760317c36e28") );// release v0.1.03

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1530892768, // * UNIX timestamp of last checkpoint block
    139385,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
        (       0,	uint256("0000065432f43b3efb23bd0f63fe33d00d02a5f36233fe1b982c08274d58ef12") ) // Genesis block       
        (    2300,  uint256("054b3a7370e9cc8141fc4c5255b8156bbff369a3b8691ead5a7f3198c4f0c3e4") );// release v0.1.03
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1530893198,
    4404,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
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
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xea;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0x81;
        vAlertPubKey = ParseHex("046741f2432dde5dfb6b019c6901aaa9fe611ec82c2848af3826017aeccc96d22aa3dfa32edfab2676f29b572451a645f2caf50101880d0b0027b9ff23c7b7a9c5");
        nDefaultPort = 37415;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // SLATE starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SLATE: 1 day
        nTargetSpacing = 1 * 60;  // SLATE: 1 minute
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 9500000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1000;
        nZerocoinStartHeight = 25;
        nZerocoinStartTime = 1524496462; // October 17, 2017 4:30:00 AM
        nBlockEnforceSerialRange = 25; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 100000002; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 100000000; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 100000200; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 60; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1525158000; //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1525158000; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * python genesis.py -z "Investing.com 23/Apr/2018 Facebook Gets First Downgrade Since Data Scandal" -t 1524496461 -n 67453891 -b 0x1e0ffff0 -v 0
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Investing.com 23/Apr/2018 Facebook Gets First Downgrade Since Data Scandal";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1524496461;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 67657104;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000feb03167c4a4fa9f2bafcaea0e9f7e5646330e13c69e7ffa2dce58ace44"));
        assert(genesis.hashMerkleRoot == uint256("0x80290404060ff7ff5bc6a42f755d24f6087ba5685474a5c8ffafac65de8b2bbf"));

        vSeeds.push_back(CDNSSeedData("slate.slate.io", "seed.slate.slate.io"));                       // Slate Entertainment Group DNS Seeder
        vSeeds.push_back(CDNSSeedData("seeder.slate.host", "main.seeder.slate.host"));                 // Slate DNS Seeder
        vSeeds.push_back(CDNSSeedData("slateseeder1.xhost.host", "main.slateseeder1.xhost.host"));     // Slate US1 DNS Seeder
        vSeeds.push_back(CDNSSeedData("slateseeder2.xhost.host", "main.slateseeder2.xhost.host"));     // Slate EU1 DNS Seeder
        vSeeds.push_back(CDNSSeedData("slateseeder3.xhost.host", "main.slateseeder3.xhost.host"));     // Slate ASIA1 (Singapore) DNS Seeder
        vSeeds.push_back(CDNSSeedData("slateseeder4.xhost.host", "main.slateseeder4.xhost.host"));     // Slate AUSTRALIA1 (Sydney) DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 140);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

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
        strSporkKey = "04700e916c512d08e658a97c7e76fab398968e4a442415f51d3907aeaa705831792197a9904597445d72a3f99ab200e264a8e767a6a2f8b499ec1684831f95cbc1";
        strSporkKeyOld = "04700e916c512d08e658a97c7e76fab398968e4a442415f51d3907aeaa705831792197a9904597445d72a3f99ab200e264a8e767a6a2f8b499ec1684831f95cbc1";
        strObfuscationPoolDummyAddress = "sMGx5WVasXzj2HNxd6xczLgzaUrY1RpaHH";
        nStartMasternodePayments = 1524496461; 

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
        nZerocoinHeaderVersion = BLOCKHEADER_ZEROCOIN_VERSION; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zslx to be stakable

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
        pchMessageStart[0] = 0x81;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0x9f;
        pchMessageStart[3] = 0x83;
        vAlertPubKey = ParseHex("049fabf4ea83728bdfd51caf8862b101ef14d03c1a7e88263fd84151aa4bcb50d06198e4709ae7c42ba97e32ac9adb70491c6524849ff13846925ef7cfbbd74df6");
        nDefaultPort = 47415;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SLATE: 1 day
        nTargetSpacing = 1 * 60;  // SLATE: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 9500000000 * COIN;
        nZerocoinStartHeight = 25;
        nZerocoinStartTime = 1524496462;
        nBlockEnforceSerialRange = 25; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 100000002; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 100000000; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 100000200; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 60; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1521604800; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        // python genesis.py -z "Investing.com 23/Apr/2018 Facebook Gets First Downgrade Since Data Scandal" -t 1524496461 -n 342781 -b 0x1e0ffff0 -v 0
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1524496461;
        genesis.nNonce = 846737;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000065432f43b3efb23bd0f63fe33d00d02a5f36233fe1b982c08274d58ef12"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet-slate.slate.io", "seed.testnet-slate.slate.io"));                  // Slate Entertainment Group DNS Seeder
        vSeeds.push_back(CDNSSeedData("seeder.slate.host", "testnet.seeder.slate.host"));                         // Slate DNS Seeder
        vSeeds.push_back(CDNSSeedData("slatetestseeder1.xhost.host", "testnet.slatetestseeder1.xhost.host"));     // Slate US1 DNS Seeder
        vSeeds.push_back(CDNSSeedData("slatetestseeder2.xhost.host", "testnet.slatetestseeder2.xhost.host"));     // Slate EU1 DNS Seeder
        vSeeds.push_back(CDNSSeedData("slatetestseeder3.xhost.host", "testnet.slatetestseeder3.xhost.host"));     // Slate ASIA1 (Singapore) DNS Seeder
        vSeeds.push_back(CDNSSeedData("slatetestseeder4.xhost.host", "testnet.slatetestseeder4.xhost.host"));     // Slate AUSTRALIA1 (Sydney) DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66); // Testnet slate addresses start with 'T'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 9);  // Testnet slate script addresses start with '4' or '5'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 144);     // Testnet private keys start with 'z' or '2'
        // Testnet slate BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet slate BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet slate BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04b33722601343992c8a651fafa0f424c6ac90f797d3f58d90eebf96e817e9d7ca76a40e3c53b3d47f6f6a60b0d36dbb94ee630a5ad622f08d92782999fe7b043a";
        strSporkKeyOld = "04b33722601343992c8a651fafa0f424c6ac90f797d3f58d90eebf96e817e9d7ca76a40e3c53b3d47f6f6a60b0d36dbb94ee630a5ad622f08d92782999fe7b043a";
        strObfuscationPoolDummyAddress = "TcShTh43pddH9bxzq1583cgHYE5rmbCfVF";
        nStartMasternodePayments = 1524496461; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
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
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x8f;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xcc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // SLATE: 1 day
        nTargetSpacing = 1 * 60;        // SLATE: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        // python genesis.py -z "Investing.com 23/Apr/2018 Facebook Gets First Downgrade Since Data Scandal" -t 1524496461 -n 12345 -b 0x207fffff -v 0
        genesis.nTime = 1524496461;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12351;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 47526;
        assert(hashGenesisBlock == uint256("0x618435c615f3d628acf97c19c4b3e6320555c62f515d4144425e4e8b7610fbab"));

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
        nDefaultPort = 47527;
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
