#include"Network.h"

#define SERVER_IP "127.0.0.1"
#define BUFFER_LENGHT 4048 
#define PORT 51051

Network::Network() = default;
Network::~Network() = default;

int Network::connectClientOpen()
{
	struct sockaddr_in serveraddress;
	struct sockaddr_in client;

	int socket_discriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_discriptor == -1)
	{
		std::cout << "������ �������� ������!" << std::endl;
		return -1;
	}

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr(SERVER_IP);

	int connection = connect(socket_discriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	if (connection == -1)
	{
		std::cout << "�� ������� ���������� ���������� � ��������!" << std::endl;
		return -1;
	}
	return socket_discriptor;
}

// ���������
void Network::sendMessage(int connection, const std::string& str)
{
	char buffer[str.size() + 1]{};
	for (int i = 0; i <= (str.size()); i++)
	{
		buffer[i] = str[i];
	}
	size_t bytes = write(connection, buffer, (str.size() + 1));
	if (bytes == -1)
	{
		std::cout << "������ �������� ���������!" << std::endl;
	}

}

// ��������
std::string Network::reseiveMessage(int connection)
{
	char buffer[BUFFER_LENGHT]{};
	read(connection, buffer, sizeof(buffer));
	std::string str = buffer;
	return str;
}

void Network::connectClose(int socket_discriptor)
{
	close(socket_discriptor);
}

int Network::connectServerOpen()
{
	struct sockaddr_in serveraddress;
	struct sockaddr_in client;

	int socket_discriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_discriptor == -1)
	{
		std::cout << "������ �������� ������!" << std::endl;
		return -1;
	}

	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_family = AF_INET;

	int bind_status = bind(socket_discriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	if (bind_status == -1)
	{
		std::cout << "������ �������� ������!" << std::endl;
		return -1;
	}

	int connection_status = listen(socket_discriptor, 7);
	if (connection_status == -1)
	{
		std::cout << "������ ����� ������!" << std::endl;
		return -1;

	}
	else
	{
		std::cout << "Server is listening for new connection: " << std::endl;
	}

	socklen_t lenght = sizeof(client);
	int connection = accept(socket_discriptor, (struct sockaddr*)&client, &lenght);
	if (connection == -1)
	{
		std::cout << "������. ������ �� ����� ������� ������ �� �������!" << std::endl;
		return -1;
	}
	return connection;
}