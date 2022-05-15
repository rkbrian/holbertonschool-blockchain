#include "../blockchain.h"

/**
 * coinbase_create - create a coinbase transaction
 * @receiver: contains the public key of the miner, who will receive the
 *  coinbase coins
 * @block_index: the index of Block the coinbase transaction will belong to
 * Return: a pointer to the created transaction upon success,
 *  or NULL upon failure
 */
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	;
}
