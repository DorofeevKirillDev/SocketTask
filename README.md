# SocketTask
Internship task.
Client side uses multithreading: first thread recieves input and puts it to buffer, second thread sends data from the buffer to server (Producer–consumer problem solved with semaphores). Server side obtains data and processes it.
Interaction between programs organized with sockets from standart library, any problems with connection or with functioning of one of the programs does not affect the other one. Programs will reconnect if any connection problem occurs.
