#pragma once
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp> 
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio/write.hpp>
#include <SkyOn Data.h>

using boost::asio::ip::tcp;

class Server
{
	bool disconnect;

	

public:
	tcp::socket * sock;
	boost::asio::io_service * servc;
	tcp::endpoint ep;
	SkyOnData::Client clien;
	
	
	void Init(tcp::socket * socket, boost::asio::io_service * service, tcp::endpoint & endp, SkyOnData::Client & client) 
	{
		ep = endp;
		sock = socket;
		servc = service;
		clien = client;
		disconnect = false;
	}

	void OnConnect() 
	{
	
	}
	void OnDisconnect()
	{
		this->disconnect = true;
		this->Disconnect();
	}
	void Disconnect() 
	{
		
	}
	void Start() 
	{
		std::cout << "New Client Connected! IP: " << sock->remote_endpoint().address();
		std::cout << "New server started!\n";
		Connection();
	}

	void Send()
	{
		try {
			std::stringstream ss;
			boost::archive::binary_oarchive(ss) << clien;
			boost::system::error_code error = boost::asio::error::host_not_found;
			boost::asio::write(sock, boost::asio::buffer(ss.str()), boost::asio::transfer_all(), error);
		}
		catch (const boost::system::system_error& e)
		{

		}
	}

	void Receive()
	{
		std::stringstream ss;
		{ boost::archive::binary_iarchive(ss) >> clien; }
		boost::system::error_code error = boost::asio::error::host_not_found;
		boost::asio::write(sock, boost::asio::buffer(ss.str()), boost::asio::transfer_all(), error);
		std::cout << "Player ip: %d.%d.%d.%d" << clien.ip << "  \n Player name: " << clien.name << "\n PLayer ID: %i" << clien.npcID << ("\n PLayer pos: " + std::to_string(clien.state.location.player.pos.x) + std::to_string(clien.state.location.player.pos.y) + std::to_string(clien.state.location.player.pos.z)) << "\n PLayer Location: %i" << clien.state.location.id << "\n";
	}
	void Connection() 
	{
		//boost::thread disc(boost::bind(&Server::OnDisconnect, this));
		while (!disconnect) 
		{
			Receive();
		}
	}

	

	

	
};