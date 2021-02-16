### Compile server

``` gcc -Wall -o ServerTCP ServerTCP.c HandleTCP.c ../Error.c```

### Start server 


``` ./ServerTCP <PORT> & ``` 

Example: ``` ./ServerTCP 5005 &```   


### End server  

Check process ID   ```ps``` 

Kill process   ```kill <PROCESS ID>```

