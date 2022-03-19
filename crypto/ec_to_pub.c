#include "hblk_crypto.h"

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	EC_GROUP *ecgroup;
	EC_POINT *ecpoint;

	if (!key)
		return (NULL);
	ecgroup = EC_KEY_get0_group(key);
	ecpoint = EC_KEY_get0_public_key(key);
	EC_POINT_point2oct(ecgroup, ecpoint, POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, NULL);
	return (pub);
}
