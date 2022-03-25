/* Description: Generates 10 signatures of the same string */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hblk_crypto.h"
EC_KEY *_ec_create(void);
int _ec_verify(EC_KEY const *key, uint8_t const *msg,
	       size_t msglen, sig_t const *sig);
static void _print_hex_buffer(uint8_t const *buf, size_t len)
{
	size_t i;
	for (i = 0; buf && i < len; i++)
		printf("%02x", buf[i]);
}
uint8_t *alex_ec_sign(EC_KEY const *key, uint8_t const *msg,
		      size_t msglen, sig_t *sig)
{
	uint32_t _len = 0;
	if (!key || !msg || !msglen)
		return (NULL);
	bzero(sig->sig, sizeof(sig->sig));
	if (!ECDSA_sign(0, msg, msglen, sig->sig, &_len, (EC_KEY *)key))
	{
		sig->len = 0;
		return (NULL);
	}
	sig->len = (uint8_t)_len;
	return ((uint8_t *)sig->sig);
}
static int test_ec_sign(EC_KEY const *key)
{
	unsigned char const str[] = "Holberton School";
	sig_t sig;
	sig_t sig_alex;
	if (!ec_sign(key, str, strlen((char *)str), &sig))
	{
		printf("ec_sign() failed\n");
		return (EXIT_FAILURE);
	}
	if (!alex_ec_sign(key, str, strlen((char *)str), &sig_alex))
	{
		printf("alex_ec_sign() failed\n");
		return (EXIT_FAILURE);
	}
	_print_hex_buffer(sig.sig, SIG_MAX_LEN);
	printf("\n");
	_print_hex_buffer(sig_alex.sig, SIG_MAX_LEN);
	printf("\n");
	if (!_ec_verify(key, str, strlen((char *)str), &sig))
	{
		printf("Signature verification failed\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	EC_KEY *key;
	int i;
	/* Prerequisites */
	key = _ec_create();
	if (!key)
	{
		printf("ec_create() failed\n");
		return (EXIT_FAILURE);
	}
	/* Test `ec_sign()` */
	for (i = 0; i < 10; i++)
	{
		if (test_ec_sign(key) != EXIT_SUCCESS)
		{
			EC_KEY_free(key);
			return (EXIT_FAILURE);
		}
	}
	/* Cleanup */
	EC_KEY_free(key);
	return (EXIT_SUCCESS);
}
