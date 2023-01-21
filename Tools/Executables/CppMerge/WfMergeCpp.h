/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Workflow::C++ Code Generator

Interfaces:
**********************************************************************/

#ifndef VCZH_WORKFLOW_CPP_WFMERGECPP
#define VCZH_WORKFLOW_CPP_WFMERGECPP

#include <VlppOS.h>

namespace vl
{
	namespace workflow
	{
		namespace cppcodegen
		{

/***********************************************************************
MergeCpp
***********************************************************************/

			class MergeCppMultiPlatformException : public Exception
			{
			public:
				vint											row32;
				vint											column32;
				vint											row64;
				vint											column64;

				MergeCppMultiPlatformException(vint _row32, vint _column32, vint _row64, vint _column64);
			};

			extern WString				MergeCppMultiPlatform(const WString& code32, const WString& code64);
			extern WString				MergeCppFileContent(const WString& dst, const WString& src);
		}
	}
}

#endif