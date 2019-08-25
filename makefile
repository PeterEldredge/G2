#### C ####

.PHONY: build view clean

build : build1 build2 build3 build4 build5

build1: G2Client.c
		gcc G2Client.c -o Client.exe

build2: G2Server.c
		gcc G2Server.c -o Server.exe

build3: miniRSA.c
		gcc miniRSA.c genkey.c -lm -o genkey.exe

build4: encryptor.c	
		gcc miniRSA.c encryptor.c -lm -o encryptor.exe

build5: keycracker.c
		gcc miniRSA.c keycracker.c -lm -o keycracker.exe

genkey : 
		./genkey.exe "${MPRIME}" "${NPRIME}"

clean:
		-\rm Client.exe
		-\rm Server.exe
		-\rm genkey.exe
		-\rm encryptor.exe