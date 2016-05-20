#include "SkyOn Server.h"

//typedef unsigned char BYTE;
#define MAX_CLIENTS 32
bool loaded = false;
std::string serverIP = "null";
boost::container::vector<Client> clients;
int port = 666;
boost::container::vector<Server> procs;



std::string operator *(std::string a, int b)
{
	std::string str;
	for (int i = 0; i < b; i++)
	{
		str += a;
	}
	return str;
}


std::string GetKeyName(BYTE key)
{
	DWORD sc = MapVirtualKeyA(key, 0);
	// check key for ascii
	BYTE buf[256];
	memset(buf, 0, 256);
	WORD temp;
	DWORD asc = (key <= 32);
	if (!asc && (key != VK_DIVIDE)) asc = ToAscii(key, sc, buf, &temp, 1);
	// set bits
	sc <<= 16;
	sc |= 0x1 << 25;  // <- don't care
	if (!asc) sc |= 0x1 << 24; // <- extended bit
							   // convert to ansi string
	if (GetKeyNameTextA(sc, (char *)buf, sizeof(buf)))
		return (char *)buf;
	else return "";
}


void Load()
{
	std::string slah[5];
	slah[0] = "\\";
	slah[1] = "|";
	slah[2] = "/";
	slah[3] = char(0xC4);
	slah[4] = "\\";
	std::string ok = { char(0xFB) };
	std::string poins[5];
	poins[0] = ".   ";
	poins[1] = "..   ";
	poins[2] = "... ";
	poins[3] = "....";
	poins[4] = ".   ";
	for (int i = 0; !loaded; i++)
	{
		std::string point = ".";
		std::string a = point * i;
		std::cout << "\r" << ((!loaded) ? ((slah[i]).c_str()) : ok.c_str()) << "\t" << "Starting SkyOn server" << poins[i].c_str() << "\t" << ((loaded && i == 4) ? "\n" : "  ");
		if (i == 4)
		{
			a = " ";
			i = 0;
		}
		boost::posix_time::milliseconds sleep(200);
		boost::this_thread::sleep(sleep);

	}
	
}

void Init() 
{
	boost::thread Loading(Load);
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini("SkyOn.ini", pt);
	BYTE key = (pt.get<BYTE>("main.key"));
	serverIP = pt.get<std::string>("connection.serverip");
	port = pt.get<int>("connection.port");
	std::string ok = { char(0xFB) };
	std::string poins[5];
	poins[0] = ".   ";
	poins[1] = "..   ";
	poins[2] = "... ";
	poins[3] = "....";
	poins[4] = ".   ";
	loaded = true;
	boost::posix_time::milliseconds sleep(400);
	boost::this_thread::sleep(sleep);
	std::cout << "\r" << (ok.c_str()) << "\t" << "Starting SkyOn server" << poins[2].c_str() << "\t" << ((loaded) ? "\n" : "  ");
	std::cout << "\n" << "Client connection Key : " << GetKeyName(key).c_str();
	std::cout << "\n" << "My IP : " << serverIP;
	std::cout << "\n" << "Port: " << port;
	std::cout << "\n";
	std::cout << "\nMax clients: \t\t" << MAX_CLIENTS;
	std::cout << "\nCurrent clients: \t" << clients.size();
}


int main()
{
	//Console::WriteLine();
	boost::thread Thread(Init);
	Thread.join();
	std::cout << "\n";
	while (true)
	{
		std::string title = "title SkyON Server. Clients:" + std::to_string(clients.size());
		system(title.c_str());
		if (procs.size() <= MAX_CLIENTS)
		{
			try
			{
				Server server;
				Client client;
				clients.push_back(client);
				boost::asio::io_service service;
				tcp::endpoint endp(tcp::v4(), port);
				tcp::socket socket(service);
				tcp::acceptor acc(service, endp);
				server.Init(&socket, &service, endp, client);
				acc.async_accept(socket, endp, boost::bind(&Server::Start, &(server)));
				procs.push_back(server);
			}
			catch (std::exception& e)
			{
				std::cerr << "Exception: " << e.what() << "\n";
				break;
			}
		}
		
	}
	

	std::getchar();
	return 0;
}
