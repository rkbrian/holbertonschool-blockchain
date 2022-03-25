#include "hblk_crypto.h"

/**
 * ec_verify - verify the signature of a given set of bytes, using a given
 *  EC_KEY public key.
 * @key: points to the EC_KEY structure containing the public key to be used
 *  to verify the signature
 * @msg: points to the msglen characters to verify the signature of
 * @msglen: msg length
 * @sig: points to the signature to be checked
 * Return: 1 if the signature is valid, and 0 otherwise
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
	      sig_t const *sig)
{
	int validity;

	if (!key || !msg || !sig || sig->len == 0)
		return (0);
	validity = ECDSA_verify(0, msg, (int)msglen,
				(unsigned char *)sig->sig, (int)sig->len, (EC_KEY *)key);
	return (validity);
}
