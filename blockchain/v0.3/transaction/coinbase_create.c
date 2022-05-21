#include "../blockchain.h"

/**
 * coinbase_create - create a coinbase transaction
 * @receiver: contains the public key of the miner, who will receive the
 *  coinbase coins
 * @block_index: the index of Block the coinbase transaction will belong to
 * Return: a pointer to the created transaction upon success,
 *  or NULL upon failure
 * Notes: The resulting transaction must contain a single transaction input
 *  and a single transaction output.
 *  The transaction input should be zeroed, and not signed. To ensure this
 *  transaction input is unique, the block index will be copied in the first
 *  4 bytes of the input's tx_out_hash.
 *  The amount in the transaction output should be exactly COINBASE_AMOUNT.
 */
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	transaction_t *cb;
	tx_in_t *tx_in;
	tx_out_t *tx_out;
	uint8_t pub_key[EC_PUB_LEN];

	if ((receiver == NULL) || ec_to_pub(receiver, pub_key) == NULL)
		return (NULL);
	cb = malloc(sizeof(transaction_t));
	if (cb == NULL)
		return (NULL);
	tx_in = malloc(sizeof(tx_in_t));
	if (tx_in == NULL)
	{
		free(cb);
		return (NULL);
	}
	tx_out = tx_out_create(COINBASE_AMOUNT, pub_key);
	if (tx_out == NULL)
	{
		free(tx_in), free(cb);
		return (NULL);
	}
	memset(tx_in, 0, sizeof(tx_in_t)); /* removing all wild data */
	memcpy(tx_in->tx_out_hash, &block_index, 4);
	cb->inputs = llist_create(MT_SUPPORT_FALSE);
	cb->outputs = llist_create(MT_SUPPORT_FALSE);
	llist_add_node(cb->inputs, tx_in, ADD_NODE_REAR);
	llist_add_node(cb->outputs, tx_out, ADD_NODE_REAR);
	if (transaction_hash(cb, cb->id) == NULL)
	{
		llist_destroy(cb->inputs, 0, NULL), free(tx_in);
		llist_destroy(cb->outputs, 0, NULL), free(tx_out), free(cb);
		return (NULL);
	}
	return (cb);
}
