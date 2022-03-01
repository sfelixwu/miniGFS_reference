
#
# Makefile for miniGFS, ecs251 and ecs36b
#

CC = g++ -std=c++17

# CFLAGS = -g

# for most Linux environments, but might need to be changed to find json stuff
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# the following, RPCG, are JSONRPC generated files
RPCG_INCS =	minigfs_client.h minigfs_server.h

# all files inherited from Core objects plus the RPCG stuff
CORE_INCS =	Core.h Directory.h Shadow_Directory.h Replica.h Shadow_Replica.h $(RPCG_INCS)
CORE_OBJS =	Core.o Directory.o Shadow_Directory.o Replica.o Shadow_Replica.o

# libraries needed for JSON and JSONRPC
LDFLAGS_SV = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server
LDFLAGS_CL = 	-ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client

# executable
EXE_FILES =	minigfs_client minigfs_master minigfs_primary minigfs_secondary_A minigfs_secondary_B

# rules

all: 	minigfs_client minigfs_master minigfs_primary minigfs_secondary_A minigfs_secondary_B

# why do I need this line?

minigfs_client.h:	minigfs.json
	jsonrpcstub minigfs.json --cpp-server=minigfs_Server --cpp-client=minigfs_Client

minigfs_server.h:	minigfs.json
	jsonrpcstub minigfs.json --cpp-server=minigfs_Server --cpp-client=minigfs_Client

base64.o:		base64.cpp base64.h
	$(CC) -c $(CFLAGS) base64.cpp

Core.o:			Core.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Core.cpp

Directory.o:		Directory.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Directory.cpp

Shadow_Directory.o:	Shadow_Directory.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Directory.cpp

Replica.o:		Replica.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Replica.cpp

Shadow_Replica.o:	Shadow_Replica.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Replica.cpp

minigfs_client.o:	minigfs_client.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) minigfs_client.cpp

minigfs_master.o:	minigfs_master.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) minigfs_master.cpp

minigfs_primary.o:	minigfs_primary.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) minigfs_primary.cpp

minigfs_secondary_A.o:	minigfs_secondary_A.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) minigfs_secondary_A.cpp

minigfs_secondary_B.o:	minigfs_secondary_B.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) minigfs_secondary_B.cpp

minigfs_client:		$(CORE_OBJS) minigfs_client.o base64.o
	$(CC) -o minigfs_client $(CORE_OBJS) minigfs_client.o base64.o $(LDFLAGS_SV) $(LDFLAGS_CL)

minigfs_master:		$(CORE_OBJS) minigfs_master.o base64.o
	$(CC) -o minigfs_master $(CORE_OBJS) minigfs_master.o base64.o $(LDFLAGS_SV) $(LDFLAGS_CL)

minigfs_primary:	$(CORE_OBJS) minigfs_primary.o base64.o
	$(CC) -o minigfs_primary $(CORE_OBJS) minigfs_primary.o base64.o $(LDFLAGS_SV) $(LDFLAGS_CL)

minigfs_secondary_A:	$(CORE_OBJS) minigfs_secondary_A.o base64.o
	$(CC) -o minigfs_secondary_A $(CORE_OBJS) minigfs_secondary_A.o base64.o $(LDFLAGS_SV) $(LDFLAGS_CL)

minigfs_secondary_B:	$(CORE_OBJS) minigfs_secondary_B.o base64.o
	$(CC) -o minigfs_secondary_B $(CORE_OBJS) minigfs_secondary_B.o base64.o $(LDFLAGS_SV) $(LDFLAGS_CL)

clean:
	rm -f *.o *~ core $(EXE_FILES) $(RPCG_INCS)

# end of the Makefile