#pragma once 

#include <string>
#include <cmath>

namespace cw {
    namespace crypto{
           //type must support size(), resize() and operator[]
            namespace base_64 {
               
            }


            namespace MD5{

                template<class type>
                void MD5(const type& input, type& hash) {
                    MD5_CTX context;
                    MD5_Init(&context);
                    MD5_Update(&context, &input[0], input.size());
                    
                    hash.resize(128/8);
                    MD5_Final((unsigned char*)&hash[0], &context);
                }
                template<class type>
                type MD5(const type& input) {
                    type hash;
                    MD5(input, hash);
                    return hash;
                }

            }

            namespace SHA1{



                template<class type>
                void SHA1(const type& input, type& hash) {
                    SHA_CTX context;
                    SHA1_Init(&context);
                    SHA1_Update(&context, &input[0], input.size());
                    
                    hash.resize(160/8);
                    SHA1_Final((unsigned char*)&hash[0], &context);
                }
                template<class type>
                type SHA1(const type& input) {
                    type hash;
                    SHA1(input, hash);
                    return hash;
                }
            }

            




            template<class type>
            void SHA256(const type& input, type& hash) {
                SHA256_CTX context;
                SHA256_Init(&context);
                SHA256_Update(&context, &input[0], input.size());
                
                hash.resize(256/8);
                SHA256_Final((unsigned char*)&hash[0], &context);
            }
            template<class type>
            type SHA256(const type& input) {
                type hash;
                SHA256(input, hash);
                return hash;
            }

            template<class type>
            void SHA512(const type& input, type& hash) {
                SHA512_CTX context;
                SHA512_Init(&context);
                SHA512_Update(&context, &input[0], input.size());
                
                hash.resize(512/8);
                SHA512_Final((unsigned char*)&hash[0], &context);
            }
            template<class type>
            type SHA512(const type& input) {
                type hash;
                SHA512(input, hash);
                return hash;
            }
    } 
} 