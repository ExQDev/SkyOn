// SkyOn Data.h

#pragma once
#define SkyOn_Data_H
#include <stdio.h>
#include <string>
//#ifdef SkyOn_Data_H


namespace SkyOnData {



typedef struct 
	{
		
	public:
		float x;
		float y;
		float z;
		float w;
		void Set(float X, float Y, float Z, float W) 
		{
			x = X;
			y = Y;
			z = Z;
			w = W;
		}

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & x;
			ar & y;
			ar & z;
			ar & w;
		}
	} Vector4;

	typedef struct
	{
	public:
		Vector4 pos;
		Vector4 rot;
		float scale;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & pos;
			ar & rot;
			ar & scale;
		}
	} Player;

	typedef struct
	{
	public:
		int id;
		Player player;
		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & id;
			ar & player;
		}
	}  Locatn;




	typedef struct
	{
	public:
		Locatn location;
		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & location;
		}
	} GameState;

	typedef struct
	{
	public:
		std::string name;
		std::string ip;
		int npcID;
		GameState state;
		std::string type = "def";

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & name;
			ar & ip;
			ar & npcID;
			ar & state;
			ar & type;
		}
	} Client ;


	
}
//#endif // SKYON_DATA_H