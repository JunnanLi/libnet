all:
	gcc -o t_nmac nmac.c function.c recvPacket.c sendPacket.c l2_learning.c -lpcap -lnet -lpthread
clean:
	rm t_nmac
