/*
 * @Author: Tairan Gao
 * @Date:   2023-11-22 13:12:38
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-22 15:33:32
 */

#ifndef FIXEDALLOCATOR_H //
#define FIXEDALLOCATOR_H

#include <cstddef>
#include <vector>

#include "Chunk.cpp"

class FixedAllocator
{
private:
    std::size_t blockSize_;
    unsigned char numBlocks_;
    typedef std::vector<Chunk> Chunks;
    Chunks chunks_;
    Chunk *allocChunk_ = nullptr;
    Chunk *deallocChunk_ = nullptr;
};

#endif // FIXEDALLOCATOR_H