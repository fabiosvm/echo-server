
# Echo Server

A simple, and cross-platform TCP echo server. The `echo-server` listens on port `9000` (default) and echoes back any data received.
The `echo-client` can be used to test the server.

## Building

```
mkdir build && cd build
cmake ..
cmake --build .
```

## Running the server

```
./echo-server 9090
```

## Running the client

```
./echo-client 127.0.0.1 9090 "Hello!"
```
