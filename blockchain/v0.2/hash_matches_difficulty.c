#include "blockchain.h"

/**
 * hash_matches_difficulty - check if a given hash matches a given difficulty
 * @hash: the hash to check
 * @difficulty: the minimum difficulty the hash should match
 * Return: 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	uint32_t i, binary_ha, test_diff = 0;

	if (difficulty > SHA256_DIGEST_LENGTH * 8)
		return (0);
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		if (hash[i] == 0)
			test_diff += 8; /* leap of bite size = 8 */
		else
			break;
	}
	if (i == SHA256_DIGEST_LENGTH)
		return (1);
	for (binary_ha = 128; binary_ha > 0; binary_ha = binary_ha >> 1)
	{
		if (binary_ha & hash[i])
			break;
		test_diff++;
	}
	if (test_diff >= difficulty)
		return (1);
	return (0);
}
