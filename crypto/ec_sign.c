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
	uint8_t *sig_buffer = NULL;
	EC_KEY *keycopy;

	if (!key || !msg)
		return (NULL);
	keycopy = EC_KEY_dup(key); /* ECDSA_sign uses non-const key */
	if (!keycopy)
		return (NULL);
	/* Computes ECDSA signature of a given hash value using the supplied */
	/*   private key (note: sig must point to ECDSA_size(eckey) bytes */
	/*   of memory). */
	if (!ECDSA_sign(0, msg, msglen, sig->sig, (unsigned int *)&sig->len, keycopy))
	{
		EC_KEY_free(keycopy);
		return (NULL);
	}
	if (sig->sig)
		sig_buffer = sig->sig;
	EC_KEY_free(keycopy);
	return (sig_buffer);
}
