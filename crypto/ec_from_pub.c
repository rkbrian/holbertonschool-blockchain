#include "hblk_crypto.h"

/**
 * ec_from_pub - create an EC_KEY structure given a public key.
 *  The created EC_KEY's private key does not have to be initialized/set,
 *  we only care about the public one
 * @pub: the public key to be converted
 * Return: a pointer to the created EC_KEY structure upon success,
 *  or NULL upon failure
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *eckey;
	const EC_GROUP *ecgroup;
	EC_POINT *ecpoint; /* not const in EC_POINT_oct2point() */

	if (!pub)
		return (NULL);
	eckey = EC_KEY_new_by_curve_name(EC_CURVE);
	ecgroup = EC_KEY_get0_group(eckey);
	/* eckey is not const, use ecgroup to make new point */
	ecpoint = EC_POINT_new(ecgroup);
	/* BN_CTX *ctx is optional, so make it NULL */
	EC_POINT_oct2point(ecgroup, ecpoint, pub, EC_PUB_LEN, NULL);
	EC_KEY_set_public_key(eckey, ecpoint);
	EC_POINT_free(ecpoint);
	return (eckey);
}
