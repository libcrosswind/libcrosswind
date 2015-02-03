#pragma once 

#include <Crosswind/non_public/flag_set.hpp> //@TODO move to util maybe?


namespace cw{
	namespace util{

	    class flag_container{
        public:
            flag_container(){

                container_confirmation_method = [](){
                    return [](int test_flags){
                        return false;
                    };

                }();
            }


            template<typename T>
            void set(T flags){	

                container_confirmation_method = [&flags](){
                    std::shared_ptr<non_public::flag_set<T> > flag_set(new non_public::flag_set<T>(flags));

                    return [flag_set](int test_flags){
                        return flag_set->test((T)test_flags);
                    };

                }();
            }

            bool contains(int flags){
                return container_confirmation_method(flags);
            }

        protected:
            std::function<bool(int)> container_confirmation_method;
        };

	}
}