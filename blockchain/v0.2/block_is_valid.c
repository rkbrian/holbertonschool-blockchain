#include "blockchain.h"

block_t const GEN_BLOCK_COPY = {
	{
		0,
		0,
		1537578000,
		0,
		{0}
	}, /* can't reuse non-pointer struct from blockchain_create() */
	{
		GENESIS_STRING,
		16
	},
	GENESIS_HASH
};

/**
 * block_is_valid - verify that a Block is valid
 * @block: points to the Block to check
 * @prev_block: points to the previous Block in the Blockchain,
 *  or is NULL if block is the first Block of the chain
 * Return: 0 if valid, 1 if invalid
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buffer[SHA256_DIGEST_LENGTH];

	if (!block || (!prev_block && block->info.index)) /* block must exist */
		return (1);
	if (block->info.index == 0) /* case no prev */
		return (gen_block_validity(block));
	if (block->info.index != prev_block->info.index + 1) /* neighbor check */
		return (1);
	block_hash(prev_block, hash_buffer);
	if (memcmp(hash_buffer, prev_block->hash, sizeof(hash_buffer)) != 0)
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash,
		   SHA256_DIGEST_LENGTH) != 0)
		return (1);
	block_hash(block, hash_buffer);
	if (memcmp(hash_buffer, block->hash, sizeof(hash_buffer)) != 0)
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	return (0);
}

/**
 * gen_block_validity - verify if the given head block is a genesis block
 * @block: points to the Block to check
 * Return: 0 if valid, 1 if invalid
 */
int gen_block_validity(block_t const *block)
{
	if ((block->info.index != GEN_BLOCK_COPY.info.index) ||
	    (block->info.difficulty != GEN_BLOCK_COPY.info.difficulty) ||
	    (block->info.timestamp != GEN_BLOCK_COPY.info.timestamp) ||
	    (block->info.nonce != GEN_BLOCK_COPY.info.nonce) ||
	    (memcmp(block->info.prev_hash, GEN_BLOCK_COPY.info.prev_hash,
		    SHA256_DIGEST_LENGTH)) ||
	    (block->data.len != GEN_BLOCK_COPY.data.len) ||
	    (memcmp(block->data.buffer, GEN_BLOCK_COPY.data.buffer,
		    GEN_BLOCK_COPY.data.len) != 0) ||
	    (memcmp(block->hash, GEN_BLOCK_COPY.hash, SHA256_DIGEST_LENGTH) != 0))
		return (1);
	return (0);
}
