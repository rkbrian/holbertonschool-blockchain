#include "blockchain.h"

/**
 * blockchain_difficulty - compute the difficulty to assign to a potential
 *  next Block in the Blockchain.
 * @blockchain: points to the Blockchain to analyze
 * Return: the difficulty to be assigned to a potential next Block in the
 *  Blockchain
 * Notes: difficulty adjustment rules
 *  Retrieve the last Block for which an adjustment was made,
 *  Compute the expected elapsed time between the two Blocks,
 *  Compute the actual elapsed time,
 *  The difficulty must be incremented if the elapsed time is lower than
 *  half the expected elapsed time,
 *  The difficulty must be decremented if the elapsed time is greater than
 *  twice the expected elapsed time,
 *  The difficulty should not change otherwise.
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	uint64_t exp_time, act_time; /* expected time difference and actual time */
	block_t *block = NULL, *prev_block = NULL;
	int prev_i = 0;

	if (!blockchain) /* basically impossible */
		return (0);
	block = llist_get_tail(blockchain->chain);
	/* Genesis Block or before condi of change */
	if (block->info.index == 0 ||
	    (block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL) > 0)
		return (block->info.difficulty);
	/* condi of change difficulty, i+1 for referable in range */
	prev_i = block->info.index - DIFFICULTY_ADJUSTMENT_INTERVAL + 1;
	prev_block = llist_get_node_at(blockchain->chain, prev_i);
	exp_time = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL;
	act_time = block->info.timestamp - prev_block->info.timestamp;
	if (act_time < (exp_time / 2))
		return (block->info.difficulty + 1);
	if (act_time > (exp_time * 2))
		return (block->info.difficulty - 1);
	return (block->info.difficulty);
}
