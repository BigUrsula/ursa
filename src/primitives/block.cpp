// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <hash.h>
#include <streams.h>
#include <tinyformat.h>
#include <utilstrencodings.h>



uint32_t nHeavyHashActivationTime;


uint256 CBlockHeader::GetHash() const
{
    if (nTime < nHeavyHashActivationTime) {
        std::vector<unsigned char> vch(80);
        CVectorWriter ss(SER_GETHASH, PROTOCOL_VERSION, vch, 0);
        ss << *this;
        //std::cout<<"HASHX11"<<std::endl;
        return HashX11((const char *)vch.data(), (const char *)vch.data() + vch.size());
    } else {
        //std::cout<<"HEAVYHASH"<<std::endl;
        //std::cout<<nTime<<std::endl;
        //std::cout<<nHeavyHashActivationTime<<std::endl;
        return GetHeavyHash();
    }
}


uint256 CBlockHeader::GetHeavyHash() const
{
    uint256 seed;
    CSHA3_256().Write(hashPrevBlock.begin(), 32).Finalize(seed.begin());
    uint64_t matrix[64*64];
    GenerateHeavyHashMatrix(seed, matrix);
    return SerializeHeavyHash(*this, matrix);
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
