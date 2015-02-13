#pragma once

#include <atomic> 

namespace cw{
    namespace concurrency{
        template<typename T>
        class atomical_property{
        public:
            atomical_property(){
                property_value.store(0);
            }

            T operator=(){
                return property_value.load();
            }

            void operator=(T other){
                property_value.store(other);
            }

        private:
            std::atomic<T> property_value;
        };
    }
}
