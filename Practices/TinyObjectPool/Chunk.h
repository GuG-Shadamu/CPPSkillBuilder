/*
 * @Author: Tairan Gao
 * @Date:   2023-11-22 10:47:14
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-22 15:51:25
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

public:
private:
    void Init(std::size_t blockSize, unsigned char blocks);
    [[nodiscard]] void *Allocate(std::size_t blockSize);
    void Deallocate(void *p, std::size_t blockSize);
    void Release();

private:
    std::byte *pData_ = nullptr;
    unsigned char firstAvailableBlock_;
    unsigned char blocksAvailable_;
};

#endif // CHUNK_H