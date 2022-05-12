#include "../blockchain.h"

/**
 * unspent_tx_out_create - allocate and initialize an unspent transaction
 *  output structure
 *
 * @block_hash: the hash of the Block where the referenced transaction output
 *  is located
 * @tx_id: the hash of a transaction in the Block block_hash, where the
 *  referenced transaction output is located
 * @out: points to the referenced transaction output
 * Return: a pointer to the created unspent transaction output upon success,
 *  or NULL upon failure
 */
unspent_tx_out_t *unspent_tx_out_create(uint8_t
					block_hash[SHA256_DIGEST_LENGTH],
					uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
	unspent_tx_out_t *uns_out;

	uns_out = malloc(sizeof(unspent_tx_out_t));
	if (!uns_out)
		return (NULL);
	memcpy(uns_out->block_hash, block_hash, sizeof(uns_out->block_hash));
	memcpy(uns_out->tx_id, tx_id, sizeof(uns_out->tx_id));
	memcpy(&uns_out->out, out, sizeof(uns_out->out));
	return (uns_out);
}
