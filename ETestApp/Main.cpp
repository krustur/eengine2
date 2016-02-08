#include <windows.h>
#include "AppFactory.h"
#include "AppWindowFactory.h"
#include "Logger.h"
#include "BoxTest.h"

#include <stdio.h>

#pragma comment (lib, "D3D11.lib")
//#pragma comment (lib, "Effects11.lib")
/*d3d11.lib
Effects11.lib
d3dcompiler.lib*/
using namespace EEngine;

class CopyAssignmentAndConstructorTest {
	public: 
		CopyAssignmentAndConstructorTest(int member) { _member = member; }

		CopyAssignmentAndConstructorTest(const CopyAssignmentAndConstructorTest &other) { // Copy constructur
			_member = 100 + other._member;
		}
		CopyAssignmentAndConstructorTest & operator= (const CopyAssignmentAndConstructorTest & other) { // Copy assignment operator
			_member = 200 + other._member;
			return *this;
		}
		~CopyAssignmentAndConstructorTest() {
			_member += 1000;
		}

		int _member;
};

class DeleteSpecialMembersTest {
public:
	DeleteSpecialMembersTest(int member) { _member = member; }
	DeleteSpecialMembersTest(const DeleteSpecialMembersTest &other) = delete;
	DeleteSpecialMembersTest & operator= (const DeleteSpecialMembersTest & other) = delete;
	~DeleteSpecialMembersTest() {};

	int _member;
};

void TestCode()
{
	CopyAssignmentAndConstructorTest *a1 = new CopyAssignmentAndConstructorTest(1);
	CopyAssignmentAndConstructorTest a2 = CopyAssignmentAndConstructorTest(2);
	CopyAssignmentAndConstructorTest(3); // Temporary, destroyed immediately
	a1 = new CopyAssignmentAndConstructorTest(4); // pointer => not destroyed (=memory leak!)
	a2 = CopyAssignmentAndConstructorTest(5); // Copy assignment operator "ConstructorTest(5)" is destroyed after assignment
	CopyAssignmentAndConstructorTest a6 = CopyAssignmentAndConstructorTest(6);
	CopyAssignmentAndConstructorTest a7 = CopyAssignmentAndConstructorTest(a6); // Copy constructor
	// a2, a6 and a7 are destroyed

	DeleteSpecialMembersTest *b1 = new DeleteSpecialMembersTest(1);
	//DeleteSpecialMembersTest b2 = DeleteSpecialMembersTest(2);
	//DeleteSpecialMembersTest b3 = DeleteSpecialMembersTest(*b1); // Can't compile, Copy constructor is deleted
	//DeleteSpecialMembersTest b4 = DeleteSpecialMembersTest(b2); // Can't compile, Copy constructor is deleted
	//b2 = DeleteSpecialMembersTest(5); // Can't compile, Copy assignment operator is deleted
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmsLine, int nShowCmd)
{
	AppWindowFactory windowFactory;
	auto &window = windowFactory.CreateAppWindow(hInstance, nShowCmd);
	window.Init();

	AppFactory appFactory;
	auto &app = appFactory.CreateApp(hInstance, window.GetWindowHandle());
	app.SetAppStatsListener(&window);

	window.Open();

	TestCode();
	
	app.Init();

	BoxTest boxTest(&app);
	boxTest.Init();

	app.SetEffect(&boxTest);
	window.SetWindowEventListener(&boxTest);
	window.SetWindowEventListener(&app);
	window.SetWindowEventListener(app.GetRenderer());

	auto runResult = app.Run();

	return runResult;
}

