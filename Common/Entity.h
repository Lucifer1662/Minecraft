#pragma once
#include <glm\glm.hpp>
#include "IUpdate.h"
#include <memory>
#include "tcp_connection.h"
#include <array>

template<typename View, typename Controller, typename Model, typename State>
struct Entity
{
	struct Server : public Model, public IUpdate  {
		Server() : State() {}
		Server(State state) : State(state) {}
		void update() override { Model::update(); }
	};

	struct Remote : public View, public Controller, public IUpdate {
		Remote() : State() {}
		Remote(State state) : State(state) {}
		void update() override { View::update(); Controller::update(); }
	};

	struct Local : public Model, public View, public Controller, public IUpdate {
		Local() : State() {}
		Local(State state) : State(state) {}
		void update() override { Model::update();  Controller::update(); View::update(); }
	};
};





template<typename... Data>
struct Message {
	size_t type;
	std::tuple<Data...> data;
	Message(size_t type, Data... data) : type(type),data(data...) {}

	void send(tcp_connection& connection) {
		connection.getMutexWrite().lock();
		connection.write(MessageClass::Request);
		connection.write(*this);
		connection.getMutexWrite().unlock();
	}
};

struct CowState {
	//udp
	glm::vec3 position = { 0,0,0 };
	glm::vec3 rotation = { 0,0,0 };
	//tcp
	bool milked = false;
	int health = 100;
	int enitityId = 0;

	void damage(int d) {
		health -= d;
	}
};





void f() {
	CowState state;
	
}

struct CowStateRemote : public virtual CowState {
	std::shared_ptr<tcp_connection> connection;



	//server
	void damage(int d) {
		Message(1,enitityId, (int)&health-(int)this, sizeof(health), d).send(*connection);
	}

	//client
	void resolve(int index, tcp_connection& connection) {
		auto offset = connection.read<int>();
		auto size = connection.read<int>();
		connection.read(this + offset, size);
	}

};

struct CowView : public virtual CowState {
	void update() {
		//render the cow
	}
};

struct CowModel : public virtual CowState {
	void update() {
		
	}
};

struct CowController : public virtual CowState {
	void update() {

	}
};


using Cow = Entity<CowView, CowController, CowModel, CowState>;