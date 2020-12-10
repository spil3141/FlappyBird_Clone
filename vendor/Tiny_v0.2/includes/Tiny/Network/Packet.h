#pragma once
#include "Common.h"

namespace Tiny {

	// Packet Header Examples Type
	/*enum class MessageTypes : uint32_t
	{
		ServerAccept,
		FindMatch,
		MatchFound,
		BoardUpdate,
		MoveRegister,
		SignalServerDisconnect
	};*/

	template <typename T>
	struct Packet_Header
	{
		T id{};
		uint32_t size = 0;
	};

	template<typename T>
	struct Packet
	{
		Packet_Header<T> header{};
		std::vector<uint8_t> body;

		size_t size() const{ return body.size(); }

		friend std::ostream& operator << (std::ostream& os, const Packet<T>& msg)
		{
			os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
			return os;
		}

		/* Summary: 
		    - Convenience Operator overloads - These allow us to add and remove stuff from
			- the body vector as if it were a stack, so First in, Last Out. These are a
			- template in itself, because we dont know what data type the user is pushing or
			- popping, so lets allow them all. NOTE: It assumes the data type is fundamentally
			- Plain Old Data (POD). TLDR: Serialise & Deserialise into/from a vector
		*/
		// Pushes any POD-like data into the Packet buffer
		template<typename DataType>
		friend Packet<T>& operator << (Packet<T>& msg, const DataType& data)
		{
			// Check that the type of the data being pushed is trivially copyable
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

			// Cache current size of vector, as this will be the point we insert the data
			size_t i = msg.body.size();

			// Resize the vector by the size of the data being pushed
			msg.body.resize(msg.body.size() + sizeof(DataType));

			// Physically copy the data into the newly allocated vector space
			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

			// Recalculate the message size
			msg.header.size = msg.size();

			// Return the target message so it can be "chained"
			return msg;
		}

		// Pulls any POD-like data form the Packet buffer
		template<typename DataType>
		friend Packet<T>& operator >> (Packet<T>& msg, DataType& data)
		{
			// Check that the type of the data being pushed is trivially copyable
			static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

			// Cache the location towards the end of the vector where the pulled data starts
			size_t i = msg.body.size() - sizeof(DataType);

			// Physically copy the data from the vector into the user variable
			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

			// Shrink the vector to remove read bytes, and reset end position
			msg.body.resize(i);

			// Recalculate the message size
			msg.header.size = msg.size();

			// Return the target message so it can be "chained"
			return msg;
		}
	};

	/* Summary:
			-An "owned" packet is identical to a regular Packet, but it is associated with
			- a connection. On a server, the owner would be the client that sent the Packet,
			- on a client the owner would be the server.
	*/

	// Forward declare the connection
	template <typename T>
	class Connection;

	template <typename T>
	struct Owned_Packet
	{
		std::shared_ptr<Connection<T>> owner = nullptr;
		Packet<T> msg;

		// Again, a friendly string maker
		friend std::ostream& operator<<(std::ostream& os, const Owned_Packet<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
}

