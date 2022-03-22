#include "hblk_crypto.h"

/**
 * ec_to_pub - extract the public key from an EC_KEY opaque structure
 * @key: a pointer to the EC_KEY structure to retrieve the public key from.
 *  If it is NULL, your function must do nothing and fail
 * @pub: the address at which to store the extracted public key
 *  (The key shall not be compressed)
 * NOTE: It is also possible to extract the private key from an EC_KEY
 *  structure, but we’re never going to store one’s private key anywhere
 *  in the Blockchain. So we don’t really need it.
 * Return: a pointer to pub, or NULL upon failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_GROUP *ecgroup;
	const EC_POINT *ecpoint;

	if (!key)
		return (NULL);
	ecgroup = EC_KEY_get0_group(key);
	ecpoint = EC_KEY_get0_public_key(key);
	EC_POINT_point2oct(ecgroup, ecpoint, POINT_CONVERSION_UNCOMPRESSED,
			   pub, EC_PUB_LEN, NULL);
	return (pub);
}
