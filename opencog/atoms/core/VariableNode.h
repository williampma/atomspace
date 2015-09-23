/*
 * opencog/atoms/core/VariableNode.h
 *
 * Copyright (C) 2015 OpenCog Foundation
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _OPENCOG_VARIABLE_NODE_H
#define _OPENCOG_VARIABLE_NODE_H

#include <opencog/atomspace/Handle.h>
#include <opencog/atomspace/Node.h>

namespace opencog
{
/** \addtogroup grp_atomspace
 *  @{
 */

class VariableNode : public Node
{
protected:

	VariableNode(Type,  const std::string& s,
	           TruthValuePtr tv = TruthValue::DEFAULT_TV(),
	           AttentionValuePtr av = AttentionValue::DEFAULT_AV());

	void init(void);

	WinkPtr _scope;		// weak link to avoid shared_ptr cycle

public:

	VariableNode(const std::string& s,
	           TruthValuePtr tv = TruthValue::DEFAULT_TV(),
	           AttentionValuePtr av = AttentionValue::DEFAULT_AV());

	VariableNode(Node&);

	void receive_scope(const Handle& scope_link);
	void remove_scope();
};

typedef std::shared_ptr<VariableNode> VariableNodePtr;
static inline VariableNodePtr VariableNodeCast(const Handle& h)
	{ AtomPtr a(h); return std::dynamic_pointer_cast<VariableNode>(a); }
static inline VariableNodePtr VariableNodeCast(AtomPtr a)
	{ return std::dynamic_pointer_cast<VariableNode>(a); }

// XXX temporary hack ...
#define createVariableNode std::make_shared<VariableNode>

/** @}*/
}

#endif // _OPENCOG_VARIABLE_NODE_H
