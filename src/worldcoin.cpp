// Copyright (c) 2015-2017 The Worldcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>

#include <arith_uint256.h>
#include <worldcoin.h>
#include <pow.h>
#include <util.h>

// As Worldcoin calculate block reward using trigonometric functions to follow the Earth rotation ...
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

int static generateMTRandom(unsigned int s, int range)
{
    boost::mt19937 gen(s);
    boost::uniform_int<> dist(1, range);
    return dist(gen);
}

// Worldcoin: Normally minimum difficulty blocks can only occur in between
// retarget blocks. However, once we introduce Digishield every block is
// a retarget, so we need to handle minimum difficulty on all blocks.
bool AllowDigishieldMinDifficultyForBlock(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
   // never allow minimal difficulty, WDC retarget works fine	
    return false;
}

//unsigned int CalculateWorldcoinNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
//{
//    // do not change retarget algo	
//    return CalculateNextWorkRequired(pindexLast, nFirstBlockTime, params);
//}

bool CheckAuxPowProofOfWork(const CBlockHeader& block, const Consensus::Params& params)
{
    // check legacy blocks and non-AUXPOW
    if ( block.IsLegacy() || !block.IsAuxpow() ) {
        if (block.auxpow)
            return error("%s : legacy block with auxpow properties",
                         __func__);
        return CheckProofOfWork(block.GetPoWHash(), block.nBits, params);
    }

    /* We have auxpow.  Check it.  */
    if (!block.auxpow)
            return error("%s : auxpow block without auxpow properties",
                         __func__);

    /* Except for legacy blocks with full version 1, ensure that
       the chain ID is correct.  Legacy blocks are not allowed since
       the merge-mining start, which is checked in AcceptBlockHeader
       where the height is known.  */
    if (params.fStrictChainId && (block.GetChainId() != params.nAuxpowChainId) )
        return error("%s : block does not have our chain ID"
                     " (got %d, expected %d, full nVersion %d)",
                     __func__, block.GetChainId(),
                     params.nAuxpowChainId, block.nVersion);

    if (!block.auxpow->check(block.GetHash(), block.GetChainId(), params))
        return error("%s : AUX POW is not valid", __func__);
    if (!CheckProofOfWork(block.auxpow->getParentBlockPoWHash(), block.nBits, params))
        return error("%s : AUX proof of work failed", __func__);

    return true;	
}



unsigned int CalculateWorldcoinNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    int nHeight = pindexLast->nHeight + 1;
    int64_t retargetTimespan = params.nPowTargetTimespan;
    int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
    int64_t nModulatedTimespan = nActualTimespan;
    int64_t nMaxTimespan;
    int64_t nMinTimespan;

    bool fNewDifficultyProtocol = (nHeight >= params.nDiffChangeTarget);

    if (fNewDifficultyProtocol) {
        retargetTimespan = params.nTargetTimespanRe;
        nMinTimespan = (retargetTimespan - (retargetTimespan/10));
        nMaxTimespan = (retargetTimespan + (retargetTimespan/10));  
    } else {
        retargetTimespan = params.nPowTargetTimespan;
        nMinTimespan = retargetTimespan/4;
        nMaxTimespan = retargetTimespan*4;
    }

    // Limit adjustment step
    if (nModulatedTimespan < nMinTimespan)
        nModulatedTimespan = nMinTimespan;
    else if (nModulatedTimespan > nMaxTimespan)
        nModulatedTimespan = nMaxTimespan;

    // Retarget
    arith_uint256 bnNew;
    arith_uint256 bnOld;
    bnNew.SetCompact(pindexLast->nBits);
    bnOld = bnNew;
    // litecoin: intermediate uint256 can overflow by 1 bit
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    bool fShift = bnNew.bits() > bnPowLimit.bits() - 1;
    if (fShift)
        bnNew >>= 1;
    bnNew *= nModulatedTimespan;
    bnNew /= retargetTimespan;
    if (fShift)
        bnNew <<= 1;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

CAmount GetWorldcoinBlockSubsidy(int nHeight, const Consensus::Params& consensusParams)
{
    const CAmount nMinSubsidy = 1 * COIN;
    // base payout
    CAmount nSubsidy = 50 * COIN;
    // bypass, don't use this function
    return nSubsidy;
}
