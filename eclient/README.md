### Compile 

1. Create 'build' folder and make it your root
``` mkdir build && cd build ```

2. Generate files and build the project.
``` cmake .. && cd build ```

### Start client - Server must be running on the PORT specified (see ../eserver)

``` ./echoTCP <HOST> <PORT> ``` 

Example: ``` ./echoTCP 0.0.0.0 5005```   



