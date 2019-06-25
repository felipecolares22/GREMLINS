#ifndef MPOOL_H
#define MPOOL_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <string>
#include <sstream>
#include <string.h>

namespace mp
{
	class StoragePool
	{
	public:
		virtual ~StoragePool() {};
		virtual void* Allocate( size_t ) = 0;
		virtual void Free( void * ) = 0;
	}; // StoragePool class

	struct Tag
	{
		mp::StoragePool * pool;
	}; // Tag struct

	template < size_t BLK_SIZE=16 >
	class SLPool : public StoragePool
	{
	public:
		static constexpr size_t BLK_SZ = sizeof( mp::SLPool<BLK_SIZE>::Block ); //!< The block size in bytes.
		static constexpr size_t TAG_SZ = sizeof( mp::Tag ); //!< The Tag size in bytes (each reserved area has a tag).
		static constexpr size_t HEADER_SZ = sizeof( mp::SLPool<BLK_SIZE>::Header ); 

		struct Header
		{
			size_t m_length;
			Header() : m_length(0u) { };
		};

		struct Block: public Header
		{
			union
			{
				Block *m_next;
				char m_raw[ BLK_SIZE - sizeof(Header) ];
			};

			Block() : Header(), m_next( nullptr ) { };
		};

	private:
		unsigned int m_n_blocks;
		Block *m_pool;
		Block &m_sentinel;

	public:
		/// Constructor
		explicit SLPool( size_t num_blk )
			: m_n_blocks{ (unsigned int) std::ceil( (num_blk + sizeof( Header )) / BLK_SIZE ) + 1u },
			m_pool{ new Block[m_n_blocks] },
			m_sentinel{ m_pool[m_n_blocks - 1] }
		{
			this->m_pool[0].m_length = (m_n_blocks - 1);
			this->m_pool[0].m_next = nullptr;

			this->m_sentinel.m_next = this->m_pool;
			this->m_sentinel.m_length = 0;
		}

		// Destructor
		~SLPool()
		{ delete [] m_pool; }

		void * Allocate( size_t tot_size )
		{
			Block *fast = this->m_sentinel.m_next;
			Block *slow = &this->m_sentinel;
			size_t num_blocks = std::ceil( (tot_size + sizeof( Header ))/BLK_SIZE );

			while( fast != nullptr )
			{
				if(fast->m_length == num_blocks)
				{
					slow->m_next = fast->m_next;
					fast->m_length = num_blocks;
					return reinterpret_cast< void* >(reinterpret_cast< Header* > (fast) + (1U));
				}
				else if(fast->m_length > num_blocks)
				{
					slow->m_next = fast + num_blocks;
					slow->m_next->m_next = fast->m_next;
					slow->m_next->m_length = fast->m_length - num_blocks;
					fast->m_length = num_blocks;

					return reinterpret_cast< void* >(reinterpret_cast< Header* > (fast) + (1U));
				}
				else
				{
					slow = fast;
					fast = fast->m_next;
				}
			}

			throw std::bad_alloc();
		}

		void Free( void * ptr )
		{
			ptr = reinterpret_cast<Block *> (reinterpret_cast <Header *> (ptr) - (1U));

			Block * current = (Block *) ptr;
			Block * fast = this->m_sentinel.m_next;
			Block * slow = &this->m_sentinel;

			while(fast != nullptr)
			{
				if( (current - fast) < (current - slow) and (current - fast) > 0 )
				{
					slow = fast;
					fast = fast->m_next;
				}
				else
					break;
			}

			Block * pre = fast;
			Block * pos = fast->m_next;

			if(	(current - pre) == (long int)pre->m_length and (pos - current) == (long int)current->m_length )
			{
				pre->m_next = pos->m_next;
				pre->m_length = pre->m_length + current->m_length + pos->m_length;
			}
			else if( (current - pre) == (long int)pre->m_length )
			{
				pre->m_next = pos;
				pre->m_length = pre->m_length + current->m_length;
			}
			else if( (pos - current) == (long int)current->m_length )
			{
				pre->m_next = current;
				current->m_next = pos->m_next;
				current->m_length = current->m_length + pos->m_length;
			}
			else
			{
				current->m_next = pre->m_next;
				pre->m_next = current;
			}
		}

		friend std::ostream& operator<< (std::ostream& stream, const SLPool& obj)
		{
			stream << " operator << of SLPool Class is a WIP " << std::endl;
			
			return stream;
		} 

	}; // SLPool class
} //namespace mp

#endif