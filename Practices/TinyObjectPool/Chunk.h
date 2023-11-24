/*
 * @Author: Tairan Gao
 * @Date:   2023-11-22 10:47:14
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-24 15:05:08
 */

#ifndef CHUNK_H //
#define CHUNK_H

#include <cstddef>

// Allocates only onject of one given size
// Bottom of the heirarchy, handles the raw data

class FixedAllocator;

class Chunk
{
    // make sure that Chunk can only be manipulated by FixedAllocator
    friend class FixedAllocator;

private:
    void Init(std::size_t blockSize, unsigned char blocks);
    void Reset(std::size_t blockSize, unsigned char blocks);
    [[nodiscard]] void *Allocate(std::size_t blockSize);
    void Deallocate(void *p, std::size_t blockSize);
    void Release();

    bool IsBlockAvailable(void *p, unsigned char numBlocks, std::size_t blockSize) const;

    inline bool IsFilled() const { return (blocksAvailable_ == 0); };
    inline bool HasAvailable(unsigned char numBlocks) const { return (blocksAvailable_ >= numBlocks); }
    inline bool HasBlock(void *p, std::size_t chunkLength) const
    {
        std::byte *p_ = reinterpret_cast<std::byte *>(p);
        return (pData_ <= p_) && (p_ < pData_ + chunkLength);
    }

private:
    std::byte *pData_ = nullptr;
    unsigned char firstAvailableBlock_;
    unsigned char blocksAvailable_;
};

#endif // CHUNK_H