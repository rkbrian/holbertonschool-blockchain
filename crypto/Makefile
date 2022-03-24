sha256-test: # usage: ./sha256-test string
	gcc -Wall -Wextra -Werror -pedantic -I. -o sha256-test test/sha256-main.c provided/_print_hex_buffer.c sha256.c -lssl -lcrypto
ec_create-test: # usage: valgrind ./ec_create-test
	gcc -Wall -Wextra -Werror -pedantic -I. -o ec_create-test test/ec_create-main.c ec_create.c -lssl -lcrypto
ec_to_pub-test: # usage: valgrind ./ec_to_pub-test
	gcc -Wall -Wextra -Werror -pedantic -I. -o ec_to_pub-test test/ec_to_pub-main.c provided/_print_hex_buffer.c ec_to_pub.c ec_create.c -lssl -lcrypto
ec_from_pub-test: # usage: valgrind ./ec_from_pub-test
	gcc -Wall -Wextra -Werror -pedantic -I. -o ec_from_pub-test test/ec_from_pub-main.c provided/_print_hex_buffer.c ec_from_pub.c ec_to_pub.c ec_create.c -lssl -lcrypto
# usage: - Step A: ./ec_save-test foldername ---- create <folder>/key.pem and <folder>/key_pub.pem.
# - Step B: openssl ec -text -noout -in foldername/key.pem ---- show readable content of key.pem
ec_save-test:
	gcc -Wall -Wextra -Werror -pedantic -I. -o ec_save-test test/ec_save-main.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c -lssl -lcrypto
ec_load-test: # usage: ./ec_load-test foldername
	gcc -Wall -Wextra -Werror -pedantic -I. -o ec_load-test test/ec_load-main.c ec_load.c ec_save.c ec_create.c ec_to_pub.c provided/_print_hex_buffer.c -lssl -lcrypto
