#include "hblk_crypto.h"

/**
 * ec_save - save an existing EC key pair on the disk.
 * @key: points to the EC key pair to be saved on disk
 * @folder: is the path to the folder in which to save the keys
 *  (e.g. /home/hblk/alex). Must be created if it doesn't already exist.
 * Return: 1 or 0 upon success or failure.
 */
int ec_save(EC_KEY *key, char const *folder)
{
	;
}
