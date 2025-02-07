mysh: mysh.c
	gcc -g3 -O0 -o mysh mysh.c
myls: myls.c
	gcc -g3 -O0 -o myls myls.c
inode: inode.c
	gcc -g3 -O0 -o inode inode.c

check: mysh myls inode
	echo "Trying:  ./mysh"
	echo 'ls -l' | ./mysh
	@ echo ""
	@ # NOTE: '2>&1' means redirect stderr (fd 2) to stdout (fd 1)
	echo "Testing extended./mysh test"
	cat mysh.in | ./mysh 2<&1 | diff --ignore-all-space - mysh.out
	@ echo "If no output above, then extended test of ./mysh test succeeded"
	@ echo ""
	echo "Trying:  ./myls /usr/bin/ls"
	echo "Trying:  ./myls /usr/bin"
	./myls /usr/bin/ls
	@echo ""
	@ echo "Comparing xv6-sh.c and mysh.c"
	diff xv6-sh.c mysh.c | grep '^>' | wc -l
	@ echo "Comparing ls.c and myls.c"
	diff xv6-ls.c myls.c | grep '^>' | wc -l
	@echo ""
	@ echo "Print the inode of /usr/bin/ls."
	./inode /usr/bin/ls

clean:
	rm -f mysh myls