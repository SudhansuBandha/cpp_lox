#include "scanner/Token.h"

std::ostream& operator<<(std::ostream& os, const Token& token){
    os << token.type << " ";
    os << token.lexeme << " ";
   
    std::visit (
        [&](const auto& value){
            using T = std::decay_t<decltype(value)>;
            
            if constexpr (std::is_same_v<T, std::monostate>){
                os << "null";
            }else{
                os << value;
            }
        },
    token.literal
    );

    return os;
} 

