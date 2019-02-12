#pragma once

#define CSET_VALUE_PRESENT ((LPVOID)1)

#include <afxwin.h>

template<class KEY, class ARG_KEY = const KEY&>class CSet : public CObject
{
public:
	CSet(INT_PTR nBlockSize = 10);
	BOOL Add(KEY key);
	BOOL Contains(KEY key);
	BOOL Remove(KEY key);
	void RemoveAll();
	BOOL IsEmpty() const;
	INT_PTR GetCount() const;
	INT_PTR GetSize() const;
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, KEY& rKey) const;
	void Serialize(CArchive&);
protected:
	CMap<KEY, ARG_KEY, LPVOID, LPVOID> m_Map;
};


template<class KEY, class ARG_KEY>
inline CSet<KEY, ARG_KEY>::CSet(INT_PTR nBlockSize):m_Map(nBlockSize)
{
}

template<class KEY, class ARG_KEY>
inline BOOL CSet<KEY, ARG_KEY>::Add(KEY key)
{
	LPVOID value;
	if (m_Map.Lookup(key, value))
	{
		return FALSE;
	}
	m_Map.SetAt(key, CSET_VALUE_PRESENT);
	return TRUE;
}

template<class KEY, class ARG_KEY>
inline BOOL CSet<KEY, ARG_KEY>::Contains(KEY key)
{
	LPVOID value;
	return m_Map.Lookup(key, value);
}

template<class KEY, class ARG_KEY>
inline BOOL CSet<KEY, ARG_KEY>::Remove(KEY key)
{
	return m_Map.RemoveKey(key);
}

template<class KEY, class ARG_KEY>
inline void CSet<KEY, ARG_KEY>::RemoveAll()
{
	m_Map.RemoveAll();
}

template<class KEY, class ARG_KEY>
inline BOOL CSet<KEY, ARG_KEY>::IsEmpty() const
{
	return m_Map.IsEmpty();
}

template<class KEY, class ARG_KEY>
inline INT_PTR CSet<KEY, ARG_KEY>::GetCount() const
{
	return m_Map.GetCount();
}

template<class KEY, class ARG_KEY>
inline INT_PTR CSet<KEY, ARG_KEY>::GetSize() const
{
	return m_Map.GetSize();
}

template<class KEY, class ARG_KEY>
inline POSITION CSet<KEY, ARG_KEY>::GetStartPosition() const
{
	return m_Map.GetStartPosition();
}

template<class KEY, class ARG_KEY>
inline void CSet<KEY, ARG_KEY>::GetNextAssoc(POSITION & rNextPosition, KEY & rKey) const
{
	LPVOID dummy = NULL;
	m_Map.GetNextAssoc(rNextPosition, rKey, dummy);
}

template<class KEY, class ARG_KEY>
inline void CSet<KEY, ARG_KEY>::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CObject::Serialize(ar);
	m_Map.Serialize(ar);
}