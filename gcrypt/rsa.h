#ifndef CRYPT_RSAH
#define CRYPT_RSAH

#include <stddef.h>
#include <stdint.h>

#include "asymmetric.h"
#include "hash.h"

namespace gcrypt
{
namespace asymmetric
{
namespace rsa
{

class pub_t:
    public key_t,
    public pub_sign_key_t<pub_t>,
    public pub_crypt_key_t<pub_t>
{
public:
typedef hash::sha256_t  id_t;
typedef mpi_t           n_t;
typedef unsigned long   e_t;

protected:
                pub_t();
void            fingerprint(int algo, void* dst, size_t size) const throw(exception);

public:
                pub_t(const n_t& n, const e_t& e) throw(exception);
inline  id_t    fingerprint() const throw(exception);
template <int algo, class T, int size>
inline  void    fingerprint(hash::hash_t<algo,T,size>& hash) const throw(exception);
};

class priv_t:
    public pub_t,
    public priv_sign_key_t<priv_t>,
    public priv_crypt_key_t<priv_t>
{
public:
typedef smpi_t      p_t;
typedef smpi_t      q_t;

public:
    priv_t(const p_t& p, const q_t& q);
};

//inc
pub_t::id_t pub_t::fingerprint() const throw(exception)
{
id_t result;
fingerprint( result );
return result;
}

template <int algo, class T, int size>
void pub_t::fingerprint(hash::hash_t<algo,T,size>& hash) const throw(exception)
{
fingerprint( algo, &hash, hash::hash_t<algo,T,size>::static_size );
}

} //namespace rsa
} //namespace asymmetric
} //namespace crypt

#endif

