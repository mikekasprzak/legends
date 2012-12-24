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

public:
	inline GelListNode()
	{
	}
	
	inline GelListNode( const T& _Data ) :
		Data( _Data )
	{
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
template< class T >
class GelList {
	typedef GelListNode<T>* tNode;
	
	GelListNode<T>* First;
	GelListNode<T>* Last;
	GelListNode<T> End;			// Not a Pointer. Actually Instanced. //
	
	size_t Count;
public:
	inline GelList() :
		First( &End ),
		Last( &End ),
		Count( 0 )
	{
		End.Prev = &End;
		End.Next = &End;
	}
	
	inline ~GelList() {
		tNode Node = Front();
		while ( Node != Back() ) {
			Node = Node->Next;
			delete Node->Prev;
		}
	}
	
	void Logs() {
		Log( "Front: %x  Back: %x  Size: %i", Front(), Back(), Size() );
		tNode Node = Front();
		while ( Node != Back() ) {
			Node = Node->Next;
			Log( "* %x -- %i", Node->Prev, Node->Prev->Data );
		}
	}
	
public:
	inline size_t Size() const {
		return Count;
	}
	
public:
	inline GelListNode<T>* Front() {
		return First;
	}
	inline GelListNode<T>* Back() {
		return &End;
	}

	inline void PushFront( const T& _Data ) {
		GelListNode<T>* Node = new GelListNode<T>( _Data );
		Node->Next = First;
		Node->Prev = &End;
		
		First = Node;

		// If the Last node is the End node (i.e. an empty list) //
		if ( Last == &End ) {
			Last = Node;
		}

		Node->Prev->Next = Node;
		Node->Next->Prev = Node;
		
		Count++;
	}
	
	inline void PushBack( const T& _Data ) {
		GelListNode<T>* Node = new GelListNode<T>( _Data );
		Node->Next = &End;
		Node->Prev = Last;
		
		Last = Node;
		
		// If the First node is the End node (i.e. an empty list) //
		if ( First == &End ) {
			First = Node;
		}

		Node->Prev->Next = Node;
		Node->Next->Prev = Node;
		
		Count++;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Nodal_GelList_H__ //
// - ------------------------------------------------------------------------------------------ - //
