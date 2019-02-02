// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Set.h"
#include "Main.h"

#include <iostream>

typedef CSet<CString, LPCTSTR> CStringSet;

int main()
{
	CStringSet css;
	css.Add("Apples");
	css.Add("Bananas");
	css.Add("Oranges");
	POSITION pos = css.GetStartPosition();
	CString sKey;
	while (pos != NULL)
	{
		css.GetNextAssoc(pos, sKey);
		std::wcout << sKey.GetString() << "\n";
	}
	std::cin.get();
}

