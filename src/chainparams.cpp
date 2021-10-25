// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin developers
// Copyright (c) 2009-2018 The Litecoin developers
// Copyright (c) 2009-2018 The Dogecoin developers
// Copyright (c) 2019 The WorldCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>
#include <auxpowforkparams.h>

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
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1386325540, nBits=1e0ffff0, nNonce=99943, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "May 13, 2013 11:34pm EDT: U.S. crude futures were up 0.3 percent at $95.41 a barrel";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
		//Fix me
        consensus.nSubsidyHalvingInterval = 4147200;
        consensus.BIP16Exception = uint256();
        //consensus.BIP16Height = 0; // October 1, 2012 it was before WDC genesis // int64 nBIP16SwitchTime = 1349049600
        consensus.BIP34Height = 71000000;      // WDC dev note: after this height only block version 2 are allowed;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 999999999; // WDC dev note: disabled for now     // OP_CHECKLOCKTIMEVERIFY
        consensus.BIP66Height = 999999999; // WDC dev note: disabled for now


        consensus.nDiffChangeTarget = 600000;
        consensus.patchBlockRewardDuration = 20160;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 0.35 *24 * 60 * 60;	// worldcoin: 0.35 day
        consensus.nPowTargetSpacing = 15;					// worldcoin: 15 sec
        
        consensus.nTargetTimespanRe = 60 * 60;	            // worldcoin: 1 hour
        consensus.nTargetSpacingRe = 1 * 30;				// worldcoin: 30 sec
        
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1611720000; // Wednesday, January 27, 2021 4:00:00 AM
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1614398400; // Saturday, February 27, 2021 4:00:00 AM


        // Deployment of BIP68, BIP112, and BIP113.
        // XXX: BIP heights and hashes all need to be updated to Worldcoin values
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1611720000; // Wednesday, January 27, 2021 4:00:00 AM
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1614398400; // Saturday, February 27, 2021 4:00:00 AM

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1611720000; // Wednesday, January 27, 2021 4:00:00 AM
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1614398400; // Saturday, February 27, 2021 4:00:00 AM



        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000039074d9094ce9aa5");
		
        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xd16fbc79554b9759c6c81c90e509bc90e94764637ae43b86a4573ab33807f664");

        // AuxPoW parameters
		consensus.nAuxpowChainId = AUXPOW_CHAIN_ID;
        consensus.nAuxpowStartHeight = AUXPOW_START_HEIGHT;
        consensus.fStrictChainId = true;
        consensus.nLegacyBlocksBefore = AUXPOW_START_HEIGHT;    

        // Blocks 6569805 - 6601666 are  AuxPoW without LWMA
        consensus.nDiffChangeTargetLWMA = LWMA_START_HEIGHT;
        consensus.nLWMAPowTargetTimespan = 30; // post-lwma: 0.5 minute
        consensus.lwmaAveragingWindow = 120;
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        nDefaultPort = 11081;
        nPruneAfterHeight = 100000;
        
        genesis = CreateGenesisBlock(1368503907, 102158625, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

	//uint32_t *p = (uint32_t *)&consensus.hashGenesisBlock;
 	////LogPrint(BCLog::ALL, "CreateGenesisBlock GetHash is 0x%X\n", consensus.hashGenesisBlock);
	////fwrite(&consensus.hashGenesisBlock, sizeof(char), sizeof(consensus.hashGenesisBlock), stdout);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fprintf(stdout,"%X ", *p++);
	//fflush(stdout);

        assert(consensus.hashGenesisBlock == uint256S("0x7231b064d3e620c55960abce2963ea19e1c3ffb6f5ff70e975114835a7024107"));
        assert(genesis.hashMerkleRoot == uint256S("0x4fe8c1ba0a102fea0643287bb22ce7469ecb9b690362013f269a423fefa77b6e"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.

        vSeeds.emplace_back("72.18.200.11:11081");
        vSeeds.emplace_back("72.18.200.81:11081");
        vSeeds.emplace_back("51.91.94.23:11081");
        vSeeds.emplace_back("64.235.35.46:11081");
        vSeeds.emplace_back("87.99.119.6:11081");
        vSeeds.emplace_back("103.147.12.229:11081");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,73);
        // base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);  // 
		//Fix me:
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,135);    // segwit addresses will start with W
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,201);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "wdc";

        //TODO: fix this for worldcoin -- plddr
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //vFixedSeeds.clear();

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {  0,       uint256S("0x7231b064d3e620c55960abce2963ea19e1c3ffb6f5ff70e975114835a7024107")},
                {  1,       uint256S("0x1a48c2bf97e0df6d4f03cd5cb0896ef43b04987048fbeb5ab2dc013335e40731")},
                {  50, uint256S("0x98fb00f9a3559063b2bf890fc0b16b99fecd3f87634ffd384917603fb535320b")},
                {  100, uint256S("0xf3ab5c3dc665f4e36654af1208910d72075664c9a9883a3d1403255c50a72996")},
                {  1000, uint256S("0x3cbc5f253052bc892fc77c5419e06afbe1237eb187df0693a332d6a836c9417c")},
                {  5000, uint256S("0xd4641bd171ccfbd571bead813ee31cee4d60581b28c1de6be68fb1fde63643f0")},
                {  10000, uint256S("0x1f1b1265d26e097af90ad524d3342b13765750e77b7fec77ff957f1147ef5b41")},
                {  50000, uint256S("0x430d653a28a4bbaf3da98b6bcbc034aaf3151950eb0cff680c36b09c12d7c2b3")},
                {  100000, uint256S("0x15394ecf8684bb31821ef0d9ddffe56ea49364d2e2cdcb771c94f95f0817b7c1")},
                {  500000, uint256S("0x4c94848c214c4779cbaa15d83b0bbee57afce5e754184368e6b25ac084689608")},
                {  1000000, uint256S("0xce846668f4120671a9a5fc1b863482c5991c451b9a848a57cf9f563bf54a5baf")},
                {  2000000, uint256S("0xf82b25241763f20e1f5981390b6580a46e8e9bfb9dd3dd8c771a4115be4b4996")},
                {  3000000, uint256S("0xeb8a9b0a0692dcdc66edc216aba6c316b62b4b0125263bf161993ca530969265")},
                {  4000000, uint256S("0x938eb1050f5f7c4d11b6e8435413e4d98c906fcb572ef4b062d3559c4dd4f124")},
                {  5000000, uint256S("0x0418d1e279f1c1cf4c52eeaf668356622931d100147454c020a2ae6f13185acd")},
                {  6000000, uint256S("0x0a89bd046c42d7a0c125173209a5de6bb8f8cf3a3748a588796c5ad7b43c682e")},
                {  6570530, uint256S("0x0481191e24da748820450e562f7b4ad450eddcabe66291cab91b1a947996a5b1")},
                {  6642500, uint256S("0xd16fbc79554b9759c6c81c90e509bc90e94764637ae43b86a4573ab33807f664")},
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 6642500 d16fbc79554b9759c6c81c90e509bc90e94764637ae43b86a4573ab33807f664
            /* nTime    */ 1635180496,
            /* nTxCount */ 8839767,
            /* dTxRate  */ 0.03314798533777966
        };

        /* disable fallback fee on mainnet */
		//Fix me
        m_fallback_fee_enabled = true;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 525600;
        consensus.BIP16Exception = uint256();
        //consensus.BIP16Height = 0; // always enforce P2SH BIP16 on testnet
        consensus.BIP34Height = 76;
        consensus.BIP34Hash = uint256S("8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573");
        consensus.BIP65Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.BIP66Height = 76; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // 7 days
        consensus.nPowTargetSpacing = 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x14b1da80b3d734d36a4a2be97ed2c9d49e79c47213d5bcc15b475a1115d28918"); //0

	// AuxPoW parameters
        consensus.nAuxpowChainId = AUXPOW_CHAIN_ID;
	consensus.nAuxpowStartHeight = 5;            // test-net only	
        consensus.fStrictChainId = true;
	consensus.nLegacyBlocksBefore = 5;           // test-net only
        
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xf1;
        nDefaultPort = 25677;
        nPruneAfterHeight = 1000;
        
        genesis = CreateGenesisBlock(1396382110, 1529337473, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xdf83d8ce31005c88ee7e27aaf802a96dd6042800300c35d3045fe013a105ac39"));
        assert(genesis.hashMerkleRoot == uint256S("0x4fe8c1ba0a102fea0643287bb22ce7469ecb9b690362013f269a423fefa77b6e"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
	    //vSeeds.emplace_back("testnet-seed.eacpay.com");
	    //vSeeds.emplace_back("testnet-seed.worldcoin.global");    

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        //base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "twdc";

        //TODO: fix this for worldcoin -- plddr
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
        //vFixedSeeds.clear();

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0xdf83d8ce31005c88ee7e27aaf802a96dd6042800300c35d3045fe013a105ac39")},
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 438b7e1c86f58b4e62e8cf2d0f9f256e3dddaebc5d1cc568e633a38e0db6c025
            /* nTime    */ 1565582448,
            /* nTxCount */ 2848910,
            /* dTxRate  */ 0.02265200874042768
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 1;
        consensus.nPowTargetTimespan = 30 * 60; 
        consensus.nPowTargetSpacing = 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (60 instead of 240)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 19444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1396382110, 1529337473, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //LogPrint(BCLog::ALL, "CreateGenesisBlock GetHash is 0x%X\n", consensus.hashGenesisBlock);
        assert(consensus.hashGenesisBlock == uint256S("0x14b1da80b3d734d36a4a2be97ed2c9d49e79c47213d5bcc15b475a1115d28918"));
        assert(genesis.hashMerkleRoot == uint256S("0x13757c3610411891452ac1f04d7f81946339b0e5b5aba216e6646e81805c4bb1"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("0x14b1da80b3d734d36a4a2be97ed2c9d49e79c47213d5bcc15b475a1115d28918")},
            }
        };
        
        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        // base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rwdc";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
