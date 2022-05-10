#include "transaction.h"

/**
 * tx_out_create - allocate and initialize a transaction output structure
 * @amount: the amount of the transaction
 * @pub: the public key of the transaction receiver
 * Return: Pointer to the created transaction output upon success,
 *  or NULL upon failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out;

	out = malloc(sizeof(tx_out_t));
	if (!out)
		return (NULL);
	out->amount = amount;
	memcpy(out->pub, pub, sizeof(out->pub));
	sha256((const int8_t *)out, sizeof(out->amount) + sizeof(out->pub),
	       out->hash);
	return (out);
}
