//--------------------------------------------------------------------------
// Copyright (C) 2020-2025 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------

// hash_lru_cache.h author davis mcpherson davmcphe@cisco.com

#ifndef HASH_LRU_CACHE_H
#define HASH_LRU_CACHE_H

#include "hash_defs.h"

class HashLruCache
{
public:
    HashLruCache();

    void insert(snort::HashNode*);
    void touch(snort::HashNode*);
    void remove_node(snort::HashNode*);

    snort::HashNode* get_lru_node()
    {
        cursor = tail;
        return cursor;
    }

    snort::HashNode* get_next_lru_node()
    {
        if ( cursor )
            cursor = cursor->gprev;
        return cursor;
    }

    snort::HashNode* get_current_node()
    { return cursor; }

    void* get_mru_user_data()
    { return ( head ) ? head->data : nullptr; }

    void* get_lru_user_data()
    { return ( tail ) ? tail->data : nullptr; }

    snort::HashNode* remove_lru_node()
    {
        snort::HashNode* hnode = tail;
        if ( hnode )
            remove_node(hnode);

        return hnode;
    }

    snort::HashNode* get_walk_node()
    {
        if ( tail )
            walk_cursor = tail->gprev;
        return tail;
    }

    snort::HashNode* get_next_walk_node()
    {
        snort::HashNode* rnode = walk_cursor;
        if ( walk_cursor )
            walk_cursor = walk_cursor->gprev;
        return rnode;
    }

    inline uint64_t get_node_count()
    { return node_count; }

private:
    snort::HashNode* head = nullptr;
    snort::HashNode* tail = nullptr;
    snort::HashNode* cursor = nullptr;
    //walk_cursor is used to traverse from tail to head while dumping the flows.
    snort::HashNode* walk_cursor = nullptr;
    uint64_t node_count = 0;
};

#endif

