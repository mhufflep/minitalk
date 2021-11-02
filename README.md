# minitalk

## Description
This project is about communication between two processes: client and server. <br>
Interaction processed by sending two types of signals: SIGUSR1 and SIGUSR2

## Dependencies
 * `gcc`

## Compile
```bash
# This command will сompile the project
make

# This command will re-сompile the project
make re
```

## Run
```bash
# Run the server without any arguments

./server
# It will show his PID
```

```bash
# Run the client specifying server's PID and the message you want to send

# Calling
./client <PID> <Message>

####### Examples

# You can send any ASCII message
./client 32147 "Hello!"
# Or unicode message: 
./client 65374 "Привет!" 
./client 21344 "こんにちは!" 

# Even emoji
./client 32147 "😍"
```

After sending full message to the server, client will print amount of bits that server received.

```bash
./client 32147 "Hello!"
# 56/56 bits sent!

./client 65374 "Привет!"
# 112/112 bits sent!
```


