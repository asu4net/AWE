#pragma once
#include "AWEpch.h"

namespace AWE
{
	//Add Listener macro...

	//Suscribes t_function to the Event.
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

		Listener(int t_index, Method<TArgs> t_method)
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
	/// It ONLY suports class member functions.
	/// </summary>
	template<class TArgs>
	class Event
	{
	private:
		vector<Listener<TArgs>> m_Listeners;
		int m_Count = 0;

		template<class TArgs>
		using ListenerIterator = typename vector<Listener<TArgs>>::iterator;

		//Check if the given Listener is suscribed.
		bool HasListener(Listener<TArgs> t_Listener, ListenerIterator<TArgs>& t_it)
		{
			t_it = std::find_if(m_Listeners.begin(), m_Listeners.end(),
				[t_Listener](Listener<TArgs>& i_Listener) { return t_Listener == i_Listener; });

			if (t_it == m_Listeners.end())
				return false;

			return true;
		}

	public:
		Event() = default;
		Event(Event& other) = delete;
		Event(Event&& other) = delete;
		~Event() { RemoveAllListeners(); }

		//Suscribes t_function to the Event.
		template<class TSubscriber>
		Listener<TArgs> AddListener(TSubscriber* t_Subscriber, void (TSubscriber::* t_function)(TArgs))
		{
			Listener<TArgs> listener = m_Listeners.emplace_back(m_Count, std::bind(t_function, t_Subscriber, std::placeholders::_1));
			m_Count++;
			return listener;
		}

		//Check if the given Listener is suscribed.
		bool HasListener(Listener<TArgs> t_Listener)
		{
			ListenerIterator<TArgs> it;
			return HasListener(t_Listener, it);
		}

		//Unsubscribes t_function from the Event.
		void RemoveListener(Listener<TArgs> t_Listener)
		{
			ListenerIterator<TArgs> it;

			if (HasListener(t_Listener, it))
			{
				m_Listeners.erase(it);
				return;
			}
				
			LOG("Listener not found."); //TODO: Use the future Logging System.
		}

		//Removes all the Event subscriptions.
		void RemoveAllListeners() { m_Listeners.clear(); }

		//Fires the event and dispatches a TArgs instance.
		void Invoke(TArgs t_Args)
		{
			for (Listener listener : m_Listeners)
				listener.method(t_Args);
		}
	};
}