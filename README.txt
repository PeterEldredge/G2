Group Members: Jacob Dixey, Peter Eldredge
CS283-001
Due Date: 8/25/19

We believe we've completed the assignment as it was asked of us.

We will explain the purpose of each file below:

miniRSA.c : 
    Holds the functions necessary for finding the prime numbers,
    calculating the information needed to make both keys, and 
    encrypting and decrypting the messages

miniRSA.h : 
    Header file for miniRSA.c that allows its usage with all other files
    that compile with it

encryptor.c :
    Takes in a character, E, C, D, and DC in that order. E and C are for your public key, and D and DC for your private key
    Test file for encrypting and decrypting a single character. Not used within the chat program flow.

genkey.c : 
    Takes in two integers that tell the program the number of prime they'd like used to calculate their keys.
    Then calculates all the necessary variables using functions from miniRSA.c until finally printing the users randomized keys.

keycracker.c : 
    Takes in public key (e) and N.
    Prints private key by finding p and q from N and looping through different values of K to find d.

G2Server.c : 
    Takes in the port number, E, C, D, and DC where E and C make up your partner's public key, and D and DC make up your private key.
    Sets the server up to run infinitely and only allows message responses once it itself has been sent a message.
    Decrypts sender's messages and encrypts its own messages messages
    Compiled with miniRSA.c

G2Client.c :
    Takes in the host/server, port number, E, C, D, and DC where E and C make up your partner's public key, and D and DC make up your private key.
    Connects to the server at the specified host and port and allows the user to send a message and subsequently receive one back from server.
    Decrypts sender's messages and encrypts its own messages messages.
    Compiled with miniRSA.c
  
