#pragma once

namespace Devel {
    /**
     * @brief Singleton class
     * @tparam T Type of the Singleton class
     *
     * Ensures that only one object of a class exists.
     *
     * <b>Example</b>
     *
     * The class must be derived from this class.
     * @code{.c}
        class CSingletonClass : public Devel::CSingleton<CSingletonClass>	// Derive the Singleton class
        {
            friend class CSingleton<Devel::CSingletonClass>;		        // For access to constructor
        private:
            CSingletonClass() {}					                        // Private constructor!
            virtual ~CSingletonClass() {}
        public:
            bool initialize();						                        // Example function!
        };

        Then you can use it like that:
        CSingletonClass::instance()->initialize();	                        // Function initialize just an example!
        @endcode
    */
    template<typename T>
    class CSingleton {
    protected:
        /**
         * @brief Constructor
         *
         * Protected constructor to prevent instantiation.
         *
        */
        CSingleton() = default;
        CSingleton(const CSingleton &) = delete;
        CSingleton &operator=(const CSingleton &) = delete;
        virtual ~CSingleton() = default;

    public:
        /**
         * @brief Get the instance of the Singleton class
         * @return Instance of the Singleton class
         *
         * Returns the instance of the Singleton class.
         *
         * If the instance does not exist, it will be created.
         *
        */
        static T *instance() {
            static T s_oInstance;
            return &s_oInstance;
        }
    };
}