### Compile

1. Create 'build' folder and make it your root
``` mkdir build && cd build ```

2. Generate files and build the project.
``` cmake .. && make ```

### Start server 

Usage:  
``` ./ServerTCP <PORT> & ``` 

Example:  
``` ./ServerTCP 5005 &```   

### End server (ubuntu)

Check process ID   ```ps``` 

Kill process   ```kill <PROCESS ID>```

