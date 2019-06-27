#ifndef MEMPOOL_COMMON_H
#define MEMPOOL_COMMON_H

#include "mpool.h"

#include <memory>

void *operator new( size_t bytes, mp::StoragePool & p )
{
	mp::Tag * const tag = reinterpret_cast<mp::Tag *> (p.Allocate(bytes + sizeof(mp::Tag)));
	tag->pool = &p;

	return ( reinterpret_cast<void *>( tag+1U ) );
}

void *operator new[]( size_t bytes, mp::StoragePool & p )
{
	mp::Tag * const tag = reinterpret_cast<mp::Tag *> (p.Allocate(bytes + sizeof(mp::Tag)));
	tag->pool = &p;

	return ( reinterpret_cast<void *>( tag+1U ) );
}

void *operator new( size_t bytes )
{
	mp::Tag * const tag = reinterpret_cast<mp::Tag *> (std::malloc(bytes + sizeof(mp::Tag)));
	tag->pool = nullptr;

	return ( reinterpret_cast<void *>( tag+1U ) );
}

void *operator new[]( size_t bytes )
{
	mp::Tag * const tag = reinterpret_cast<mp::Tag *> (std::malloc(bytes + sizeof(mp::Tag)));
	tag->pool = nullptr;

	return ( reinterpret_cast<void *>( tag+1U ) );
}

void operator delete( void * arg )
{
	mp::Tag * const tag = reinterpret_cast< mp::Tag * >( arg ) - 1U;
	if( nullptr != tag->pool )
		tag->pool->Free(arg);
	else
		std::free( tag );
}

void operator delete[]( void * arg )
{
	mp::Tag * const tag = reinterpret_cast< mp::Tag * >( arg ) - 1U;
	if( nullptr != tag->pool )
		tag->pool->Free(arg);
	else
		std::free( tag );
}

#endif