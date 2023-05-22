#pragma once
#include < assert.h >
#include < functional >
#include < algorithm >
template < typename T > class Node
{
public:
    Node(  T m_value  )
        : m_value(  m_value  )
        , m_prev( nullptr )
        , m_next( nullptr )
    {}
    T m_value;
    Node< T > * m_prev;
    Node< T > * m_next;
};

template < typename T > class Container
{
public:
    Container(  )
        : m_size( 0 )
        , m_first( nullptr )
        , m_last( nullptr ) {}
    Container( Container const &  origin ) : Container(  ) {
        * this = origin;
    }
    Container &  operator =( Container const &  origin ) {
        if ( this ==  & origin ) {
            return *this;
        }
        clear(  );
        origin.forEach( 
            [this]( T const &  elem ) {addm_last( elem ); }
         );
        return *this;
    }
    ~Container(  )
    {
        clear(  );
    }
    void push_front( T const &  m_value )
    {
        Node< T> * temp = new Node< T >( m_value );
        if ( is_empty(  ) ) {
            assert( m_last == nullptr );
            m_last = temp;
        }
        else{
            m_first->m_prev = temp;
        }
        temp->m_next = m_first;
        m_first = temp;
        ++m_size;
    }
    void push_back( T const &  m_value )
    {
        Node< T > * temp = new Node< T>( m_value );
        if ( is_empty(  ) ) {
            assert( m_first == nullptr );
            m_first = temp;
        }
        else{
            m_last->m_next = temp;
        }
        temp->m_prev = m_last;
        m_last = temp;
        ++m_size;
    }

    void pop_front(  )
    {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        Node< T > * remove;
        remove = m_first;
        m_first = remove->m_next;
        if ( m_first != nullptr ) {
            m_first->m_prev = nullptr;
        }
        else{
            m_last = nullptr;
        }
        delete remove;
        --m_size;
    }

    void reverse_list(  )
    {
        auto head = m_first;
        if ( m_first == nullptr ) {
            m_last->m_next = m_first;
            return;
        }
        auto cur = head;
        Node< T > * m_prev = nullptr;
        while ( cur != nullptr ) {
            auto temp = cur->m_next;
            cur->m_next = m_prev;
            m_prev = cur;
            cur = temp;
        }
        m_first = m_prev;
        return;
    }

    void pop_back(  )
    {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        Node< T > * remove;
        remove = m_last;
        m_last = remove->m_prev;
        if ( m_last != nullptr ) {
            m_last->m_next = nullptr;
        }
        else{
            m_first = nullptr;
        }
        delete remove;
        --m_size;
    }
    T pop(  ) {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        Node< T > * remove;
        remove = m_last;
        m_last = remove->m_prev;
        if ( m_last != nullptr ) {
            m_last->m_next = nullptr;
        }
        else{
            m_first = nullptr;
        }
        //delete remove;
        --m_size;
        return remove->m_value;
    }
    T get_first(  ) const {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        return m_first->m_value;
    }
    T get_last(  ) const {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        return m_last->m_value;
    }
    unsigned int get_count(  ) const {
        return m_size;
    }
    bool is_empty(  ) const {
        return ( this->get_count(  ) == 0 );
    }
    void clear(  ) {
        while ( !is_empty(  ) )
        {
            pop_front(  );
        }
    }
    void forEach( std::function< void( T &  ) > func ) {
        Node< T > * elem = m_first;
        while ( elem != nullptr ) {
            func( elem->m_value );
            elem = elem->m_next;
        }
    }
    void forEach( std::function< void( T const &  ) > func ) const {
        Node< T > * elem = m_first;
        while ( elem != nullptr ) {
            func( elem->m_value );
            elem = elem->m_next;
        }
    }
private:
    unsigned int m_size;
    Node< T > * m_first;
    Node< T > * m_last;
};














//#ifndef CONTAINER_H
//#define CONTAINER_H
//#include < memory>
//#include < iostream>
//#include < functional>
//const std::string EMPTY_CONTAINER = "Container is empty. Nothing to delete.";
//template< class Element>
//class Container {
//    struct Node {
//        Node(  Element const  &  x, Node* m_prev, Node* m_next  ) :data(  x  ), m_next(  m_next  ), m_prev(  m_prev  ) {}
////        Node(  Element &  &  x, Node* m_prev, Node* m_next  ) :data(  std::move(  x  )  ), m_next(  m_next  ), m_prev(  m_prev  ) {}
//        Element data;
//        Node* m_next;
//        Node* m_prev;
//    };
//public:
//    Container(  ) :m_m_prev(  nullptr  ), m_m_next(  nullptr  ), m_m_size(  0  ) {}
//    ~Container(  ) { clear(  ); }
//    Container(  Container const &  in  ) :m_m_prev(  nullptr  ), m_m_next(  nullptr  ), m_m_size(  0  ) { append( in ); }
//    Container(  Container &  &  in  ) :m_m_prev(  std::move(  in.m_m_prev  )  ), m_m_next(  std::move(  in.m_m_next  )  ), m_m_size(  std::move(  in.m_size  )  )
//    {
//        in.m_m_prev = in.m_m_next = nullptr;
//        in.m_m_size = 0;
//    }
//    Container &  operator=(  Container const &  in  ) {
//        if (   & in != this  ) {
//            clear(  );
//            append(  in  );
//        }
//        return *this;
//    }
//    Container &  operator=(  Container &  &  in  ) {
//        std::swap(  m_m_size, in.m_m_size  );
//        std::swap(  m_m_prev, in.m_m_prev  );
//        std::swap(  m_m_next, in.m_m_next  );
//        return *this;
//    }
//    void push_back(  Element const &  e  ) {
//        Node* s = new Node(  e, m_m_next, nullptr  );
//        if (  m_m_next  )
//            m_m_next->m_next = s;
//        else
//            m_m_prev = s;
//        m_m_next = s;
//        ++m_m_size;
//    }
//    void push_front(  Element const &  e  ) {
//        Node* s = new Node(  e, nullptr, m_m_prev  );
//        if (  m_m_prev  )
//            m_m_prev->m_prev = s;
//        else
//            m_m_next = s;
//        m_m_prev = s;
//        ++m_m_size;
//    }
//    //void push_back(  Element &  &  e  ) {
//    //    Node* s = new Node(  std::move(  e  ), m_m_next, nullptr  );
//    //    if (  m_m_next  )
//    //        m_m_next->m_next = s;
//    //    else
//    //        m_m_prev = s;
//    //    m_m_next = s;
//    //    ++m_m_size;
//    //}
//    //void push_front(  Element &  &  e  ) {
//    //    Node* s = new Node(  std::move(  e  ), nullptr, m_m_prev  );
//    //    if ( m_m_prev )
//    //        m_m_prev->m_prev = s;
//    //    else
//    //        m_m_next = s;
//    //    m_m_prev = s;
//    //    ++m_m_size;
//    //}
//    void pop_back(  ) {
//        if (  empty(  )  ) throw std::out_of_range(  EMPTY_CONTAINER  );
//        Node* cur = m_m_next;
//        m_m_next = cur->m_prev;
//        if (  m_m_next == nullptr  ) {
//            m_m_prev = nullptr;
//        }
//        else {
//            m_m_next->m_next = nullptr;
//        }
//        cur->m_prev = cur->m_next = nullptr;
//        delete cur;
//        --m_m_size;
//    }
//    void pop_front(  ) {
//        if (  empty(  )  ) throw std::out_of_range(  EMPTY_CONTAINER  );
//        Node* cur = m_m_prev;
//        m_m_prev = cur->m_next;
//        if (  m_m_prev == nullptr  ) {
//            m_m_next = nullptr;
//        }
//        else {
//            m_m_prev->m_prev = nullptr;
//        }
//        cur->m_prev = cur->m_next = nullptr;
//        delete cur;
//        --m_m_size;
//    }
//    Element &  get_back(  ) { return m_m_next->data; }
//    Element &  get_front(  ) { return m_m_prev->data; }
//    Element const &  get_back(  ) const { return m_m_next->data; }
//    Element const &  get_front(  ) const { return m_m_prev->data; }
//    typedef std::function<  bool(  Element &   ) > callable;
//    typedef std::function<  bool(  Element const &   ) > c_callable;
//    bool iterate(  c_callable const f  ) const {
//        Node* current = m_m_prev;
//        bool ret = true;
//        while (  current  &  &  ret  ) {
//            ret = f(  current->data  );
//            current = current->m_next;
//        }
//        return ret;
//    }
//    bool iterate(  callable const f  ) {
//        Node* current = m_m_prev;
//        bool ret = true;
//        while (  current  &  &  ret  ) {
//            ret = f(  current->data  );
//            current = current->m_next;
//        }
//        return ret;
//    }
//    void append(  Container const &  in  ) {
//        in.iterate(  [ this ](  Element const &  e  ) {
//            this->push_back(  e  );
//        }  );
//    }
//    void clear(  ) { while (  !empty(  )  ) pop_back(  ); }
//    m_size_t get_count(  ) const { return m_m_size; }
//    bool empty(  ) const { return m_m_prev == nullptr; }
//private:
//    Node* m_m_prev;
//    Node* m_m_next;
//    m_size_t m_m_size;
//};
//#endif // CONTAINER_H