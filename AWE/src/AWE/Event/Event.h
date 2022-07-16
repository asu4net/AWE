#pragma once
#include "AWE/Log/Log.h"

namespace AWE
{
	//Add Listener macro...

	//Subscribes t_function to the Event.
	#define ADD_LISTENER(TSubscriber, ListenerMethod) AddListener(this, &TSubscriber::ListenerMethod)

	template<class TArgs>
	using Method = std::function<void(TArgs)>;

	/// <summary>
	/// Holds a method, that can be invoked by an Event, and an index.
	/// The only purpose of the index is to be compared.
	/// Index -1 indicates an uninitialized Listener.
	/// in Event class methods like: RemoveListener() or HasListener().
	/// </summary>
	template<class TArgs>
	struct Listener
	{
		int index = -1;
		Method<TArgs> method;

		Listener(const int t_index, Method<TArgs> t_method)
			: index(t_index), method(t_method) {}

		bool operator==(const Listener& other)
		{
			return index == other.index;
		}
	};

	/// <summary>
	/// Events enable a class to notify other classes when something of interest occurs.
	/// The class that sends(or raises) the Event is called the Publisher and the classes that receive(or handle) the
	/// Event are called Subscribers. The Publisher notifies through calling Subscriber methods called Listeners.
	/// So the Event class just stores and manages a vector of Listeners (class methods).
	/// It ONLY supports class member functions.
	/// </summary>
	template<typename TArgs>
	class Event
	{
	private:
		Vector<Listener<TArgs>> m_listeners;
		int m_count = 0;

		template<typename TArgs>
		using ListenerIterator = typename Vector<Listener<TArgs>>::iterator;

		//Check if the given Listener is subscribed.
		bool HasListener(Listener<TArgs> t_listener, ListenerIterator<TArgs>& t_it)
		{
			t_it = std::find_if(m_listeners.begin(), m_listeners.end(),
				[t_listener](Listener<TArgs>& i_listener) { return t_listener == i_listener; });

			if (t_it == m_listeners.end())
				return false;

			return true;
		}

	public:
		Event() = default;
		Event(Event& other) = delete;
		Event(Event&& other) = delete;
		~Event() { RemoveAllListeners(); }

		//Subscribes t_function to the Event.
		template<class TSubscriber>
		Listener<TArgs> AddListener(TSubscriber* t_subscriber, void (TSubscriber::* t_function)(TArgs))
		{
			Listener<TArgs> listener = m_listeners.emplace_back(m_count, std::bind(t_function, t_subscriber, std::placeholders::_1));
			m_count++;
			return listener;
		}

		//Check if the given Listener is subscribed.
		bool HasListener(Listener<TArgs> t_listener)
		{
			ListenerIterator<TArgs> it;
			return HasListener(t_listener, it);
		}

		//Unsubscribes t_function from the Event.
		void RemoveListener(Listener<TArgs> t_listener)
		{
			if (ListenerIterator<TArgs> it; HasListener(t_listener, it))
			{
				m_listeners.erase(it);
				return;
			}
			
			LOG_WARN("Listener not found."); //TODO: Use the future Logging System.
		}

		//Removes all the Event subscriptions.
		void RemoveAllListeners() { m_listeners.clear(); }

		//Fires the event and dispatches a TArgs instance.
		void Invoke(TArgs t_args)
		{
			for (const Listener<TArgs>& listener : m_listeners)
				listener.method(t_args);
		}
	};
}