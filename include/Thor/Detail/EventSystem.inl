/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2012 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

namespace thor
{

template <typename Event, typename EventIdentifier>
EventSystem<Event, EventIdentifier>::EventSystem()
: mListeners()
{
}

template <typename Event, typename EventIdentifier>
void EventSystem<Event, EventIdentifier>::triggerEvent(const Event& event)
{
	// Import symbol extractEventIdentifier to qualify for ADL.
	using namespace detail;

	mListeners.call(extractEventIdentifier(event), event);
}

template <typename Event, typename EventIdentifier>
Connection EventSystem<Event, EventIdentifier>::connect(const EventIdentifier& trigger, const Listener& listener)
{
	return mListeners.add(trigger, listener);
}

template <typename Event, typename EventIdentifier>
void EventSystem<Event, EventIdentifier>::clearConnections(EventIdentifier identifier)
{
	mListeners.clear(identifier);
}

template <typename Event, typename EventIdentifier>
void EventSystem<Event, EventIdentifier>::clearAllConnections()
{
	mListeners.clearAll();
}

// ---------------------------------------------------------------------------------------------------------------------------


namespace detail
{

	// Default implementation for events where the Event type is the same as the EventIdentifier type.
	// This declaration must appear after the invocation in call(), since g++ otherwise prefers
	// this function for overload resolution (while the overload for sf::Event isn't considered).
	template <typename Event>
	const Event& extractEventIdentifier(const Event& event)
	{
		return event;
	}

} // namespace detail
} // namespace thor