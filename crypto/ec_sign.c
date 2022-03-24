#include "hblk_crypto.h"

/**
 * ec_sign - sign a given set of bytes, using a given EC_KEY private key
 * @key: points to the EC_KEY structure containing the private key to be used
 *  to perform the signature
 * @msg: points to the msglen characters to be signed
 * @msglen: msg length
 * @sig: holds the address at which to store the signature
 * Return: a pointer to the signature buffer upon success (sig->sig).
 *  If either key or msg is NULL, function fails and return NULL
 * Notes: sig->sig does not need to be zero-terminated. If it is, sig->len
 *  should hold the size of the signature without the trailing zero byte
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen,
		 sig_t *sig)
{
	;
}
