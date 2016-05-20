#define WIN32_LEAN_AND_MEAN
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/thread/thread.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <SkyOn Data.h>
#include "Client.h"

using namespace SkyOnData;

std::string serverIP = "null";
std::string playerName = "player";
int port = 666;
int playerID = 0;




void main()
{
	PrintNote("SkyOn has been started...");
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini("SkyOn.ini", pt);
	BYTE key = (pt.get<BYTE>("main.key"));
	PrintNote("Key: '%s'", GetKeyName(key).c_str());
	serverIP = pt.get<std::string>("connection.serverip");
	port = pt.get<int>("connection.port");
	playerID = ID_Character::AelaTheHuntressREF;
	PrintNote("Server IP: %s, Port: %i", serverIP.c_str(), port);
	bool disable = false;
	while (TRUE)
	{
		
		if (GetKeyPressed(key))
		{
			PrintNote("Key Pressed!");
			
			try 
			{
				PrintNote("Your NPC: %i", playerID);
				TESObjectREFR * tempPlayer = (TESObjectREFR *)Game::GetFormById(playerID);
				ExecuteConsoleCommand((ObjectReference::IsDisabled(tempPlayer))?"enable":"disable", tempPlayer);
				SkyOnData::Client client;
				client.name = playerName;
				client.npcID = playerID;
				client.state.location.id = Form::GetFormID((TESForm*)ObjectReference::GetCurrentLocation((TESObjectREFR*)Game::GetPlayer()));
				client.state.location.player.pos.Set(ObjectReference::GetPositionX((TESObjectREFR*)Game::GetPlayer()), ObjectReference::GetPositionY((TESObjectREFR*)Game::GetPlayer()), ObjectReference::GetPositionZ((TESObjectREFR*)Game::GetPlayer()), 0.0);
				client.state.location.player.rot.Set(ObjectReference::GetAngleX((TESObjectREFR*)Game::GetPlayer()), ObjectReference::GetAngleY((TESObjectREFR*)Game::GetPlayer()), ObjectReference::GetAngleZ((TESObjectREFR*)Game::GetPlayer()), 0.0);
				client.state.location.player.scale = ObjectReference::GetScale((TESObjectREFR*)Game::GetPlayer());
				SkyOnClient::Client me;
				boost::asio::io_service ios;
				tcp::socket sock(ios);
				tcp::endpoint ep(boost::asio::ip::address_v4::from_string(serverIP), port);
				me.OnConnect(&sock, &ios, ep, client);
				
			}
			catch (std::exception& e)
			{
				PrintNote("Exception: %s", e.what());
			}
		}
		
		Wait(0);
	}
}

