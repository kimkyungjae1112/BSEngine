#pragma once
#ifndef __BSENGINE_H__
#define __BSENGINE_H__
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <ctime>
#include <memory>
typedef unsigned int uint32;

#define DEBUG_AVAILABLE 1
#define DEBUG_UNAVAILABLE 0

/* Reflection System */
#define REFLECT(ClassName, ParentClassName) \
public: \
	static void RegisterReflection() \
	{ \
		BSReflectionSystem.RegisterClass(typeid(ClassName), #ClassName, typeid(ParentClassName)); \
	} \
	virtual const char* GetTypeName() const {return #ClassName;}\

#define REFLECT_MEMBER(ClassName, Member) \
public: \
	static void AddMember() \
	{ \
		BSReflectionSystem.RegisterMember(typeid(ClassName), #Member, typeid(decltype(ClassName::Member)); \
	} \

#define BSPROPERTY(...)

struct MemberInfo
{
	std::string Name;
	std::type_index Type;

	MemberInfo(const std::string& Name, const std::type_index& Type)
		: Name(Name), Type(Type) { }
};

struct ClassInfo
{
	std::string Name;
	std::vector<MemberInfo> Members;
	std::type_index ParentType;


	ClassInfo() : ParentType(typeid(void)) { }

	ClassInfo(const std::string& Name, const std::type_index& ParentType) : Name(Name), ParentType(ParentType) { }

	void AddMember(const std::string& Name, const std::type_index& Type)
	{
		Members.emplace_back(Name, Type);
	}
};

class ReflectionSystem
{
public:
	inline void RegisterClass(const std::type_index& Type, const std::string& Name, const std::type_index& ParentType)
	{
		Classes[Type] = ClassInfo(Name, ParentType);
	}

	inline void RegisterMember(const std::type_index& ClassType, const std::string& MemberName, const std::type_index& MemberType)
	{
		Classes[ClassType].AddMember(MemberName, MemberType);
	}

	const ClassInfo* BSGetClassInfo(const std::type_index& Type) const
	{
		auto It = Classes.find(Type);
		return It != Classes.end() ? &It->second : nullptr;
	}

private:
	std::unordered_map<std::type_index, ClassInfo> Classes;
};

/* Reflection System */
static ReflectionSystem BSReflectionSystem;



/* GameEngine Core */
const uint32 TICKS_PER_SECOND = 50;
const uint32 MSECS_PER_FRAME = 1000 / TICKS_PER_SECOND; // 20ms
const uint32 MAX_FRAME_SKIP = 10;

class OBSEngine
{
public:
	double GetCurrentTime();
	
	virtual void Update();
	virtual void Render();

private:

};


#endif __BSENGINE_H__