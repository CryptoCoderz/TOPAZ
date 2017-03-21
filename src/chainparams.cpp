// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xea;
        pchMessageStart[1] = 0x92;
        pchMessageStart[2] = 0x66;
        pchMessageStart[3] = 0xe4;
        vAlertPubKey = ParseHex("01a11447c27f9745bc6b132c04b94baafbba5d5257fe028e74682a62f7c2f81f85d113a216df3be197653f454852a2d08c6314aad5ca3cbe9977428ca9e1a4caab");
        nDefaultPort = 6909;
        nRPCPort = 6908;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        const char* pszTimestamp = "MagikPOS Malware Terrorizes Point of Sale Terminals Across the US and Canada - by JP Buntinx - March 19 2017"; 
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1489956950, vin, vout, 0); 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1489956950; 
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 59933;

        /** Genesis Block MainNet */
        /*
            Hashed MainNet Genesis Block Output
            block.hashMerkleRoot == 50996d33e77ebdaa246e5668bf0f2076ae680ae28f7e9109d9cd2e0e0be27d15
            block.nTime = 1489956950
            block.nNonce = 59933
            block.GetHash = 000075a98ba8ec549b0335f3f1b6e8390208d5dd8763da19ffadc1030c4a6d4a
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000075a98ba8ec549b0335f3f1b6e8390208d5dd8763da19ffadc1030c4a6d4a"));
        assert(genesis.hashMerkleRoot == uint256("0x50996d33e77ebdaa246e5668bf0f2076ae680ae28f7e9109d9cd2e0e0be27d15"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,97);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,42);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("Seed01",  "91.134.120.210"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 5 * 60; // Initially ~5 Min during PoW
        if(nBestHeight > nStartPoSBlock) // Scaled up for PoW/PoS twin phase
        {
            nTargetSpacing = 25 * 60;
        }
        nTargetTimespan = 10 * nTargetSpacing;
        nLastPoWBlock = 9999999; // PoW does not stop - TODO: Remove PoW height check, it's not needed
        nStartPoSBlock = 5000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xaa;
        pchMessageStart[3] = 0xb8;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        vAlertPubKey = ParseHex("01b11447c27f9745bc6b132c04b94baafbba5d5257fe028e74682a62f7c2f81f85d113a216df3be197653f454852a2d08c6314aad5ca3cbe9977428ca9e1a4caab");
        nDefaultPort = 6808;
        nRPCPort = 6807;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 369490;

        /** Genesis Block TestNet */
        /*
            Hashed TestNet Genesis Block Output
            block.hashMerkleRoot == 50996d33e77ebdaa246e5668bf0f2076ae680ae28f7e9109d9cd2e0e0be27d15
            block.nTime = 1489956950
            block.nNonce = 369490
            block.GetHash = 00000000b457702fab95e75540ee9647575d66eb8ee92831882bfec59392e31f
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000b457702fab95e75540ee9647575d66eb8ee92831882bfec59392e31f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,41);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,33);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 5 * 60;
        nLastPoWBlock = 0x7fffffff;
        nStartPoSBlock = 500;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x98;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1489956960;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 6707;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
            Hashed RegNet Genesis Block Output
            block.hashMerkleRoot == 50996d33e77ebdaa246e5668bf0f2076ae680ae28f7e9109d9cd2e0e0be27d15
            block.nTime = 1489956960
            block.nNonce = 8
            block.GetHash = b5ffb600b91639af9fad2c365362c2a3f7bd5d7b9e1eb992e869573419a26447
        */

        assert(hashGenesisBlock == uint256("0xb5ffb600b91639af9fad2c365362c2a3f7bd5d7b9e1eb992e869573419a26447"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
