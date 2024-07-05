Este TP utiliza los sockets desarrollados por eldipa aquí: https://github.com/eldipa/sockets-en-cpp, bajo licencia GPL v2.

# Sockets


![image](https://github.com/Taller-de-Programacion-TPs/sockets-2024c1-ttomasbenitez/assets/88062805/8952dbd5-e4fb-432e-8d12-f3f0c3d3315a)


# Consideraciones y problemas encontrados
### Aceptación de conexión:
Al crear el socket en el server al momento de inicializarse este, al usar socket.accept() se bloquea la función hasta que se conecta el socket del cliente. Cuando se acepta la conexión con el cliente, socket.accept() devuelve el nuevo socket conectado al cliente, por lo que hay que hacer un move para reemplazar al socket anterior que escuchaba conexiones. Esto porque con los constructores de la implementación dada, no es posible inicializar inválidamente (nullptr) otro socket al momento de crear el ServerProtocol, que espere a ese nueva conexión, habiendome resultado obligatorio descartar el socket que aceptaba las conexiones.
### Recepción de mensajes de largo desconocido:
Al momento de recibir mensajes en el server, como no sabía cuantos bytes se iban a recibir, usaba socket.recvsome(). Teniendo que llamar a la función iterativamente hasta llegar al final del mensaje enviado, que por convención era el byte 0x00, tomando en consideración que por cada vez que se ejecutaba el buffer enviado, se sobreescribía. Y utilizando dos buffers (uno fijo para cada linea leída y otro temporal para cada llamada a la función), para asegurarme de luego procesar la linea completa necesaria.<br>
Además era necesario verificar luego de cada recepción de bytes en el server, que no se haya cerrado el socket. Ya que cuando el cliente cerraba el socket se terminaba el programa, actualizándose el booleano was_closed, y así evitar broken pipes.
### Uso exacto de bytes:
Para asegurarme que cuando necesitaba enviar un byte o dos bytes exactos, usaba los tipos de datos sin signo uint8_t y uint16_t que me aseguraban esos bits respectivamente.
### Formato del mensaje (payload) del server: 
Buscando contestar mensajes con formato "largo del payload" "payload", primero llamaba a socket.sendall() (porque sabía cuantos bytes iba a enviar de antemano), para enviar el largo del payload. Aplicándole primero htons() para asegurarme de que se envíe el valor en formato Big Endian. Y luego enviando todo el payload completo. Recibiéndose ordenadamente en el cliente los bytes.<br>
El cliente luego podía usar socket.recvall(), sabiendo cuantos bytes iba a recibir (habiendo interpretado antes esa parte del mensaje).
### Otras consideraciones:
- Usando la función getline() se ignoran los espacios entonces obtenía las acciones correctamente.
- ServerProtocol y ClientProtocol encapsulan todas las funcionalidades como privadas, por lo que fuera de ellos solo se puede iniciar la comunicación, pero no modificarlos directamente.
- Al enviar strings desde el server al cliente, por ejemplo "JUMP", como se envian bytes cada letra se traduce en ASCII.
  

## Anexo

Código PlantUML que generó el diagrama:

```
@startuml
hide empty attributes
hide circle


package "User Interface"  {
  class Client {
    - ClientProtocol protocol
    + Client(const char* hostname, const char* port)
    + void run();
  }
}

package "Protocol"  {
  class ClientProtocol{
    - Socket socket
    - std::vector<Action> encode_actions_line(std::string& line)
    + ClientProtocol(const char* hostname, const char* port)
    + void send_message(std::string line)
    + std::string receive_message()
  }
  class ServerProtocol{
    - Socket socket
    + ServerProtocol(Socket& socket)
    + std::vector<uint8_t> receive_line(bool* was_closed)
    + std::vector<std::string> decode_received_line(uint8_t* data, int number_received)
    + void send_received_line(const std::string& line, bool* was_closed)
    
  }
}

package "Network"  {
  class Socket {
    -sendall()
    -recvall()
    -sendsome()
    -recvsome()
    -accept()
    + Socket (const char* hostname, const char* servname)
    + Socket (const char* servname)
  }

}


package "Game"  {
  class Server {
    - Socket socket
    + Server(const char* port)
    + void run()
  }
  class GameLogic{
    - int performed_actions
    + GameLogic()
    + std::string filter_combos(std::string* received_actions, int received_number)
    + int get_performed_actions()
  }
}



Network <-- "Protocol"
Protocol <-- "User Interface"
Protocol <-- "Server"
GameLogic <-- "Server"

@enduml
