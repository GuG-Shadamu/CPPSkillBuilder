/*
 * @Author: Tairan Gao
 * @Date:   2023-11-22 13:12:38
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-22 20:13:27
 */

#include <cstddef>
#include <cassert>
#include <vector>

#include "Chunk.h"

// Handles all Chunks of the size given to blockSize
class FixedAllocator
{
    using Chunks = std::vector<Chunk>;

public:
    void *Allocate();
    void Deallocate(void *p, Chunk *hint);
    ~FixedAllocator();

private:
    std::size_t blockSize_;
    unsigned char numBlocks_;
    Chunks chunks_;
    Chunk *allocChunk_ = nullptr;
    Chunk *deallocChunk_ = nullptr;

    Chunk *emptyChunk_ = nullptr;
};

FixedAllocator::~FixedAllocator()
{
    for (auto &&chunk : chunks_)
        chunk.Release();
}

void *FixedAllocator::Allocate()
{
    if (allocChunk_ == 0 || allocChunk_->blocksAvailable_ == 0)
    {
        // No available memory in this chunk
        // Try to find one

        bool found = false;
        for (auto &chunk : chunks_)
        {
            if (chunk.blocksAvailable_ > 0)
            {
                // Found a chunk
                allocChunk_ = &chunk;
                found = true;
                break;
            }
        }

        if (!found)
        {
            // All filled up - add a new chunk
            chunks_.reserve(chunks_.size() + 1);
            Chunk newChunk;
            newChunk.Init(blockSize_, numBlocks_);
            chunks_.push_back(newChunk);
            allocChunk_ = &chunks_.back();
            deallocChunk_ = &chunks_.back();
        }
    }
    assert(allocChunk_ != 0);
    assert(allocChunk_->blocksAvailable_ > 0);
    return allocChunk_->Allocate(blockSize_);
}

void FixedAllocator::Deallocate(void *p, Chunk *hint)
{
    if (p == nullptr)
        return;

    if (emptyChunk_ == nullptr)
    {
        p->
    }
}