#include "../blockchain.h"

/**
 * tx_in_create - allocate and initialize a transaction input structure
 *
 * @unspent: points to the unspent transaction output to be converted to
 *  a transaction input
 * Return: a pointer to the created transaction input upon success,
 *  or NULL upon failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *in;

	if (!unspent)
		return (NULL);
	in = malloc(sizeof(tx_in_t));
	if (!in)
		return (NULL);
	memcpy(in->block_hash, unspent->block_hash, sizeof(in->block_hash));
	memcpy(in->tx_id, unspent->tx_id, sizeof(in->tx_id));
	memcpy(in->tx_out_hash, unspent->out.hash, sizeof(in->tx_out_hash));
	memset(&in->sig.sig, 0, sizeof(in->sig.sig));
	in->sig.len = 0;
	return (in);
}
