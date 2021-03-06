CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
SRCBC = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_serialize.c blockchain_deserialize.c block_is_valid.c hash_matches_difficulty.c blockchain_difficulty.c block_mine.c
SRCTX = tx_out_create.c unspent_tx_out_create.c tx_in_create.c transaction_hash.c tx_in_sign.c transaction_create.c transaction_is_valid.c coinbase_create.c coinbase_is_valid.c transaction_destroy.c update_unspent.c
SRC = $(SRCBC) $(addprefix transaction/, $(SRCTX))
OBJ = $(SRC:.c=.o)
RM = rm -f

# needs update here
blockchain_create-test: # usage: ./blockchain_create-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c test/blockchain_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_create-test: # usage: ./block_create-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c test/block_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_destroy-test: # usage: valgrind ./block_destroy-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c block_destroy.c test/block_destroy-main.c provided/_blockchain_destroy.c  -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
blockchain_destroy-test: # usage: valgrind ./blockchain_destroy-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_destroy.c blockchain_create.c block_create.c block_destroy.c test/blockchain_destroy-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_hash-test: # usage: ./block_hash-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c transaction/tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/coinbase_create.c transaction/transaction_destroy.c provided/_genesis.c provided/_print_hex_buffer.c provided/_blockchain_print.c provided/_transaction_print.c provided/_transaction_print_brief.c test/block_hash-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
blockchain_serialize-test: # usage: ./blockchain_serialize-test
# hexdump -Cv save.hblk
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_serialize.c provided/_endianness.c test/blockchain_serialize-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
blockchain_deserialize-test: # hexdump -Cv save.hblk
# usage: ./blockchain_deserialize-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_deserialize.c provided/_blockchain_print.c provided/_endianness.c test/blockchain_deserialize-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_is_valid-test: # usage: ./block_is_valid-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c hash_matches_difficulty.c blockchain_difficulty.c block_mine.c transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/transaction_is_valid.c transaction/coinbase_create.c transaction/coinbase_is_valid.c transaction/transaction_destroy.c provided/_genesis.c provided/_print_hex_buffer.c test/block_is_valid-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
hash_matches_difficulty-test: # usage: ./hash_matches_difficulty-test
	$(CC) $(CFLAGS) -I. -I../../crypto -o $@ hash_matches_difficulty.c test/hash_matches_difficulty-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_mine-test: # usage: ./block_mine-test
	$(CC) $(CFLAGS) -I. -I../../crypto -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c hash_matches_difficulty.c block_mine.c provided/_genesis.c provided/_blockchain_print.c test/block_mine-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
blockchain_difficulty-test: # usage: ./blockchain_difficulty-test
	$(CC) $(CFLAGS) -I. -I../../crypto -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_difficulty.c provided/_genesis.c provided/_blockchain_print.c test/blockchain_difficulty-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
# transactions
transaction/tx_out_create-test: # usage: ./transaction/tx_out_create-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c provided/_print_hex_buffer.c transaction/test/tx_out_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/unspent_tx_out_create-test: # usage: ./transaction/unspent_tx_out_create-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/unspent_tx_out_create.c provided/_print_hex_buffer.c transaction/test/unspent_tx_out_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/tx_in_create-test: # usage: ./transaction/tx_in_create-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c provided/_print_hex_buffer.c transaction/test/tx_in_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/transaction_hash-test: # usage: ./transaction/transaction_hash-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c provided/_print_hex_buffer.c transaction/test/transaction_hash-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/tx_in_sign-test: # usage ./transaction/tx_in_sign-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c provided/_print_hex_buffer.c transaction/test/tx_in_sign-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/transaction_create-test: # usage: ./transaction/transaction_create-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c provided/_print_hex_buffer.c provided/_transaction_print.c transaction/test/transaction_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/transaction_is_valid-test: # usage: ./transaction/transaction_is_valid-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_is_valid.c provided/_print_hex_buffer.c transaction/test/transaction_is_valid-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/coinbase_create-test: # usage: ./transaction/coinbase_create-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/transaction_hash.c transaction/coinbase_create.c provided/_print_hex_buffer.c transaction/test/coinbase_create-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/coinbase_is_valid-test: # usage: ./transaction/coinbase_is_valid-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/transaction_hash.c transaction/coinbase_create.c transaction/coinbase_is_valid.c provided/_print_hex_buffer.c transaction/test/coinbase_is_valid-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/transaction_destroy-test: # usage: valgrind ./transaction/transaction_destroy-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ transaction/tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/coinbase_create.c transaction/transaction_destroy.c transaction/test/transaction_destroy-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
transaction/update_unspent-test: # usage: ./transaction/update_unspent-test
	$(CC) $(CFLAGS) -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c hash_matches_difficulty.c blockchain_difficulty.c block_mine.c transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/transaction_is_valid.c transaction/coinbase_create.c transaction/coinbase_is_valid.c transaction/transaction_destroy.c transaction/update_unspent.c provided/_genesis.c provided/_print_hex_buffer.c provided/_blockchain_print.c provided/_transaction_print.c provided/_transaction_print_brief.c transaction/test/update_unspent-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
libhblk_blockchain.a: $(OBJ)
	ar rcs libhblk_blockchain.a $(OBJ)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto
# provided/_genesis.c provided/_print_hex_buffer.c provided/_blockchain_print.c provided/_transaction_print.c provided/_transaction_print_brief.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
oclean:
	$(RM) $(OBJ)
testclean:
	$(RM) *-test
.PHONY: sha256-test ec_create-test ec_to_pub-test ec_from_pub-test ec_save-test ec_load-test ec_sign-test ec_verify-test oclean testclean $(CFLAGS)
