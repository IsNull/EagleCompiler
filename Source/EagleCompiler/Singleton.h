//
//  Singleton.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 10/10/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef EagleCompiler_Singleton_h
#define EagleCompiler_Singleton_h

template <typename C>
class Singleton
{
public:
    static C* instance ()
    {
        if (!_instance)
            _instance = new C ();
        return _instance;
    }
    virtual
    ~Singleton ()
    {
        _instance = 0;
    }
private:
    static C* _instance;
protected:
    Singleton () { }
};
template <typename C> C* Singleton <C>::_instance = 0;

#endif
