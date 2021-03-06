// 
// Scheme Environment
// 
// Author: Zhang Zhenghao (zhangzhenghao@hotmail.com)
//
#pragma once

#include <map>
#include <string>
#include <memory>
#include "garbage.hpp"

// Declare variable
class Variable;

// Constant values
extern const Variable VAR_NULL;
extern const Variable VAR_VOID;
extern const Variable VAR_TRUE;
extern const Variable VAR_FALSE;

class Environment: public GarbageObject
{
	// Type alias
	using string = std::string;
	using frame = std::map<string, Variable>;
	template <typename T> using shared_ptr = std::shared_ptr<T>;

	// Data member
	shared_ptr<Environment> encloseEnvPtr;
	shared_ptr<frame> framePtr;

	friend class Variable;

	// Add variables
	void addVars(const Variable& vars, const Variable& vals);

	// Find variable
	frame::iterator findVar(const string& var);

public:
	
	// Constructor for top-environment
	Environment(const Variable& vars = VAR_NULL, const Variable& vals = VAR_NULL);

	// Constructor for sub-environment
	Environment(const Variable& vars, const Variable& vals, const Environment& encloseEnv);

	// Assign variable
	Variable assignVariable(const Variable& var, const Variable& val);

	// Define variable
	Variable defineVariable(const Variable& var, const Variable& val);
	Variable defineVariable(const string& var, const Variable& val);

	// Lookup variable
	Variable lookupVariable(const Variable& var);

	// Finalize values
	void finalize() const override;

	// Scan and tag values in using
	void scan(int tag) const override;
};