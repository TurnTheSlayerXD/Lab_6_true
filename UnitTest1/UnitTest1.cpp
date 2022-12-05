#include "pch.h"
#include "CppUnitTest.h"
#include"..\Lab_6\Functions.h";
#include<iostream>
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			string get = fuu("[sin(x)]");
			string expected = "(cos(x)*1)";
			bool x = false;
			if (get == expected)
				x = true;
			Assert::IsTrue(x == true);
		}

		TEST_METHOD(TestMethod2)
		{
			string get = fuu("[3^x]");
			string expected = "3^x*(0*(x)+1*log(3))";
			bool x = false;
			if (get == expected)
				x = true;
			Assert::IsTrue(x == true);
		}
		TEST_METHOD(TestMethod3)
		{
			string get = fuu("[x^x]");
			string expected = "x^x*((1/(x)*1)*(x)+1*log(x))";
			bool x = false;
			if (get == expected)
				x = true;
			Assert::IsTrue(x == true);
		}
	};
}