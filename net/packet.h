#ifndef NET_PACKETH
#define NET_PACKETH

#include <stdint.h>
#include <stddef.h>
#include "proto.h"

namespace net
{
namespace packet
{
//           packet
//--------------------------------
//|   0 1   |   2 3  | size - 2  |
//|get_proto|get_size|           |
//--------------------------------
//|    get_header    | get_data  |
//--------------------------------
//|            get_all           |
//--------------------------------
#pragma pack(push)
#pragma pack(1)
class header
{
protected:
const uint16_t          m_proto;
uint16_t                m_size;

public:
inline                  header(const proto::enum_proto p) throw();
inline                  header(const proto::enum_proto p, const size_t size) throw();
inline  const header*   get_header() const throw();
inline  const proto     get_proto() const throw();
inline  const size_t    get_size() const throw();      
};
#pragma(pop)

#pragma pack(push)
#pragma pack(1)
template <class T>
class fixed_size:
    private header,
    public T
{
public:
using header::get_header;
using header::get_proto;
using header::get_size;

typedef fixed_size<T>   base;

inline                  fixed_size(const proto::enum_proto p) throw();
inline  const void*     get_data() const throw();
inline  const void*     get_all() const throw();
};
#pragma pack(pop)

//---- class header methods
header::header(const proto::enum_proto p) throw():
    m_proto( (uint16_t)p )
{
}

header::header(const proto::enum_proto p, const size_t size) throw():
    m_proto( (uint16_t)p ), m_size( size )
{
}

const header* header::get_header() const throw()
{
return this;
}

const proto header::get_proto() const throw()
{
return (proto::enum_proto)m_proto;
}

const size_t header::get_size() const throw()
{
return m_size;
}

//---- class fixed_size methods
template <class T>
fixed_size<T>::fixed_size(proto::enum_proto p) throw():
    header( p, sizeof(header) + sizeof(T) )
{
}

template <class T>
const void* fixed_size<T>::get_data() const throw()
{
T* userdata = this;
return userdata;
}

template <class T>
const void* fixed_size<T>::get_all() const throw()
{
return this;
}

}//namespace packet
}//namespace net

#endif

