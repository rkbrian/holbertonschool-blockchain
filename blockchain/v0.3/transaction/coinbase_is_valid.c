#include "blockchain.h"

/**
 * coinbase_is_valid - check whether a coinbase transaction is valid
 * @coinbase: points to the coinbase transaction to verify
 * @block_index: the index of Block the coinbase transaction will belong to
 * Return: 1 if the coinbase transaction is valid, and 0 otherwise
 * Notes: The coinbase transaction must verify the following:
 *  The computed hash of the transaction must match the hash stored in it
 *  The transaction must contain exactly 1 input.
 *  The transaction must contain exactly 1 output.
 *  The transaction input's tx_out_hash first 4 bytes must match block_index.
 *  The transaction input's block_hash, tx_id, and signature must be zeroed.
 *  The transaction output amount must be exactly COINBASE_AMOUNT.
 */
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	tx_in_t *tx_in;
	tx_out_t *tx_out;

	if ((coinbase == NULL))
		return (0);
	transaction_hash(coinbase, hash_buf); /* hash match check */
	if (memcmp(hash_buf, coinbase->id, SHA256_DIGEST_LENGTH) != 0)
		return (0);
	if (llist_size(coinbase->inputs) != 1 ||
	    llist_size(coinbase->outputs) != 1)
		return (0); /* only 1 input & 1 output check */
	tx_in = llist_get_node_at(coinbase->inputs, 0);
	tx_out = llist_get_node_at(coinbase->outputs, 0);
	if (memcmp(&block_index, tx_in->tx_out_hash, 4) != 0)
		return (0); /* tx_out_hash first 4 bytes check */
	 /* zeroed contents check */
	if (memcmp(zero_hash, tx_in->block_hash, SHA256_DIGEST_LENGTH) != 0
	    || memcmp(zero_id, tx_in->tx_id, SHA256_DIGEST_LENGTH) != 0 ||
	    memcmp(&zero_sig, &tx_in->sig, sizeof(tx_in->sig)) != 0)
	{
		/*free(empty_in);*/
		return (0);
	}
	/*empty_in = malloc(sizeof(tx_in_t));
	free(empty_in);*/
	if (tx_out->amount != COINBASE_AMOUNT) /* output amount check */
		return (0);
	return (1);
}
