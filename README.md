openstack-cli-ser
=================

A simple client server based program to connect to your openstack based vm instance written in C.
*****************************************
Run sample client-server application with the cloud instance
-
-
-
Copy sample server code from ser.c to some file ‘server.c’
Compile that file on your local machine (not on cloud instance)
Copy server binary to cloud instance :

$ gcc server.c –o server
$ scp server ubuntu@10.0.0.2:~/
Copy sample client code from cli to some file ‘client.c’
Compile that file on your local machine (not on cloud instance)
Run that client binary
$ gcc client.c –o client
$ ./client 10.0.0.2 1234
