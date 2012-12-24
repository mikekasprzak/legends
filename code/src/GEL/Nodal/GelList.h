// - ------------------------------------------------------------------------------------------ - //
// List - Double Linked List //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Nodal_GelList_H__
#define __Library_Nodal_GelList_H__
// - ------------------------------------------------------------------------------------------ - //
template< class T >
class GelListNode {
public:
	GelListNode<T>* Prev;
	GelListNode<T>* Next;
	
	T Data;
};
// - ------------------------------------------------------------------------------------------ - //
template< class T >
class GelList {
	GelListNode<T>* Start;
	GelListNode<T> End;			// Not a Pointer. Actually Instanced. //
	
	size_t Count;
public:
	GelList() :
		Start( &End ),
		Count( 0 )
	{
		End.Prev = &End;
		End.Next = &End;
	}
	
public:
	inline size_t Size() const {
		return Count;
	}
	
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Nodal_GelList_H__ //
// - ------------------------------------------------------------------------------------------ - //
