/////////////////////////////////////////////////////////////////////////////
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING //
// This file is generated by CIB and should not be edited.
// If CIB is run again the edited changes will go away for ever.
/////////////////////////////////////////////////////////////////////////////

#ifndef __CIB_$MODULE$_H__
#define __CIB_$MODULE$_H__

#include <map>

namespace _cib_ { namespace $MODULE$ {
    /**
     * \brief MetaInterface is just a map between unique id and function pointer.

     There is one instance of MetaInterface class for each exported classes.
     There will be cases when instance of this class will be created on adhoc basis
     mainly by client side glue code to provide callback mechanism to the library.
     */
    class MetaInterface
    {
    private:
        typedef std::map<int, void*> MethodIdToProcMap;
        MethodIdToProcMap methods;

    protected:
        /**
         * Creates the map between unique id and function pointer.
         * Derived class must implement it.
         */
        virtual void LoadMethods() {}

    public:
        void AddMethod(int funcCibId, void* proc)
        {
            methods[funcCibId] = proc;
        }
        void* GetMethod(int funcCibId)
        {
            if(methods.empty())
                LoadMethods();
            MethodIdToProcMap::const_iterator itr = methods.find(funcCibId);
            return itr != methods.end() ? itr->second : (void*) 0;
        }
    };
}}

#endif //__CIB_H__
