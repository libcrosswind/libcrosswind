#pragma once

#include <EXTERN.h>
#include <perl.h>

#include <crosswind/interface/scripting/interpreter.hpp>
#include <crosswind/modules/functional/resource_property.hpp>

namespace cw{
namespace implementation{
namespace scripting{
	
	class perl_interpreter;

}// namespace scripting
}// namespace implementation
}// namespace cw

class cw::implementation::scripting::perl_interpreter{
public:
	perl_interpreter(){
			PERL_SYS_INIT3(nullptr, nullptr, nullptr);
			interpreter = perl_alloc();
			perl_construct(interpreter);
			PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
			perl_parse(interpreter, NULL, argc, argv, (char **)NULL);

	}

	virtual ~perl_interpreter(){
		perl_destruct(interpreter);
		perl_free(interpreter);
		PERL_SYS_TERM();
	}

	virtual void parse(const std::string& code){
	}

	virtual void run(){
		perl_run(interpreter);
	}

private:

 PerlInterpreter* interpreter; //The Perl interpreter
}// class perl_interpreter