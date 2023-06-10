#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Ѕиблиотека дл€ работы с сокетами
#include <arpa/inet.h>
using namespace std;


// ћаксимальный размер буфера дл€ приема и передачи
#define MESSAGE_BUFFER 4096
#define PORT 7777 // номер порта, который будем использовать дл€ приема и передачи 


char buffer[MESSAGE_BUFFER];
char message[MESSAGE_BUFFER];
int socket_descriptor;
struct sockaddr_in serveraddress;

void sendRequest() {
    // ”кажем адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // «ададим номер порта дл€ соединени€ с сервером
    serveraddress.sin_port = htons(PORT);
    // »спользуем IPv4
    serveraddress.sin_family = AF_INET;
    // —оздадим сокет 
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    // ”становим соединение с сервером
    if (connect(socket_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) < 0) {
        cout << endl << " Something went wrong Connection Failed" << endl;
        exit(1);
    }

    while (1) {
        cout << "Enter a message you want to send to the server: " << endl;
        cin >> message;
        if (strcmp(message, "end") == 0) {
            sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
            cout << "Client work is done.!" << endl;
            close(socket_descriptor);
            exit(0);
        }
        else {
            sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
            cout << "Message sent successfully to the server: " << message << endl;
            cout << "Waiting for the Response from Server..." << endl;
        }
        cout << "Message Received From Server: " << endl;
        recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
        cout << buffer << endl;
    }
    // закрываем сокет, завершаем соединение
    close(socket_descriptor);
}

int main() {
    cout << "CLIENT IS ESTABLISHING A CONNECTION WITH SERVER THROUGH PORT: " << PORT << endl;
    sendRequest();
    return 0;
}