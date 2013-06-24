//
//  gcdpp_task.h
//
//  Created by Sergey Sergeev on 6/13/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#ifndef gcdpp_task_h
#define gcdpp_task_h

#include "gcdpp_common.h"

template<unsigned int NUM>
struct apply_
{
    template<typename... F_ARGS, typename... T_ARGS, typename... ARGS>
    static void apply(std::function<void(F_ARGS... args)> _function, std::tuple<T_ARGS...> const& _targs,
                      ARGS... args)
    {
        apply_<NUM-1>::apply(_function, _targs, std::get<NUM-1>(_targs), args...);
    }
};

template<>
struct apply_<0>
{
    template<typename... F_ARGS, typename... T_ARGS, typename... ARGS>
    static void apply(std::function<void(F_ARGS... args)> _function, std::tuple<T_ARGS...> const&,
                      ARGS... args)
    {
        _function(args...);
    }
};

template<typename... F_ARGS, typename... T_ARGS>
void apply(std::function<void(F_ARGS... _fargs)> _function, std::tuple<T_ARGS...> const& _targs)
{
    apply_<sizeof...(T_ARGS)>::apply(_function, _targs);
}

class gcdpp_t_i_task
{
private:
    
protected:
    
public:
    
    gcdpp_t_i_task(void)
    {
 
    };
    
    virtual ~gcdpp_t_i_task(void)
    {

    };
    
    virtual void execute(void)
    {
        assert(false);
    };
};

template<class FUCTION, class... ARGS> class gcdpp_t_task : public gcdpp_t_i_task
{
protected:
    
    FUCTION m_function;
    std::tuple<ARGS...> m_args;
    
public:
    gcdpp_t_task(FUCTION _function, ARGS... _args)
    {
        m_function = _function;
        m_args = std::make_tuple(_args...);
    };
    
    ~gcdpp_t_task(void)
    {

    };
    
    void execute(void)
    {
        apply(m_function, m_args);
        //std::thread::id this_id = std::this_thread::get_id();
    };
};


#endif
