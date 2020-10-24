#pragma once

#include<iostream>
#include<memory>
using std::dynamic_pointer_cast;
using std::shared_ptr;
using std::static_pointer_cast;
using std::weak_ptr;
using std::cerr;

#include<functional>
using std::function;

#include<vector>
#include<unordered_map>
#include<unordered_set>
using std::vector;
using std::unordered_map;
using std::unordered_set;

#include<string>
using std::string;
using std::wstring;



template<class ClassType>
void ASSERT_VALID(weak_ptr<ClassType> ptr) {
	if (shared_ptr<ClassType>(ptr) == nullptr || ptr.expired()) {
		throw new std::exception("Weak Pointer was null");
	}
}

template<class ClassType>
shared_ptr<ClassType> makeShared(weak_ptr<ClassType> weakPtr) {
	ASSERT_VALID<ClassType>(weakPtr);

	return shared_ptr<ClassType>(weakPtr);
}