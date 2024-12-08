#ifndef MEMFUN_ADAPTER_H
#define MEMFUN_ADAPTER_H
template <typename RetType, typename ClassType, typename ArgType>
class MFA_1arg {
		/* ??? */
	public:
		MFA_1arg( RetType (ClassType::*_pointer) (ArgType) ) : /* ??? */ {}
		/* ??? */ operator() ( /* ??? */ ) const {
			return /* ??? */; //call
		}
};

//helper functions
//for non-const member function
template <typename RetType, typename ClassType, typename ArgType>
MFA_1arg<RetType,ClassType,ArgType> mfp_1arg(RetType (ClassType::*pointer) (ArgType) ) { 
	return /* ??? */; 
}
#endif
