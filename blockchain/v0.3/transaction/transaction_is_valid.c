#include "blockchain.h"

/**
 * transaction_is_valid - function that checks whether a transaction is valid
 * @transaction: points to the transaction to verify
 * @all_unspent: the list of all unspent transaction outputs to date
 * Return: 1 if the transaction is valid, and 0 otherwise
 * Notes: The transaction must verify the following:
 *  - The computed hash of the transaction must match the hash stored in it
 *  - Each input in the transaction must refer to an unspent output in
 *    all_unspent
 *  - Each s signature must be verified using the public key stored in the
 *    referenced unspent output
 *  - The total amount of inputs must match the total amount of outputs
 */
int transaction_is_valid(transaction_t const *transaction,
			 llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	uint32_t sum_in = 0, sum_out = 0;
	int i, j, size_usp;
	tx_in_t *tx_in;
	unspent_tx_out_t *uns_out;
	EC_KEY *uns_pub_key;

	if ((transaction == NULL) || (all_unspent == NULL))
		return (0);
	transaction_hash(transaction, hash_buf); /* hash match check */
	if (memcmp(hash_buf, transaction->id, SHA256_DIGEST_LENGTH) != 0)
		return (0);
	size_usp = llist_size(all_unspent); /* input and unspent output check */
	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		tx_in = llist_get_node_at(transaction->inputs, i);
		for (j = 0; j < size_usp; j++)
		{
			uns_out = llist_get_node_at(all_unspent, j);
			if (memcmp(uns_out->out.hash, tx_in->tx_out_hash, SHA256_DIGEST_LENGTH) == 0
			    && memcmp(uns_out->tx_id, tx_in->tx_id, SHA256_DIGEST_LENGTH) == 0 &&
			    memcmp(uns_out->block_hash, tx_in->block_hash, SHA256_DIGEST_LENGTH)
			    == 0)
				break;
		}
		if (j == size_usp)
			return (0);
		uns_pub_key = ec_from_pub(uns_out->out.pub); /* sig verify */
		j = ec_verify(uns_pub_key, transaction->id,
			      SHA256_DIGEST_LENGTH, &tx_in->sig);
		EC_KEY_free(uns_pub_key);
		if (j == 0)
			return (0);
		sum_in += uns_out->out.amount; /* collectiong total amount of inputs */
	}
	for (i = 0; i < llist_size(transaction->outputs); i++)
		sum_out += ((tx_out_t *)llist_get_node_at(transaction->outputs, i))->amount;
	if (sum_in != sum_out) /* total amount of inputs and that of outputs */
		return (0);
	return (1);
}
