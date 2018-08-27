#include "ConnectionTest.h"
#include "cute.h"

#include "Connection.h"

#include <type_traits>

using nn::Connection;

void connectionDefaultConstructible() {
	ASSERT(std::is_default_constructible<Connection<size_t>>::value);
}

void connectionCopyConstructible() {
	ASSERT(std::is_copy_constructible<Connection<size_t>>::value);
}

void connectionCopyAssignable() {
	ASSERT(std::is_copy_assignable<Connection<size_t>>::value);
}

void connectionConstructableSizeT() {
	size_t const& ref { 12 };

	Connection<size_t> const connection { ref };
	ASSERT_EQUAL(.0f, connection.getWeight());
}

void connectionConstructableWithWeight() {
	size_t const& ref { 12 };
	float const expected { 42.f };

	Connection<size_t> const connection { ref, expected };
	ASSERT_EQUAL(expected, connection.getWeight());
}

void connectionSetRandomWeight() {
	float const weight { 42.f };

	Connection<size_t> connection { 42, weight };
	connection.setRandomWeight();

	ASSERT_NOT_EQUAL_TO(weight, connection.getWeight());
}

cute::suite make_suite_ConnectionTest() {
	cute::suite s { };
	s.push_back(CUTE(connectionDefaultConstructible));
	s.push_back(CUTE(connectionCopyConstructible));
	s.push_back(CUTE(connectionCopyAssignable));
	s.push_back(CUTE(connectionConstructableSizeT));
	s.push_back(CUTE(connectionConstructableWithWeight));
	s.push_back(CUTE(connectionSetRandomWeight));
	return s;
}
