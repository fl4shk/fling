#ifndef src_frost_program_class_hpp
#define src_frost_program_class_hpp

// src/frost_program_class.hpp

#include "misc_includes.hpp"
#include "frost_module_class.hpp"
#include "frost_package_class.hpp"

namespace frost_hdl
{

// Contains the partially-processed contents of a program written in
// Frost HDL, for the first set of passes that the "ParseTreeVisitor" goes through.
// This is simply used as a container.
class FrostProgram
{
public:		// variables
	//// Built-in "FrostLhsType"s
	//FrostLhsTypeTable frost_lhs_type_table;

	//// Built-in "FrostFullType"s
	//FrostFullTypeTable frost_full_type_table;

	// "FrostModule"s are always global anyway
	FrostModuleTable frost_module_table;
	FrostModule* curr_frost_module = nullptr;

	// "FrostPackage"s are always global anyway
	FrostPackageTable frost_package_table;
	FrostPackage* curr_frost_package = nullptr;

public:		// functions
	FrostProgram();

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostProgram);
	virtual ~FrostProgram();
};

} // namespace frost_hdl

#endif		// src_frost_program_class_hpp
