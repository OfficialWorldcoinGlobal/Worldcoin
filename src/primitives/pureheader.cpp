// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Worldcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/pureheader.h"

#include "crypto/scrypt.h"
#include "hash.h"
#include "utilstrencodings.h"

#include <auxpowforkparams.h>

void CPureBlockHeader::SetBaseVersion(int32_t nBaseVersion, int32_t nChainId)
{
    assert(nBaseVersion >= 1 && nBaseVersion < VERSION_AUXPOW);
    assert(!IsAuxpow());
    nVersion = nBaseVersion | (nChainId * VERSION_CHAIN_START);
}

uint256 CPureBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

uint256 CPureBlockHeader::GetPoWHash() const
{
    uint256 thash;
    scrypt_1024_1_1_256(BEGIN(nVersion), BEGIN(thash));
    return thash;
}

bool CPureBlockHeader::IsAuxpow() const
{
    return nVersion & VERSION_AUXPOW;
}

bool CPureBlockHeader::IsLegacy() const
{
    return ((nVersion & 0xff) < 4) || (GetChainId() != AUXPOW_CHAIN_ID);
}



