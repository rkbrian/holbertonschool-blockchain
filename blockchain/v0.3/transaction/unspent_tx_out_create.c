#include "transaction.h"

/**
 * tx_out_create - allocate and initialize a transaction output structure
 * @block_hash: the hash of the Block where the referenced transaction output
 *  is located
 * @tx_id: the hash of a transaction in the Block block_hash, where the
 *  referenced transaction output is located
 * @out: points to the referenced transaction output
 * Return: a pointer to the created unspent transaction output upon success,
 *  or NULL upon failure
 */
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],uint8_t tx_id[SHA256_DIGEST_LENGTH],
	tx_out_t const *out)
{
	;
}
