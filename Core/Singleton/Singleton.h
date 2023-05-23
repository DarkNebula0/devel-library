#pragma once

/// @namespace Devel
/// @brief A namespace for development related classes and functions.
namespace Devel {
    /// @class Devel::CSingleton
    /// @brief A class template for creating singleton classes.
    ///
    /// A singleton is a design pattern that restricts the instantiation of a class to a single instance.
    /// This is useful when exactly one object is needed to coordinate actions across the system.
    /// @tparam T The type that will be a singleton.
    ///
    /// <b>Example</b>
    ///
    /// A class must derive from this class in order to become a singleton.
    /// @code{.cpp}
    /// class CSingletonClass : public Devel::CSingleton<CSingletonClass>  // Derive the Singleton class
    /// {
    ///     friend class CSingleton<Devel::CSingletonClass>;                 // For access to constructor
    /// private:
    ///     CSingletonClass() {}                                            // Private constructor!
    ///     virtual ~CSingletonClass() {}
    /// public:
    ///     bool initialize();                                              // Example function!
    /// };
    ///
    /// // Using the singleton class:
    /// CSingletonClass::instance()->initialize();                         // Function initialize just an example!
    /// @endcode
    template<typename T>
    class CSingleton {
    protected:
        /// @brief Constructor
        ///
        /// This constructor is protected to prevent direct instantiation of the class.
        CSingleton() = default;

        /// @brief Copy constructor
        ///
        /// This constructor is deleted to prevent copying of the instance.
        CSingleton(const CSingleton &) = delete;

        /// @brief Copy assignment operator
        ///
        /// This operator is deleted to prevent assignment of the instance.
        CSingleton &operator=(const CSingleton &) = delete;

        /// @brief Destructor
        ///
        /// This destructor is virtual and does nothing, allowing derived classes to clean up if needed.
        virtual ~CSingleton() = default;

    public:
        /// @brief Get the instance of the Singleton class
        /// @return Instance of the Singleton class
        ///
        /// This function provides access to the single instance of the class.
        /// If the instance does not exist, it is created.
        static T *instance() {
            static T s_oInstance;
            return &s_oInstance;
        }
    };
}
