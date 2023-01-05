# ex3
ex3 advanced programming 2023
How to run?
1. Download the files.
2. Open 2 terminal wimdows.
3. In one terminal run the command make
4. Run the command ./server.out file port
5. In the other terminal run the command ./client.out ip port
6. Write a vector of double numbers seperated by space as an input for classificetion, type of distance function and number k and press enter.
7. You can repeat line 6 to classify more vectors in the same client, or repeat line 5 to classify from new client.
7. To close client enter -1.
8. To close the server stop the program from running by pressing ctrl+c.

How the program work?
When the command ./server.out file port run, the program create server with the parameter port, which is the number of the port where the server listens, and csv file with classified vectors.
The server turn the file to vector of vectors of doubles with the classificetion represented as numbers. The program checks if all the vectors ate valid, and create KNN object with the vectors as constructor parameters. 
The program open listening socket in the port.
When the command ./client.out ip port run the program create client where the ip and port parameters are the ip and port numbers of the listening server.
The client get from the user vector of doubles, type of distance and number k. If all the parameters are valid the client send the parameters to the server. The server send the parameters to KNN class who return the classification. The server send the classification to the client that prints the result to the user.

