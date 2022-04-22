#include "blockchain.h"

/**
 * block_mine - mine a Block in order to insert it in the Blockchain,
 *  must find a hash for block that matches its difficulty
 * @block: points to the Block to be mined
 */
void block_mine(block_t *block)
{
	if (!block)
		return;
	if (block->info.difficulty == 0)
		return;
	block_hash(block, block->hash);
	while (!hash_matches_difficulty(block->hash, block->info.difficulty))
		block->info.nonce += 1, block_hash(block, block->hash);
}
