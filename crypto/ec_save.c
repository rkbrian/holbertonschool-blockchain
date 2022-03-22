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
	DIR *dir;
	FILE *fa;
	char *pri_key, *pub_key;

	if (!folder || !key)
		return (0);
	dir = opendir(folder);
	if (errno == ENOENT) /* folder not existed */
		mkdir(folder, 0644), dir = opendir(folder);
	if (dir)
		closedir(dir);
	else
		return (0);
	pri_key = malloc(sizeof(char) * (strlen(folder) + 9)); /* extra bytes */
	if (!pri_key) /* I heard sprintf() is handy but I'm not gonna use it */
		return (0);
	pub_key = malloc(sizeof(char) * (strlen(folder) + 13));
	if (!pub_key)
	{
		free(pri_key);
		return (0);
	}
	strcpy(pri_key, folder), strcpy(pub_key, folder);
	if (folder[strlen(folder) - 1] != '/')
		strcat(pri_key, "/"), strcat(pub_key, "/");
	strcat(pri_key, "key.pem"), strcat(pub_key, "key_pub.pem");
	fa = fopen(pri_key, "w");
	PEM_write_ECPrivateKey(fa, key, NULL, NULL, 0, NULL, NULL), fclose(fa);
	fa = fopen(pub_key, "w"), PEM_write_EC_PUBKEY(fa, key), fclose(fa);
	free(pri_key), free(pub_key);
	return (1);
}
