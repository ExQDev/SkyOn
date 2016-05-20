#pragma once
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp> 
#include <SkyOn Data.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <fstream>
#include <iostream>

using boost::asio::ip::tcp;

namespace SkyOnClient
{
	class Client
	{
		bool disconnect;

	public:
		tcp::socket * sock;
		boost::asio::io_service * service;
		tcp::endpoint ep;
		SkyOnData::Client & client;
		void OnConnect(tcp::socket * sock, boost::asio::io_service * service, tcp::endpoint & ep, SkyOnData::Client & client)
		{
			//sock->async_connect(ep, boost::bind((Client::Connection), &this->Connection, &sock, &service, ep, client));
		}
		void OnDisconnect()
		{
			this->disconnect = true;
			this->Disconnect();
		}
		void Disconnect()
		{

		}

		void Connection(tcp::socket * sock, boost::asio::io_service * service, tcp::endpoint & ep, SkyOnData::Client & client)
		{
			boost::thread disc(boost::bind(&Client::OnDisconnect, this));
			
			while (!disconnect)
			{
				Send(client);
				Receive(client);
			}
		}

		void Send(SkyOnData::Client & client) 
		{
			try {
				std::stringstream ss;
				{ boost::archive::binary_oarchive(ss) << client; }
				boost::system::error_code error = boost::asio::error::host_not_found;
				boost::asio::write(sock, boost::asio::buffer(ss.str()), boost::asio::transfer_all(), error);
			}
			catch(const boost::system::system_error& e)
			{
				
			}
		}

		void Receive(SkyOnData::Client & client) 
		{
			std::stringstream ss;
			{ boost::archive::binary_iarchive(ss) >> client; }
			boost::system::error_code error = boost::asio::error::host_not_found;
			boost::asio::write(sock, boost::asio::buffer(ss.str()), boost::asio::transfer_all(), error);
		}

	};
}
