#include "hblk_crypto.h"

/**
 * sha256 - function that computes the hash of a sequence of bytes
 *
 */
uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!digest)
		return (NULL);
	return (SHA256((unsigned char *)s, len, digest));
}
