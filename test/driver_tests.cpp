#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <sstream>
#include <string.h>

#include "../include/mpool.h"
#include "mempool_common.h"

using namespace mp;

int main()
{
	// static constexpr size_t HEADER_SZ = sizeof( mp::SLPool<BLK_SIZE>::Header );

	const short BLOCK_SIZE=24;
    using byte = char; // 1 byte
    const short n_blocks(2); // How many blocks per chunk
    const short chunk( n_blocks*BLOCK_SIZE ); // Each chunk ideally should have 1 or more blocks.
    // const short header_sz_t (mp::SLPool<BLOCK_SIZE>::HEADER_SZ)
    // const short area_metainfo( mp::SLPool<BLOCK_SIZE>::TAG_SZ + header_sz_t );

    // We need MP large enough to hold 7 separate chunks of memory.
    const short n_chunks(7); // 7 pieces of 32 bytes

    std::cout << ">>> My tests\n\n";

    std::cout << ">>> Using .Allocate and .Free:\n";
    mp::SLPool<BLOCK_SIZE> q( sizeof(byte) * chunk * n_chunks );
    std::cout << "Allocating 3 int... ";
    int * int_ptr = (int *)q.Allocate( sizeof(int) * 3 );
    std::cout << "Done!\n";  
    int_ptr[0] = 0;
    int_ptr[1] = 2;
    int_ptr[2] = 6;
    std::cout << int_ptr[0] << " " << int_ptr[1] << " " << int_ptr[2] << " = 0 2 6"<< std::endl;
    std::cout << "Delleting... ";
    q.Free(int_ptr);
    std::cout << "Done!\n";

    std::cout << ">>> Using new and delete:\n";
    mp::SLPool<BLOCK_SIZE> r( sizeof(byte) * chunk * n_chunks );
    std::cout << "Allocating 3 int using new... ";
    int * int_ptr2 = new (r) int[ 3 ];
    std::cout << "Done!\n";  
    int_ptr2[0] = 0;
    int_ptr2[1] = 2;
    int_ptr2[2] = 6;
    std::cout << int_ptr2[0] << " " << int_ptr2[1] << " " << int_ptr2[2] << " = 0 2 6"<< std::endl;
    std::cout << "Delleting using delete... ";
    delete [] int_ptr2;
    std::cout << "Done!\n";



    std::cout << "\n>>> Begining DATA INTEGRITY tests...\n\n";

    {
        // Set up 7 chunks of data.
        // We decrease the area metainfo so we might suppport a single reserved area
        // with the size of the entire pool.
        // mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
        // std::cout << p << std::endl;

        // bool passed(false);
        // byte*  vet[ n_chunks ];  // Array of chunk pointer to be allocated.

        // Define the chunk length so that it corresponds to two blocks of memory.
        // size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

        // // Reference value.
        // // Fill up the cha array with "01234567890123...."
        // std::ostringstream oss;
        // auto j(0u);
        // while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
        //     oss << (j++%10);

        // // Fill up the MP.
        // for( auto i(0) ; i < n_chunks ; ++i )
        // {
        //     vet[i] = new (p) byte [chunk_len];
        //     strcpy( vet[i], oss.str().c_str() );
        // }

        // // Test each position.
        // for( auto i(0) ; i < n_chunks ; ++i )
        // {
        //     passed = strcmp( oss.str().c_str(), vet[i] ) == 0;
        //     if ( not passed ) break;
        // }

        // std::cout << ">>> Testing pool integrity after writing the entire pool... ";
        // std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
    }

   //  {
   //      // Set up 7 chunks of data.
   //      // We decrease the area metainfo so we might suppport a single reserved area
   //      // with the size of the entire pool.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
   //      //std::cout << p << std::endl;

   //      bool passed(false);
   //      byte*  vet[ n_chunks ];  // Array of chunk pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Reference value.
   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Reference value.
   //      std::string reference_a = oss.str();
   //      std::string reference_b( reference_a );
   //      std::random_device rd;
   //      std::mt19937 g(rd());
   //      std::shuffle(reference_b.begin(), reference_b.end(), g);


   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          strcpy( vet[i], reference_a.c_str() );
   //      }


   //      // Overwriting the even positions within the array of strings.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 == 0 )
   //              strcpy( vet[i], reference_b.c_str() );
   //      }

   //      // Test each position.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i%2 == 0 )
   //              passed = strcmp( reference_b.c_str(), vet[i] ) == 0;
   //          else
   //              passed = strcmp( reference_a.c_str(), vet[i] ) == 0;
   //          if ( not passed ) break;
   //      }

   //      std::cout << ">>> Testing pool integrity after interleaved writing... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }

   //  {
   //      // Set up 7 chunks of data.
   //      // We decrease the area metainfo so we might suppport a single reserved area
   //      // with the size of the entire pool.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
   //      //std::cout << p << std::endl;

   //      bool passed(false);
   //      byte*  vet[ n_chunks ];  // Array of chunk pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Reference value.
   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      std::string reference_a( oss.str());

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          strcpy( vet[i], reference_a.c_str() );
   //      }

   //      // Write a different value on odd locations.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 == 0 )
   //              delete [] vet[i];
   //      }

   //      // Test each position against references.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 != 0 )
   //          {
   //              passed = strcmp( reference_a.c_str(), vet[i] ) == 0;
   //              if ( not passed ) break;
   //          }
   //      }

   //      std::cout << ">>> Testing pool integrity after deleting even interleaved areas... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }
   //  {
   //      // Set up 7 chunks of data.
   //      // We decrease the area metainfo so we might suppport a single reserved area
   //      // with the size of the entire pool.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
   //      //std::cout << p << std::endl;

   //      bool passed(false);
   //      byte*  vet[ n_chunks ];  // Array of chunk pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Reference value.
   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      std::string reference_a( oss.str() );

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          strcpy( vet[i], reference_a.c_str() );
   //      }

   //      // Write a different value on odd locations.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 != 0 )
   //              delete [] vet[i];
   //      }

   //      // Test each position against references.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 == 0 )
   //          {
   //              passed = strcmp( reference_a.c_str(), vet[i] ) == 0;
   //              if ( not passed ) break;
   //          }
   //      }

   //      std::cout << ">>> Testing pool integrity after deleting odd interleaved areas... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }
   //  {
   //      // Set up 7 chunks of data.
   //      // We decrease the area metainfo so we might suppport a single reserved area
   //      // with the size of the entire pool.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
   //      //std::cout << p << std::endl;

   //      bool passed(false);
   //      byte*  vet[ n_chunks ];  // Array of chunk pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Reference value.
   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Reference value.
   //      std::string reference_a = oss.str();
   //      std::string reference_b( reference_a );
   //      std::random_device rd;
   //      std::mt19937 g(rd());
   //      std::shuffle(reference_b.begin(), reference_b.end(), g);

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          strcpy( vet[i], reference_a.c_str() );
   //      }

   //      // Free memory of odd positions with the array.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 != 0 )
   //              delete [] vet[i];
   //      }

   //      // Reallocate the odd locations.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 != 0 )
   //          {
   //              vet[i] = new (p) byte [chunk_len];
   //              // new value
   //              strcpy( vet[i], reference_b.c_str() );
   //          }
   //      }

   //      // Test each position against references.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          if ( i % 2 == 0 )
   //              passed = strcmp( reference_a.c_str(), vet[i] ) == 0;
   //          else
   //              passed = strcmp( reference_b.c_str(), vet[i] ) == 0;
   //          if ( not passed ) break;
   //      }

   //      std::cout << ">>> Testing pool integrity after deleting and realocating interleaved areas... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }


   //  // -------------------------------------------------------------------------------------------------------
   //  // -------------------------------------------------------------------------------------------------------
   //  // -------------------------------------------------------------------------------------------------------
  	// // -------------------------------------------------------------------------------------------------------
   //  // -------------------------------------------------------------------------------------------------------
   //  // -------------------------------------------------------------------------------------------------------
  	// // -------------------------------------------------------------------------------------------------------
   //  // -------------------------------------------------------------------------------------------------------
   //  // -------------------------------------------------------------------------------------------------------

    std::cout << ">>> Begining LIST INTEGRITY tests...\n\n";

    {
        // Set up 7 chunks of data.
        // We decrease the area metainfo so we might suppport a single reserved area
        // with the size of the entire pool.
        mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
        //std::cout << p << std::endl;

        auto passed(true);
        byte *temp;
        try {
            temp = new (p) byte[ sizeof(byte)*chunk*n_chunks ];
        }
        catch( const std::bad_alloc & e )
        {
            passed = false;
        }
        catch( const std::runtime_error & e )
        {
            passed = false;
        }
        std::cout << ">>> Allocating a single block with length equal to the entire pool size... ";
        std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
        delete [] temp;
    }


    // {
    //     // Set up 7 chunks of data.
    //     // We decrease the area metainfo so we might suppport a single reserved area
    //     // with the size of the entire pool.
    //     mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks );
    //     //std::cout << p << std::endl;

    //     bool passed(false);
    //     byte*  vet[ n_chunks ];  // Array of chunk pointer to be allocated.

    //     // Define the chunk length so that it corresponds to two blocks of memory.
    //     size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );
    //     //std::cout << ">> individual chunk length: " << chunk_len << std::endl;

    //     // Fill up the cha array with "01234567890123...."
    //     std::ostringstream oss;
    //     auto j(0u);
    //     while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
    //         oss << (j++%10);

    //     // Fill up the MP.
    //     for( auto i(0) ; i < n_chunks ; ++i )
    //     {
    //         vet[i] = new (p) byte [chunk_len];
    //         strcpy( vet[i], oss.str().c_str() );
    //     }
    //     //std::cout << p << std::endl;

    //     // Request an extra byte to invoke an exception (overflow).
    //     byte * temp(nullptr);
    //     try {
    //         temp = new (p) byte[ chunk_len ];
    //     }
    //     catch( std::runtime_error & e )
    //     {
    //         passed = true;
    //     }
    //     catch( std::bad_alloc & e )
    //     {
    //         passed = true;
    //     }

    //     std::cout << ">>> Testing pool overflow... ";
    //     std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
    //     // \e[1m text in bold \e[0m
    //     // \e[1m turn on bold
    //     // \e[0m turn off bold
    //     // 32 -> green
    //     // 21 -> red
    // }

   //  {
   //      // Set up 7 chunks of data.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks - area_metainfo );
   //      //std::cout << p << std::endl;

   //      byte*  vet[ n_chunks ];  // Array of byte pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          strcpy( vet[i], oss.str().c_str() );
   //          //std::cout << ">> vet[" << i << "] = " << vet[i] << std::endl;
   //      }

   //      /*
   //       * Freeing up target 'x'.
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       * | L | R | L | x | L | R | L |  ===>  | L | R |     L     | R | L |
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
   //       */

   //      // Set up initial condition.
   //      delete [] vet[0];
   //      delete [] vet[2];
   //      delete [] vet[4];
   //      delete [] vet[6];
   //      std::cout << p << std::endl;
   //      delete [] vet[3];
   //      //std::cout << p << std::endl;

   //      // Request a memory with size equal to the free blocks just combined.
   //      auto passed(true);
   //      try {
   //          // If the deletion went weel, we should be have a contiguous 6-block-length area.
   //          // Therefore, we should be able to successfully request back a single 6-block-length area.
   //          size_t new_size( 6*SLPool<BLOCK_SIZE>::BLK_SZ - SLPool<BLOCK_SIZE>::TAG_SZ - SLPool<BLOCK_SIZE>::HEADER_SZ );
   //          vet[3] = new (p) byte [ new_size ];
   //          // Fill up the char with "01234567890123...."
   //          std::ostringstream oss;
   //          auto j(0u);
   //          while( j < new_size-1 ) // Remember we have to reserve one extra space for the '\0'.
   //              oss << (j++%10);
   //          strcpy( vet[3], oss.str().c_str() );
   //      }
   //      catch( std::runtime_error & e )
   //      {
   //          passed = false;
   //      }
   //      catch( std::bad_alloc & e )
   //      {
   //          passed = false;
   //      }

   //      delete [] vet[1];
   //      delete [] vet[3];
   //      delete [] vet[5];

   //      std::cout << ">>> Testing pool merging 3 contiguous free areas: L R L => L L L... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }
    
   //  {
   //      // Set up 7 chunks of data.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks - area_metainfo );
   //      //std::cout << p << std::endl;

   //      byte*  vet[ n_chunks ];  // Array of byte pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          // Fill up the char with "01234567890123...."
   //          strcpy( vet[i], oss.str().c_str() );
   //          //std::cout << ">> vet[" << i << "] = " << vet[i] << std::endl;
   //      }

   //      /*
   //       * Teste #2
   //       *
   //       * Freeing up target 'x'.
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       * | R | L | R | x | R | L | R |  ===>  | R | L | R | L | R | R | L |
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
   //       */

   //      // Set up initial test condition.
   //      delete [] vet[1];
   //      delete [] vet[5];
   //      //std::cout << p << std::endl;
   //      delete [] vet[3];
   //      //std::cout << p << std::endl;

   //      auto passed(true);
   //      try {
   //          // If the deletion went well, we should be have a two free blocks at the middle.
   //          // Therefore, we should be able to successfully request back a single 2-block-length area.
   //          size_t new_size( 2*SLPool<BLOCK_SIZE>::BLK_SZ - SLPool<BLOCK_SIZE>::TAG_SZ - SLPool<BLOCK_SIZE>::HEADER_SZ );
   //          vet[1] = new (p) byte [ new_size ];
   //          vet[3] = new (p) byte [ new_size ];
   //          vet[5] = new (p) byte [ new_size ];
   //          // Fill up the char with "01234567890123...."
   //          std::ostringstream oss;
   //          auto j(0u);
   //          while( j < new_size-1 ) // Remember we have to reserve one extra space for the '\0'.
   //              oss << (j++%10);
   //          strcpy( vet[1], oss.str().c_str() );
   //          strcpy( vet[3], oss.str().c_str() );
   //          strcpy( vet[5], oss.str().c_str() );
   //      }
   //      catch( std::runtime_error & e )
   //      {
   //          passed = false;
   //      }
   //      catch( std::bad_alloc & e )
   //      {
   //          passed = false;
   //      }

   //      for ( auto i(0) ; i < n_chunks ; ++i )
   //          delete [] vet[i];

   //      std::cout << ">>> Testing pool after freeing area between 2 reserved areas:  R R R => R L R... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }

   //  {
   //      // Set up 7 chunks of data.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks - area_metainfo );

   //      byte*  vet[ n_chunks ];  // Array of byte pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          // Fill up the char with "01234567890123...."
   //          strcpy( vet[i], oss.str().c_str() );
   //          //std::cout << ">> vet[" << i << "] = " << vet[i] << std::endl;
   //      }

   //      /*
   //       * Teste #3
   //       *
   //       * Freeing up target 'x'.
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       * | R | L | R | x | L | R | L |  ===>  | R | L | R |   L   | R | L |
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
   //       */

   //      delete [] vet[1];
   //      delete [] vet[4];
   //      delete [] vet[6];
   //      //std::cout << p << std::endl;
   //      delete [] vet[3];
   //      //std::cout << p << std::endl;

   //      auto passed(true);
   //      try {
   //          // If the deletion went well, we should be have a two free blocks at the middle.
   //          // Therefore, we should be able to successfully request back a single 2-block-length area.
   //          size_t new_size( 4*SLPool<BLOCK_SIZE>::BLK_SZ - SLPool<BLOCK_SIZE>::TAG_SZ - SLPool<BLOCK_SIZE>::HEADER_SZ );
   //          vet[3] = new (p) byte [ new_size ];
   //          // Fill up the char with "01234567890123...."
   //          std::ostringstream oss;
   //          auto j(0u);
   //          while( j < new_size-1 ) // Remember we have to reserve one extra space for the '\0'.
   //              oss << (j++%10);
   //          strcpy( vet[3], oss.str().c_str() );
   //      }
   //      catch( std::runtime_error & e )
   //      {
   //          passed = false;
   //      }
   //      catch( std::bad_alloc & e )
   //      {
   //          passed = false;
   //      }

   //      std::cout << ">>> Testing pool after freeing area between a reserved and free areas:  R R L => R L L... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }
    
   //  {
   //      // Set up 7 chunks of data.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks - area_metainfo );

   //      byte*  vet[ n_chunks ];  // Array of byte pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          // Fill up the char with "01234567890123...."
   //          strcpy( vet[i], oss.str().c_str() );
   //          //std::cout << ">> vet[" << i << "] = " << vet[i] << std::endl;
   //      }

   //      /*
   //       * Teste #4
   //       *
   //       * Freeing up target 'x'.
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       * | L | R | L | x | R | L | R |  ===>  | L | R |   L   | R | L | R |
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
   //       */

   //      delete [] vet[0];
   //      delete [] vet[2];
   //      delete [] vet[5];
   //      //std::cout << p << std::endl;
   //      delete [] vet[3];
   //      //std::cout << p << std::endl;

   //      auto passed(true);
   //      try {
   //          // If the deletion went well, we should be have a two free blocks at the middle.
   //          // Therefore, we should be able to successfully request back a single 2-block-length area.
   //          size_t new_size( 4*SLPool<BLOCK_SIZE>::BLK_SZ - SLPool<BLOCK_SIZE>::TAG_SZ - SLPool<BLOCK_SIZE>::HEADER_SZ );
   //          vet[3] = new (p) byte [ new_size ];
   //          // Fill up the char with "01234567890123...."
   //          std::ostringstream oss;
   //          auto j(0u);
   //          while( j < new_size-1 ) // Remember we have to reserve one extra space for the '\0'.
   //              oss << (j++%10);
   //          strcpy( vet[3], oss.str().c_str() );
   //      }
   //      catch( std::runtime_error & e )
   //      {
   //          passed = false;
   //      }
   //      catch( std::bad_alloc & e )
   //      {
   //          passed = false;
   //      }

   //      std::cout << ">>> Testing pool after freeing area between a free and reserved areas:  L R R => L L R... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }

   //  {
   //      // Set up 7 chunks of data.
   //      mp::SLPool<BLOCK_SIZE> p( sizeof(byte) * chunk * n_chunks - area_metainfo );

   //      byte*  vet[ n_chunks ];  // Array of byte pointer to be allocated.

   //      // Define the chunk length so that it corresponds to two blocks of memory.
   //      size_t chunk_len( 2 * BLOCK_SIZE - area_metainfo );

   //      // Fill up the cha array with "01234567890123...."
   //      std::ostringstream oss;
   //      auto j(0u);
   //      while( j < chunk_len-1 ) // Remember we have to reserve one extra space for the '\0'.
   //          oss << (j++%10);

   //      // Fill up the MP.
   //      for( auto i(0) ; i < n_chunks ; ++i )
   //      {
   //          vet[i] = new (p) byte [chunk_len];
   //          // Fill up the char with "01234567890123...."
   //          strcpy( vet[i], oss.str().c_str() );
   //          //std::cout << ">> vet[" << i << "] = " << vet[i] << std::endl;
   //      }

   //      /*
   //       * Teste #4
   //       *
   //       * Freeing up target 'x'.
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       * | R | R | R | R | R | R | R |  ===>  |             L             |
   //       * +---+---+---+---+---+---+---+        +---+---+---+---+---+---+---+
   //       *   0   1   2   3   4   5   6            0   1   2   3   4   5   6
   //       */

   //      for( auto i(0) ; i < n_chunks ; i+=2 )
   //      {
   //          delete [] vet[i];
   //          // Print pool
   //          //std::cout << p << std::endl;
   //      }
   //      for( auto i(1) ; i < n_chunks ; i+=2 )
   //      {
   //          delete [] vet[i];
   //          // Print pool
   //          //std::cout << p << std::endl;
   //      }
   //      auto passed(true);
   //      try {
   //          // If the deletion went well, we should be have a two free blocks at the middle.
   //          // Therefore, we should be able to successfully request back a single 2-block-length area.
   //          size_t new_size( 14*SLPool<BLOCK_SIZE>::BLK_SZ - SLPool<BLOCK_SIZE>::TAG_SZ - SLPool<BLOCK_SIZE>::HEADER_SZ );
   //          vet[3] = new (p) byte [ new_size ];
   //          // Fill up the char with "01234567890123...."
   //          std::ostringstream oss;
   //          auto j(0u);
   //          while( j < new_size-1 ) // Remember we have to reserve one extra space for the '\0'.
   //              oss << (j++%10);
   //          strcpy( vet[3], oss.str().c_str() );
   //      }
   //      catch( std::runtime_error & e )
   //      {
   //          passed = false;
   //      }
   //      catch( std::bad_alloc & e )
   //      {
   //          passed = false;
   //      }

   //      std::cout << ">>> Testing pool after freeing the entire pool: R R R R R R R => L... ";
   //      std::cout << (passed ? "\e[1;35mpassed!\e[0m" : "\e[1;31mfailed!\e[0m") << std::endl;
   //  }

    return EXIT_SUCCESS;
}