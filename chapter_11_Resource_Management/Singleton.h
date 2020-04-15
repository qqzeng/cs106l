//
// Created by GEORGE-pc on 2020/3/19.
//

#ifndef CHAPTER_11_RESOURCE_MANAGEMENT_SINGLETON_H
#define CHAPTER_11_RESOURCE_MANAGEMENT_SINGLETON_H

namespace Singleton_V0 {

#include <cstdio>

    class Singleton
    {
    private:
        Singleton() { };
        ~Singleton() { };
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
        static Singleton instance;
    public:
        static Singleton& getInstance(){
            return instance;
        }
    };
    Singleton Singleton::instance;
};

namespace Singleton_V1 {

    #include <cstdio>

    class Singleton {
    public:
        static Singleton* getInstance();
    private:
        static Singleton *instance; // ... but they can be used here because
        Singleton();  // Clients cannot call this function; it's private
        ~Singleton(); // ... nor can they call this one
        Singleton(const Singleton& other);
        Singleton& operator=(const Singleton& other);
    };

    // maintain a object.
    Singleton* Singleton::instance = NULL;

    Singleton::Singleton() {
        std::cout << "Constructor is called." << std::endl;
    }

    Singleton::~Singleton() {
        std::cout << "Destructor is called." << std::endl;
    }

    Singleton *Singleton::getInstance() {
        if(Singleton::instance == NULL)
            Singleton::instance = new Singleton();
        return Singleton::instance;
    }
};


namespace Singleton_V2 {

#include <cstdio>

    class Singleton {
    public:
        static Singleton* getInstance();
    private:
        static Singleton *instance; // ... but they can be used here because
        Singleton();  // Clients cannot call this function; it's private
        ~Singleton(); // ... nor can they call this one
        Singleton(const Singleton& other);
        Singleton& operator=(const Singleton& other);

        // used to recycle the sole singleton instance.
        class Recycler {
        public:
            ~Recycler() {
                std::cout << "Recycler::Destructor is called." << std::endl;
                if (Singleton::instance != NULL)
                    delete Singleton::instance;
            }
        };
        static Recycler recycler;
    };

    // maintain a object.
    Singleton* Singleton::instance = NULL;

    Singleton::Singleton() {
        std::cout << "Constructor is called." << std::endl;
    }

    Singleton::~Singleton() {
        std::cout << "Destructor is called." << std::endl;
    }

    Singleton *Singleton::getInstance() {
        if(Singleton::instance == NULL)
            Singleton::instance = new Singleton();
        return Singleton::instance;
    }
};


namespace Singleton_V3 {

#include <pthread.h>
#include <cstdio>
    class Singleton {
    private:
        static Singleton *instance;

        Singleton() {
            pthread_mutex_init(&mutex, NULL);
        };
        static pthread_mutex_t mutex;
    public:
        static Singleton *getInstance();
        static bool releaseInstance();
    };

    Singleton *Singleton::instance = NULL;
    pthread_mutex_t Singleton::mutex;

    bool Singleton::releaseInstance() {
        if (Singleton::instance != NULL) {
            delete Singleton::instance;
            Singleton::instance = NULL;
            return true;
        }
        return false;
    }

    Singleton *Singleton::getInstance() {
        if (Singleton::instance == NULL) {
            pthread_mutex_lock(&mutex);
            if (Singleton::instance == NULL) {
                Singleton::instance = new Singleton;
            }
            pthread_mutex_unlock(&mutex);
        }

        return Singleton::instance;
    }
};

namespace Singleton_V4 {

#include <cstdio>

    class Singleton
    {
    private:
        Singleton() { };
        ~Singleton() { };
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
    public:
        static Singleton& getInstance()
        {
            static Singleton instance;
            return instance;
        }
    };
};

#endif //CHAPTER_11_RESOURCE_MANAGEMENT_SINGLETON_H
