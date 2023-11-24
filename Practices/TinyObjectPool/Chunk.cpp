/*
 * @Author: Tairan Gao
 * @Date:   2023-11-22 10:47:14
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-24 15:19:33
 */

#include <cassert>
#include <climits>
#include <bitset>

#include "Chunk.h"

// Allocates only onject of one given size

void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
    const std::size_t allocSize = blockSize * blocks;
    pData_ = new std::byte[allocSize]; // Throws std::bad_alloc if allocation fails
    Reset(blockSize, blocks);
}

void Chunk::Reset(std::size_t blockSize, unsigned char blocks)
{
    firstAvailableBlock_ = 0;
    blocksAvailable_ = blocks;
    std::byte *p = pData_;
    // setting up a simple linked list within the allocated memory to keep track of the available blocks
    for (unsigned char i = 0; i != blocks; p += blockSize)
    {
        *p = std::byte(++i);
    }
}

[[nodiscard]] void *Chunk::Allocate(std::size_t blockSize)
{
    if (!blocksAvailable_)
        return nullptr;

    auto pResult = pData_ + (firstAvailableBlock_ * blockSize);

    // Update firstAvailableBlock_ to point to the next block

    // The casting required when using std::byte (like reinterpret_cast) does not hurt runtime efficiency.
    // These casts are a compile-time operation and have no runtime overhead.
    // They are just instructions to the compiler on how to treat the data.
    firstAvailableBlock_ = static_cast<unsigned char>(*reinterpret_cast<std::byte *>(pResult));

    --blocksAvailable_;
    return pResult;
}

void Chunk::Deallocate(void *p, std::size_t blockSize)
{
    assert(p >= pData_);
    auto toRelease = static_cast<std::byte *>(p);

    assert((toRelease - pData_) % blockSize == 0);
    *toRelease = std::byte(firstAvailableBlock_);
    firstAvailableBlock_ = static_cast<unsigned char>((toRelease - pData_) / blockSize);

    assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);
    ++blocksAvailable_;
}

void Chunk::Release()
{
    delete[] pData_;  // Deallocate the memory block
    pData_ = nullptr; // Reset the pointer to prevent dangling references
    firstAvailableBlock_ = 0;
    blocksAvailable_ = 0;
}

bool Chunk::IsBlockAvailable(void *p, unsigned char numBlocks, std::size_t blockSize) const
{
    if (IsFilled())
        return false;

    auto place = reinterpret_cast<std::byte *>(p);
    auto blockIndex = static_cast<unsigned char>((place - pData_) / blockSize);

    if (firstAvailableBlock_ == blockIndex)
        return true;

    std::bitset<UCHAR_MAX> foundBlocks;
    for (unsigned char cc = 0, index = firstAvailableBlock_; cc < blocksAvailable_; ++cc)
    {
        auto *nextBlock = pData_ + (index * blockSize);
        foundBlocks.set(index, true);

        if (index == blockIndex)
            return true;

        index = static_cast<unsigned char>(*nextBlock);
        assert(numBlocks > index && !foundBlocks.test(index));
    }

    return false;
}