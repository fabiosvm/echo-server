
# Echo Server

A simple TCP echo server. The `echo-server` listens on port `9000` and echoes back any data received.
The `client` can be used to test the server.

## Building

```
mkdir build && cd build
cmake ..
cmake --build .
```

## Testing

```
cd build
ctest .
```
