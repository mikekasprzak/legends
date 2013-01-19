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
	typedef GelListNode<T> tNode;
	
	tNode* First;
	tNode End;			// Not a Pointer. Actually Instanced. //
	
	size_t Count;
public:
	inline GelList() :
		First( &End ),
		Count( 0 )
	{
		End.Prev = &End;
		End.Next = &End;
	}
	
	inline ~GelList() {
		tNode* Node = Front();
		while ( Node != Back() ) {
			Node = Node->Next;
			delete Node->Prev;
		}
	}
	
	void Logs() {
		Log( "Front: %x  Back: %x  Size: %i", Front(), Back(), Size() );
		tNode* Node = Front();
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
	inline tNode* Front() {
		return First;
	}
	inline tNode* Back() {
		return &End;
	}

	inline void PushFront( const T& _Data ) {
		tNode* Node = new tNode( _Data );
		Node->Next = First;
		Node->Prev = &End;
		
		First = Node;

		// If the Last node is the End node (i.e. an empty list) //
		if ( End.Prev == &End ) {
			End.Prev = Node;
		}

		Node->Prev->Next = Node;
		Node->Next->Prev = Node;
		
		Count++;
	}
	
	inline void PushBack( const T& _Data ) {
		tNode* Node = new tNode( _Data );
		Node->Next = &End;
		Node->Prev = End.Prev;
		
		End.Prev = Node;
		
		// If the First node is the End node (i.e. an empty list) //
		if ( First == &End ) {
			First = Node;
		}

		Node->Prev->Next = Node;
		Node->Next->Prev = Node;
		
		Count++;
	}
	
	inline const T PopFront() {
		Assert( First == &End, "Empty List!" );
		
		T _Data = First->Data;
		tNode* Node = First;
		
		Node->Prev->Next = Node->Next;
		Node->Next->Prev = Node->Prev;
		
		First = Node->Next;
		
		// If the First node is the End (i.e. an empty list) //
		if ( First == &End ) {
			End.Prev = &End;
		}
		
		delete Node;
		Count--;
		return _Data;
	}
	
	inline const T PopBack() {
		Assert( First == &End, "Empty List!" );
		
		T _Data = End.Prev->Data;
		tNode* Node = End.Prev;
				
		Node->Prev->Next = Node->Next;
		Node->Next->Prev = Node->Prev;
		
		End.Prev = Node->Prev;
		
		// If the Prior node is the End (i.e. an empty list) //
		if ( End.Prev == &End ) {
			First = &End;
		}
		
		delete Node;
		Count--;
		return _Data;		
	}
	
	// DestNode should be part of this list //
	inline void Insert( T _Data, tNode* DestNode ) {
		tNode* Node = new tNode( _Data );
		Insert( Node, DestNode );
	}
	
	// Should not be used on 2 seperate lists (use Move instead) //
	inline void Insert( tNode* SrcNode, tNode* DestNode ) {
		SrcNode->Prev = DestNode->Prev;
		SrcNode->Next = DestNode;
		DestNode->Prev->Next = SrcNode;
		DestNode->Prev = SrcNode;
		
		if ( First == DestNode ) {
			First = SrcNode;
		}
		if ( DestNode == &End ) {
			End.Prev = SrcNode;
		}
		
		Count++;
	}
	
	inline const T _Remove( tNode* Node ) {
		Assert( Node == &End, "Cannot Remove End!" );
		
		Node->Prev->Next = Node->Next;
		Node->Next->Prev = Node->Prev;
		
		if ( First == Node ) {
			First = Node->Next;
		}
		if ( End.Prev == Node ) {
			End.Prev = Node->Prev;
		}	
			
		Count--;
		return Node->Data;
	}
	inline const T Remove( tNode* Node ) {
		T Ret = _Remove( Node );	
		delete Node;
		return Ret;
	}
	
	inline void Move( tNode* SrcNode, GelList* Dest, tNode* DestNode ) {
		Assert( SrcNode == &End, "Cannot Move End!" );
		_Remove( SrcNode );
		Dest->Insert( SrcNode, DestNode );
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline GelList<T>* new_GelList() {
	return new GelList<T>();
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void delete_GelList( GelList<T>* List ) {
	delete List;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Nodal_GelList_H__ //
// - ------------------------------------------------------------------------------------------ - //
