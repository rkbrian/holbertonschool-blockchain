#include "blockchain.h"

/**
 * blockchain_deserialize - deserialize a Blockchain from a file
 * @path: the path to a file to load the Blockchain from
 * Return: a pointer to the deserialized Blockchain upon success,
 *  or NULL upon failure involving:
 *  - Unable to open/read file,
 *  - Incorrect magic number
 *  - Version mismatch
 * Note: fread may not successfully read, init blocks_count = 0 is safer
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fp = NULL;
	blockchain_t *bc;
	block_t *block;
	char magicnum[5], version[4]; /* strlen(string) = sizeof(string) - 1 */
	int i = 0;
	int blocks_count = 0, uns_count = 0;
	uint8_t endi;

	if (!path)
		return (NULL);
	fp = fopen(path, "rb");
	if (!fp)
		return (NULL);
	fseek(fp, 0, SEEK_SET), fread(magicnum, strlen(HBLK_MAGIC), 1, fp);
	magicnum[strlen(HBLK_MAGIC)] = 0, fread(version, strlen(HBLK_VERSION), 1, fp);
	version[strlen(HBLK_VERSION)] = 0, bc = malloc(sizeof(blockchain_t));
	if (strcmp(magicnum, HBLK_MAGIC) != 0 || strcmp(version, HBLK_VERSION) != 0 ||
	    !bc)
	{
		fclose(fp);
		return (NULL);
	}
	bc->chain = llist_create(MT_SUPPORT_FALSE);
	bc->unspent = llist_create(MT_SUPPORT_FALSE);
	fread(&endi, sizeof(uint8_t), 1, fp);
	fread(&blocks_count, sizeof(int), 1, fp);
	fread(&uns_count, sizeof(int), 1, fp);
	while (i < blocks_count)
	{
		block = malloc(sizeof(block_t));
		if (!block)
		{
			llist_destroy(bc->chain, i, NULL), fclose(fp);
			return (NULL);
		}
		block_sweep(block, endi, fp);
		llist_add_node(bc->chain, block, ADD_NODE_REAR), i++;
	}
	read_uns(uns_count, fp, bc, endi), fclose(fp);
	return (bc);
}

/**
 * read_uns - read the list of unspent outputs from file fp.
 * @uns_count: size of the unspent outputs list
 * @fp: file pointer
 * @bc: the blockchain
 * @endianness: endianness
 */
void read_uns(int uns_count, FILE *fp, blockchain_t *bc, int endianness)
{
	int j;
	unspent_tx_out_t *uns;

	for (j = 0; j < uns_count; j++)
	{
		uns = malloc(sizeof(unspent_tx_out_t));
		fread(uns, 165, 1, fp);
		if (endianness == 2)
		{
			_swap_endian(&uns->block_hash, 32);
			_swap_endian(&uns->tx_id, 32);
			_swap_endian(&uns->out.amount, 4);
			_swap_endian(&uns->out.pub, 65);
			_swap_endian(&uns->out.hash, 32);
		}
		llist_add_node(bc->unspent, uns, ADD_NODE_REAR);
	}
}

/**
 * block_sweep - function to swap bytes for proper endianness
 * @block: block
 * @endianness: endianness
 * @fp: file pointer
 */
void block_sweep(block_t *block, int endianness, FILE *fp)
{
	int nb_tx;

	fread(&block->info.index, sizeof(block->info.index), 1, fp);
	fread(&block->info.difficulty, sizeof(block->info.difficulty), 1, fp);
	fread(&block->info.timestamp, sizeof(block->info.timestamp), 1, fp);
	fread(&block->info.nonce, sizeof(block->info.nonce), 1, fp);
	fread(block->info.prev_hash, sizeof(block->info.prev_hash), 1, fp);
	fread(&block->data.len, sizeof(block->data.len), 1, fp);
	memset(block->data.buffer, 0, sizeof(block->data.buffer));
	fread(block->data.buffer, block->data.len, 1, fp);
	fread(block->hash, sizeof(block->hash), 1, fp);
	if (endianness == 2) /* big endianness */
	{
		_swap_endian(&block->info.index, sizeof(block->info.index));
		_swap_endian(&block->info.difficulty, sizeof(block->info.difficulty));
		_swap_endian(&block->info.timestamp, sizeof(block->info.timestamp));
		_swap_endian(&block->info.nonce, sizeof(block->info.nonce));
		_swap_endian(block->info.prev_hash, sizeof(block->info.prev_hash));
		_swap_endian(&block->data.len, sizeof(block->data.len));
		_swap_endian(block->data.buffer, block->data.len);
		_swap_endian(block->hash, sizeof(block->hash));
	}
	fread(&nb_tx, sizeof(nb_tx), 1, fp);
	if (endianness == 2) /* big endianness */
		_swap_endian(&nb_tx, sizeof(nb_tx));
	if (nb_tx == 1) /* coinbase */
		block->transactions = NULL;
	else
		read_tx(block, endianness, fp, nb_tx);
}

/**
 * read_tx - function to read the transaction list
 * @block: block
 * @endianness: endianness
 * @fp: file pointer
 * @nb_tx: number of transactions
 */
void read_tx(block_t *block, int endianness, FILE *fp, int nb_tx)
{
	transaction_t *tx;
	tx_in_t *tx_in;
	tx_out_t *tx_out;
	int i, j, nb_inputs, nb_outputs;

	block->transactions = llist_create(MT_SUPPORT_FALSE);
	for (i = 0; i < nb_tx; i++)
	{
		tx = malloc(sizeof(transaction_t)), fread(&tx->id, 32, 1, fp);
		fread(&nb_inputs, sizeof(nb_inputs), 1, fp);
		fread(&nb_outputs, sizeof(nb_outputs), 1, fp);
		if (endianness == 2) /* big endianness */
		{
			_swap_endian(&tx->id, 32), _swap_endian(&nb_inputs, sizeof(nb_inputs));
			_swap_endian(&nb_outputs, sizeof(nb_outputs));
		}
		for (j = 0; j < nb_inputs; j++)
		{
			tx_in = malloc(sizeof(tx_in_t)), fread(tx_in, 169, 1, fp);
			if (endianness == 2) /* big endianness */
				swap_tx_in(tx_in);
			llist_add_node(tx->inputs, tx_in, ADD_NODE_REAR);
		}
		for (j = 0; j < nb_outputs; i++)
		{
			tx_out = malloc(sizeof(tx_out_t)), fread(tx_out, 101, 1, fp);
			if (endianness == 2) /* big endianness */
			{
				_swap_endian(&tx_out->amount, sizeof(tx_out->amount));
				_swap_endian(&tx_out->pub, 65);
				_swap_endian(&tx_out->hash, 32);
			}
			llist_add_node(tx->outputs, tx_out, ADD_NODE_REAR);
		}
	}
}

/**
 * swap_tx_in - function to swap the part that betty hates
 * @tx_in: transaction input
 */
void swap_tx_in(tx_in_t *tx_in)
{
	_swap_endian(&tx_in->block_hash, sizeof(tx_in->block_hash));
	_swap_endian(&tx_in->tx_id, sizeof(tx_in->tx_id));
	_swap_endian(&tx_in->tx_out_hash, sizeof(tx_in->tx_out_hash));
	_swap_endian(&tx_in->sig.sig, sizeof(tx_in->sig.sig));
	_swap_endian(&tx_in->sig.len, sizeof(tx_in->sig.len));
}
