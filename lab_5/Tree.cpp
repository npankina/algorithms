/*
* This file is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) [2024] [Natal'ya Pankina].
 */

#include "Tree.h"

//------------------------------------------------------------
Tree::Tree(void)
{}
//------------------------------------------------------------
Tree::~Tree(void)
{}
//------------------------------------------------------------
Tree::Tree(const data_t &d)
{}
//------------------------------------------------------------
Tree::Tree(const std::initializer_list<data_t> &t)
{}
//------------------------------------------------------------
Tree::Tree(const Tree &other) // copy ctor
{}
//------------------------------------------------------------
Tree::Tree(Tree &&other) noexcept // move ctor
{}
//------------------------------------------------------------
Tree &Tree::operator=(Tree &&other) noexcept  // move assign
{}
//------------------------------------------------------------
Tree &Tree::operator=(const Tree &other) // copy assign
{}
//------------------------------------------------------------
bool Tree::empty() const noexcept
{}
//------------------------------------------------------------
size_t Tree::count() const noexcept // -- количенство элементов --
{}
//------------------------------------------------------------
size_t Tree::height() const noexcept  // -- высота дерева --
{}
//------------------------------------------------------------
Tree::data_t Tree::find(const key_t &key) const
{}
//------------------------------------------------------------
bool Tree::insert(const key_t &key, const value_t &v)
{}
//------------------------------------------------------------
bool Tree::insert(const data_t &d)
{}
//------------------------------------------------------------
bool Tree::replace(const key_t &key, const value_t &v)
{}
//------------------------------------------------------------
bool Tree::erase(const key_t &key) // удалить указанный
{}
//------------------------------------------------------------
void Tree::clear() // удалить все
{}
//------------------------------------------------------------
void Tree::swap(Tree &t) noexcept
{}
//------------------------------------------------------------