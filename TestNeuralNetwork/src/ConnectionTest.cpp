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

	Connection<size_t> { ref, ref };
	ASSERT(true); // Everything okay if we are here
}

void connectionTryConstructWithOneArgument() {
	size_t const& ref { 12 };

	ASSERT_THROWS((Connection<size_t> { ref }), std::invalid_argument);
}

void connectionTryConstructWithThreeArguments() {
	size_t const& ref { 12 };

	ASSERT_THROWS((Connection<size_t> { ref, ref, ref }), std::invalid_argument);
}

cute::suite make_suite_ConnectionTest() {
	cute::suite s { };
	s.push_back(CUTE(connectionDefaultConstructible));
	s.push_back(CUTE(connectionCopyConstructible));
	s.push_back(CUTE(connectionCopyAssignable));
	s.push_back(CUTE(connectionConstructableSizeT));
	s.push_back(CUTE(connectionTryConstructWithOneArgument));
	s.push_back(CUTE(connectionTryConstructWithThreeArguments));
	return s;
}
