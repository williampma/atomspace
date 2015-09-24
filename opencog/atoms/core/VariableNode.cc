/*
 * VariableNode.cc
 *
 * Copyright (C) 2015 OpenCog Foundation
 *
 * Author: William Ma <https://github.com/williampma>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the
 * exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <opencog/atomspace/ClassServer.h>
#include <opencog/atoms/TypeNode.h>

#include "VariableNode.h"

using namespace opencog;


VariableNode::VariableNode(Type t, const std::string& s,
                       TruthValuePtr tv, AttentionValuePtr av)
	: Node(t, s, tv, av)
{
	if (not classserver().isA(t, VARIABLE_NODE))
		throw InvalidParamException(TRACE_INFO, "Expecting a VariableNode");

	init();
}

void VariableNode::init()
{

}

VariableNode::VariableNode(const std::string& s, TruthValuePtr tv, AttentionValuePtr av)
	: Node(VARIABLE_NODE, s, tv, av)
{
	init();
}

VariableNode::VariableNode(Node &n)
	: Node(n)
{
	Type t = n.getType();
	if (not classserver().isA(t, VARIABLE_NODE))
		throw InvalidParamException(TRACE_INFO, "Expecting a VariableNode");

	init();
}

/**
 * Set the scope of a VariableNode.
 *
 * @param A scoping LambdaLink
 */
void VariableNode::receive_scope(const Handle& scope_link)
{
	Type t = scope_link->getType();
	if (not classserver().isA(t, LAMBDA_LINK))
		throw InvalidParamException(TRACE_INFO, "Expecting a LambdaLink");

	// XXX If eventually VariableNode should only be inside one scope
	// this could be changed to throw an exception
	LinkPtr lptr = _scope.lock();
	if (lptr)
#ifdef VARIABLE_NODE_FULL_SUPPORT
		throw RuntimeException(TRACE_INFO, "Reusing scoped VariableNode");
#else
		logger().warn("Reusing scoped VariableNode "
		              + toShortString()
		              + "from old scope "
		              + lptr->toShortString()
		              + "to new scope "
		              + scope_link->toShortString());
#endif

	_scope = LinkCast(scope_link);
}

/**
 * Remove the scope of the VariableNode.
 */
void VariableNode::remove_scope()
{
	// XXX It is possible the caller is not the current
	// link set in _scope now, but not if VariableNode scope
	// uniqueness is fully supported.
	_scope.reset();
}

/**
 * Return the scoping link of the VariableNode.
 *
 * @return UNDEFINED if no scope, the link if scoped
 */
Handle VariableNode::get_scope()
{
	LinkPtr lptr = _scope.lock();
	if (not lptr)
		return Handle::UNDEFINED;

	return Handle(lptr);
}

/* ===================== END OF FILE ===================== */
