#pragma once
#include <vector>
#include <functional>

template<typename Ret, typename... Args>
struct Event {
	std::vector<std::function<Ret(Args...)>> functions;

	Event() = default;
	Event(const Event&) = default;
	Event(Event&&) = default;

	void operator()(Args... args) {
		for (auto& func : functions)
		{
			func(args...);
		}
	}

	
	Event<Ret, Args...>& operator+=(std::function<Ret(Args...)> subscriber) {
		functions.push_back(subscriber);
		return *this;
	}
};

