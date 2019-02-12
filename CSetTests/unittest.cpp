#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\CSet\Set.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

typedef CSet<int> CIntSet;
typedef CSet<CString, LPCTSTR> CStringSet;

namespace CSetTests
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestIntSet)
		{
			CIntSet cis;
			for (int i = 0; i < 10; ++i)
			{
				cis.Add(i);
			}
			Assert::IsTrue(cis.GetCount() == 10);

			POSITION pos = cis.GetStartPosition();
			int nKey;
			while (pos != NULL)
			{
				cis.GetNextAssoc(pos, nKey);
				Assert::IsTrue(nKey >= 0 && nKey < 10);
			}

			Assert::IsFalse(cis.Add(1));
			Assert::IsTrue(cis.Add(10));
			Assert::IsTrue(cis.GetCount() == 11);

			for (int i = 0; i <= 10; ++i)
			{
				Assert::IsTrue(cis.Contains(i));
			}

			cis.Remove(10);
			Assert::IsFalse(cis.Contains(10));
		}

		TEST_METHOD(TestStringSet)
		{
			CStringSet css;
			Assert::IsTrue(css.IsEmpty());

			css.Add("Apples");
			css.Add("Bananas");
			css.Add("Oranges");
			Assert::IsTrue(css.GetCount() == 3);

			POSITION pos = css.GetStartPosition();
			CString sKey;
			while (pos != NULL)
			{
				css.GetNextAssoc(pos, sKey);
				Assert::IsTrue(sKey == "Apples" || sKey == "Bananas" || sKey == "Oranges");
			}

			Assert::IsTrue(css.Contains("Apples"));
			Assert::IsTrue(css.Contains("Bananas"));
			Assert::IsTrue(css.Contains("Oranges"));

			css.Remove("Bananas");
			Assert::IsFalse(css.Contains("Bananas"));

			css.Add("Bananas");
			Assert::IsTrue(css.GetCount() == 3);
			css.Add("Bananas");
			Assert::IsTrue(css.GetCount() == 3);

			css.RemoveAll();
			Assert::IsTrue(css.IsEmpty());
		}

		TEST_METHOD(TestSerialization)
		{
			CStringSet css;
			css.Add("Apples");
			css.Add("Bananas");
			css.Add("Oranges");
			Assert::IsTrue(css.GetCount() == 3);

			CFile file;
			file.Open(_T("set.dat"), CFile::modeCreate | CFile::modeWrite);
			CArchive archive(&file, CArchive::store);
			css.Serialize(archive);
			archive.Close();
			file.Close();
			css.RemoveAll();
			Assert::IsTrue(css.GetCount() == 0);

			file.Open(_T("set.dat"), CFile::modeRead);
			CArchive archive2(&file, CArchive::load);
			css.Serialize(archive2);

			Assert::IsTrue(css.GetCount() == 3);
			Assert::IsTrue(css.Contains("Apples"));
			Assert::IsTrue(css.Contains("Bananas"));
			Assert::IsTrue(css.Contains("Oranges"));

			archive2.Close();
			file.Close();
			CFile::Remove(_T("set.dat"));
		}
	};
}
