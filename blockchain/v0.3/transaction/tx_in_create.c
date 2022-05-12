#include "../blockchain.h"

/**
 * tx_in_create - allocate and initialize a transaction input structure
 * @unspent: points to the unspent transaction output to be converted to
 *  a transaction input
 * Return: a pointer to the created transaction input upon success,
 *  or NULL upon failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *in;

	in = malloc(sizeof(tx_in_t));
	if (!in)
		return (NULL);
	in->;
	in->block_hash;


	return ();
}
