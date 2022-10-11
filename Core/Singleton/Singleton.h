#pragma once

/*
	Example/How to use:

	class CSingletonClass : public Devel::CSingleton<CSingletonClass>	// Derive the Singleton class
	{
		friend class CSingleton<Devel::CSingletonClass>;		// For access to constructor
	private:
		CSingletonClass() {}					// Private constructor!
		virtual ~CSingletonClass() {}

	public:
		bool initialize();						// Example function!
	};


	Then you can use it like that:

	CSingletonClass::instance()->initialize();	// Function initialize just an example!
*/

namespace Devel {
    template<typename T>
    class CSingleton {
    protected:
        CSingleton() = default;
        CSingleton(const CSingleton &) = delete;
        CSingleton &operator=(const CSingleton &) = delete;

        virtual ~CSingleton() = default;

    public:
        static T *instance() {
            static T s_oInstance;
            return &s_oInstance;
        }
    };
}