#include "BSEngine.h"

// Derived class
class Base : public OBSEngine
{
	REFLECT(Base, OBSEngine)
public:
	int i;
	virtual void Function() {}
	Base() : i(1)
	{
	}

	REFLECT_MEMBER(Base, i)

};

// More derived class
class Derived : public Base
{
	REFLECT(Derived, Base)
public:
	float f;
	void Function() override {}
	Derived() : f(1.0f)
	{
	}

	REFLECT_MEMBER(Derived, f)

};

int main()
{

	/* Reflection 기능 디버그 */
#if DEBUG_AVAILABLE
	// Register the classes
	Base::RegisterReflection();
	Derived::RegisterReflection();

	// Get class info for Derived
	const ClassInfo* classInfo = BSReflectionSystem.BSGetClassInfo(typeid(Derived));
	if (classInfo)
	{
		std::cout << "Class: " << classInfo->Name << std::endl;

		// Get parent class info
		const ClassInfo* parentClassInfo = BSReflectionSystem.BSGetClassInfo(classInfo->ParentType);
		if (parentClassInfo)
		{
			std::cout << "Parent Class: " << parentClassInfo->Name << std::endl;
		}

		std::cout << classInfo->Members[0].Name << std::endl;

		for (auto& member : classInfo->Members)
		{
			std::cout << "Member: " << member.Name << ", Type: " << member.Type.name() << std::endl;
		}
	}
#endif
	

	std::unique_ptr<OBSEngine> BSEngine = std::unique_ptr<OBSEngine>(new OBSEngine);
	
	double NextFrameMs = BSEngine->GetCurrentTime();
	uint32 SkippedFrameCount;
	while (true)
	{
		SkippedFrameCount = 0;
		while (BSEngine->GetCurrentTime() > NextFrameMs && SkippedFrameCount < MAX_FRAME_SKIP)
		{
			BSEngine->Update();

			NextFrameMs += MSECS_PER_FRAME;
			SkippedFrameCount++;
		}
		BSEngine->Render();
	}



	return 0;
}