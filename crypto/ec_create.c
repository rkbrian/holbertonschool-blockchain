#include "hblk_crypto.h"

/**
 * ec_create - function that creates a new EC key pair.
 * NOTE: Both the private and the public keys must be generated. Need to use
 *  the secp256k1 elliptic curve to create the new pair (See EC_CURVE macro)
 * Return: a pointer to an EC_KEY structure, containing both the public and
 *  private keys, or NULL upon failure
 */
EC_KEY *ec_create(void)
{
	EC_KEY *eckey;

	eckey = EC_KEY_new_by_curve_name(EC_CURVE); /* create EC_KEY */
	EC_KEY_generate_key(eckey); /* generate the private and the pub keys */
	return (eckey);
}
