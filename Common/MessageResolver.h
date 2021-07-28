#pragma once
#include <functional>
#include <memory>
#include "Message.h"
#include <tuple>
struct tcp_connection;

struct MessageResolver
{
	MessageResolver();
	MessageResolver(const MessageResolver&) = default;
	MessageResolver(MessageResolver&&) = default;
	
	static size_t nextId;

	static std::vector<std::function<void(tcp_connection&)>> resolvers;
	std::unordered_map<size_t, std::function<void(tcp_connection&)>> responseHandlers;

	void resolveMessage(tcp_connection& connection);
	MessageID addRequest(std::function<void(tcp_connection&)>&& responseHandler);
	static void initResolvers();


	template<typename T, typename Connection> 
	static void resolverFor(Connection& connection) {
		auto&& guard = connection.getGuardRead();
		connection.read<T>().respond(connection);
	}

	template<MessageID ID, typename T> 
	static void addResolver() {
		resolvers[ID] = resolverFor<T, tcp_connection>;
	}

	static void reserveMaxResolvers(size_t m) {
		resolvers.resize(m);
	}
};

//template<int N, typename... Ts> using NthTypeOf =
//typename std::tuple_element<N, std::tuple<Ts...>>::type;


//template<typename... Messages>
//struct MessageDirector
//{
//	MessageDirector();
//	MessageDirector(const MessageDirector&) = default;
//	MessageDirector(MessageDirector&&) = default;
//
//	static size_t nextId;
//
//	static std::array<std::function<void(tcp_connection&)>, 1> resolvers;
//	std::tuple<Messages...> messages;
//
//
//	std::unordered_map<size_t, std::function<void(tcp_connection&)>> responseHandlers;
//
//	template<typename T>
//	T load(tcp_connection& connection) {
//		return connection.read<T>();
//	}
//
//	template<typename I>
//	void loadMessage(tcp_connection& connection) {
//		using Type = NthTypeOf<I, Messages...>;
//		auto message = load<Type>(connection);
//		message.respond(connection);
//	}
//
//	template<int i> 
//	void resolveDynamic(int j, tcp_connection& connection) {
//		if (j == i) {
//			loadMessage<i>(connection);
//		}
//		else {
//			resolveDynamic(j + 1, connection);
//		}
//	}
//
//	void resolveMessage(tcp_connection& connection) {
//		
//	}
//
//	MessageID addRequest(std::function<void(tcp_connection&)>&& responseHandler);
//	static void initResolvers();
//};
//
