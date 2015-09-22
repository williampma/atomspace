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

void VariableNode::receive_scope(const Handle& scope_link)
{
	Type t = scope_link->getType();
	if (not classserver().isA(t, LAMBDA_LINK))
		throw InvalidParamException(TRACE_INFO, "Expecting a LambdaLink");

	// XXX If eventually VariableNode should only be inside one scope
	// this could be changed to throw an exception
	if (_scope.lock())
		logger().warn("Reusing scoped VariableNode " + toShortString());

	_scope = LinkCast(scope_link);
}

/* ===================== END OF FILE ===================== */
