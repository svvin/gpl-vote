#include "rsa.h"

namespace gcrypt
{
namespace asymmetric
{
namespace rsa
{

pub_t::pub_t(const n_t& n, const e_t& e) throw(exception)
{
error_t err = gcry_sexp_build( &m_key.native(), NULL, "(public-key(rsa(n%m)(e%d)))", n.native(), e );
if ( GPG_ERR_NO_ERROR != err )
    {
    throw exception( err );
    }
}

void pub_t::fingerprint(int algo, void* dst, size_t size) const throw(exception)
{
sexp_t n = m_key.find( ext::const_c_str( "n" ) );
hash::make mh;
mh.enable( algo );
mh.write( n.data( 1 ) );
mh.read( algo, dst, size );
}

} //namespace rsa
} //namespace asymmetric
} //namespace gcrypt

