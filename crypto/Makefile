CC = gcc
SRC = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c ec_save.c ec_load.c ec_sign.c ec_verify.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pedantic
RM = rm -f

sha256-test: # usage: ./sha256-test string
	$(CC) $(CFLAGS) -I. -o sha256-test test/sha256-main.c provided/_print_hex_buffer.c sha256.c -lssl -lcrypto
ec_create-test: # usage: valgrind ./ec_create-test
	$(CC) $(CFLAGS) -I. -o ec_create-test test/ec_create-main.c ec_create.c -lssl -lcrypto
ec_to_pub-test: # usage: valgrind ./ec_to_pub-test
	$(CC) $(CFLAGS) -I. -o ec_to_pub-test test/ec_to_pub-main.c provided/_print_hex_buffer.c ec_to_pub.c ec_create.c -lssl -lcrypto
ec_from_pub-test: # usage: valgrind ./ec_from_pub-test
	$(CC) $(CFLAGS) -I. -o ec_from_pub-test test/ec_from_pub-main.c provided/_print_hex_buffer.c ec_from_pub.c ec_to_pub.c ec_create.c -lssl -lcrypto
# usage: - Step A: ./ec_save-test foldername ---- create <folder>/key.pem and <folder>/key_pub.pem.
# - Step B: openssl ec -text -noout -in foldername/key.pem ---- show readable content of key.pem
ec_save-test:
	$(CC) $(CFLAGS) -I. -o ec_save-test test/ec_save-main.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c -lssl -lcrypto
ec_load-test: # usage: ./ec_load-test foldername
	$(CC) $(CFLAGS) -I. -o ec_load-test test/ec_load-main.c ec_load.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c -lssl -lcrypto
ec_sign-test: # usage: ./ec_sign-test
	$(CC) $(CFLAGS) -I. -o ec_sign-test test/ec_sign-main.c provided/_print_hex_buffer.c ec_sign.c ec_create.c -lssl -lcrypto
ec_verify-test: # usage: ./ec_verify-test
	$(CC) $(CFLAGS) -I. -o ec_verify-test test/ec_verify-main.c provided/_print_hex_buffer.c ec_verify.c ec_sign.c ec_create.c -lssl -lcrypto
$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
libhblk_crypto.a: $(OBJ)
	ar rc $@ $(OBJ)
oclean:
	$(RM) $(OBJ)
testclean:
	$(RM) *-test
.PHONY: sha256-test ec_create-test ec_to_pub-test ec_from_pub-test ec_save-test ec_load-test ec_sign-test ec_verify-test oclean testclean $(CFLAGS)
