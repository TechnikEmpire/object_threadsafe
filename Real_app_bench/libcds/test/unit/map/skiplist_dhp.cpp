/*
    This file is a part of libcds - Concurrent Data Structures library

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2016

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     
*/

#include "test_skiplist_hp.h"

#include <cds/container/skip_list_map_dhp.h>

namespace {
    namespace cc = cds::container;
    typedef cds::gc::DHP gc_type;

    class SkipListMap_DHP : public cds_test::skiplist_map_hp
    {
    protected:
        typedef cds_test::skiplist_map_hp base_class;

        void SetUp()
        {
            struct map_traits: public cc::skip_list::traits
            {
                typedef cmp compare;
            };
            typedef cc::SkipListMap< gc_type, key_type, value_type > map_type;

            cds::gc::dhp::GarbageCollector::Construct( 16, map_type::c_nHazardPtrCount );
            cds::threading::Manager::attachThread();
        }

        void TearDown()
        {
            cds::threading::Manager::detachThread();
            cds::gc::dhp::GarbageCollector::Destruct();
        }
    };

    TEST_F( SkipListMap_DHP, compare )
    {
        typedef cc::SkipListMap< gc_type, key_type, value_type,
            typename cc::skip_list::make_traits<
                cds::opt::compare< cmp >
            >::type
        > map_type;

        map_type m;
        test( m );
    }

    TEST_F( SkipListMap_DHP, less )
    {
        typedef cc::SkipListMap< gc_type, key_type, value_type,
            typename cc::skip_list::make_traits<
                cds::opt::less< base_class::less >
            >::type
        > map_type;

        map_type m;
        test( m );
    }

    TEST_F( SkipListMap_DHP, cmpmix )
    {
        typedef cc::SkipListMap< gc_type, key_type, value_type,
            typename cc::skip_list::make_traits<
                cds::opt::less< base_class::less >
                ,cds::opt::compare< cmp >
            >::type
        > map_type;

        map_type m;
        test( m );
    }

    TEST_F( SkipListMap_DHP, item_counting )
    {
        struct map_traits: public cc::skip_list::traits
        {
            typedef cmp compare;
            typedef base_class::less less;
            typedef cds::atomicity::item_counter item_counter;
        };
        typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

        map_type m;
        test( m );
    }

    TEST_F( SkipListMap_DHP, backoff )
    {
        struct map_traits: public cc::skip_list::traits
        {
            typedef cmp compare;
            typedef base_class::less less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cds::backoff::yield back_off;
        };
        typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

        map_type m;
        test( m );
    }

    TEST_F( SkipListMap_DHP, stat )
    {
        struct map_traits: public cc::skip_list::traits
        {
            typedef cmp compare;
            typedef base_class::less less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cds::backoff::yield back_off;
            typedef cc::skip_list::stat<> stat;
        };
        typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

        map_type m;
        test( m );
    }

    TEST_F( SkipListMap_DHP, random_level_generator )
    {
        struct map_traits: public cc::skip_list::traits
        {
            typedef cmp compare;
            typedef base_class::less less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cc::skip_list::stat<> stat;
            typedef cc::skip_list::xorshift random_level_generator;
        };
        typedef cc::SkipListMap< gc_type, key_type, value_type, map_traits > map_type;

        map_type m;
        test( m );
    }

} // namespace
