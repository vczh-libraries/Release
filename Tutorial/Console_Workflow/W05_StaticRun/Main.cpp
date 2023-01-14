#include "Generated/W05ScriptIncludes.h"

using namespace myscript;

int main()
{
	// VCZH_DEBUG_NO_REFLECTION is on
	// so we don't need, and are not allowed, to start reflection
	auto myapp = Ptr(new MyApp);
	myapp->CreateScripting()->Execute(L"Gaclib");

	// we need to call this because we use generated code from Workflow script
	FinalizeGlobalStorage();
}