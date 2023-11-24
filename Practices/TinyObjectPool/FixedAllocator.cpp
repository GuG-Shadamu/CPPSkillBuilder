/*
 * @Author: Tairan Gao
 * @Date:   2023-11-22 13:12:38
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-24 15:22:59
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

    FixedAllocator();
    ~FixedAllocator();

private:
    Chunk *VicinityFind(void *p) const;
    void DoDeallocate(void *p);

private:
    std::size_t blockSize_;
    unsigned char numBlocks_;
    Chunks chunks_;
    Chunk *allocChunk_ = nullptr;
    Chunk *deallocChunk_ = nullptr;
    Chunk *emptyChunk_ = nullptr;
};

FixedAllocator::FixedAllocator()
    : blockSize_(0), numBlocks_(0), chunks_({}), allocChunk_(nullptr), deallocChunk_(nullptr), emptyChunk_(nullptr)
{
}

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
    Chunk *foundChunk = (hint) ? hint : VicinityFind(p);
    if (!foundChunk)
        return;

    if (foundChunk->IsBlockAvailable(p, numBlocks_, blockSize_))
        return;
    deallocChunk_ = foundChunk;
    DoDeallocate(p);
}

Chunk *FixedAllocator::VicinityFind(void *p) const
{
    if (chunks_.empty())
        return nullptr;

    assert(deallocChunk_);

    const std::size_t chunkLength = numBlocks_ * blockSize_;
    Chunk *lo = deallocChunk_;
    Chunk *hi = deallocChunk_ + 1;
    const Chunk *loBound = &chunks_.front();
    const Chunk *hiBound = &chunks_.back() + 1;

    // Special case: deallocChunk_ is the last in the array
    if (hi == hiBound)
        hi = nullptr;

    while (true)
    {
        if (lo)
        {
            if (lo->HasBlock(p, chunkLength))
                return lo;
            if (lo == loBound)
            {
                lo = nullptr;
                if (!hi)
                    break;
            }
            else
                --lo;
        }

        if (hi)
        {
            if (hi->HasBlock(p, chunkLength))
                return hi;
            if (++hi == hiBound)
            {
                hi = nullptr;
                if (!lo)
                    break;
            }
        }
    }

    return nullptr;
}

void FixedAllocator::DoDeallocate(void *p)
{
    // Deallocate from the current chunk
    deallocChunk_->Deallocate(p, blockSize_);

    if (deallocChunk_->HasAvailable(numBlocks_))
    {
        if (emptyChunk_)
        {
            auto *lastChunk = &chunks_.back();

            // Check if deallocChunk_ is the last chunk
            if (lastChunk == deallocChunk_)
            {
                deallocChunk_ = emptyChunk_;
            }
            else if (lastChunk != emptyChunk_)
            {
                std::swap(*emptyChunk_, *lastChunk);
            }
            // Release the last chunk and remove it from the vector
            lastChunk->Release();
            chunks_.pop_back();

            // Update allocChunk_ if necessary
            if ((allocChunk_ == lastChunk) || allocChunk_->IsFilled())
            {
                allocChunk_ = deallocChunk_;
            }
        }
        emptyChunk_ = deallocChunk_;
    }
}
