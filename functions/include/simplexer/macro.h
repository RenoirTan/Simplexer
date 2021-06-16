#ifndef SIMPLEXER_FUNCTIONS_MACRO_H
#   define SIMPLEXER_FUNCTIONS_MACRO_H

#   define SLF_DUMMYWRAPPER(token) token
#   define SLF_STRINGIFY(token) #token

#   define SLF_IFERROR(status) if (status)
#   define SLF_ERROR_RETURN(status) SLF_IFERROR(status) { return status; }

#   define SLF_NULL_RETURN(pointer, obj) if (pointer == NULL) { return obj; }

#endif