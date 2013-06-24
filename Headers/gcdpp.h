//
//  gcdpp.h
//  gcdpp
//
//  Created by Sergey Sergeev on 6/24/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#ifndef gcdpp_h
#define gcdpp_h

#include "../Sources/gcdpp_common.h"
#include "../Sources/gcdpp_queue.h"
#include "../Sources/gcdpp_task.h"

namespace gcdpp
{
    enum GCDPP_DISPATCH_QUEUE_PRIORITY
    {
        GCDPP_DISPATCH_QUEUE_PRIORITY_LOW = 1,
        GCDPP_DISPATCH_QUEUE_PRIORITY_DEFAULT,
        GCDPP_DISPATCH_QUEUE_PRIORITY_HIGH,
        GCDPP_DISPATCH_QUEUE_PRIORITY_MAX,
        GCDPP_DISPATCH_QUEUE_PRIORITY_MAIN
    };
    
    class gcdpp_impl
    {
    private:
        
    protected:
        
        friend void gcdpp_dispatch_init_main_queue(void);
        friend void gcdpp_dispatch_update_main_queue(void);
        friend std::shared_ptr<gcdpp_t_queue> gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY _priority);
        friend std::shared_ptr<gcdpp_t_main_queue> gcdpp_dispatch_get_main_queue(void);
        
        template<class... ARGS>
        friend void gcdpp_dispatch_async(std::shared_ptr<gcdpp_t_main_queue> _queue, std::function<void(ARGS... args)> _function, ARGS... args);
        
        std::shared_ptr<gcdpp_t_main_queue> m_mainQueue;
        std::shared_ptr<gcdpp_t_queue> m_poolQueue[gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY_MAX];
        
        static std::shared_ptr<gcdpp_impl> instance(void);
        
        std::shared_ptr<gcdpp_t_queue> gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY _priority);
        std::shared_ptr<gcdpp_t_main_queue> gcdpp_dispatch_get_main_queue(void);
        
        template<class... ARGS>
        void gcdpp_dispatch_async(std::shared_ptr<gcdpp_t_main_queue> _queue, std::function<void(ARGS... args)> _function, ARGS... args);
        
    public:
        
        gcdpp_impl(void);
        ~gcdpp_impl(void);
        
    };
    
    inline void gcdpp_dispatch_init_main_queue(void)
    {
        gcdpp::gcdpp_impl::instance();
    };
    
    inline void gcdpp_dispatch_update_main_queue(void)
    {
        assert(gcdpp::gcdpp_impl::instance()->m_mainQueue != nullptr);
        gcdpp::gcdpp_impl::instance()->m_mainQueue->_Update();
    };
    
    inline std::shared_ptr<gcdpp_t_queue> gcdpp_dispatch_get_global_queue(gcdpp::GCDPP_DISPATCH_QUEUE_PRIORITY _priority)
    {
        return gcdpp::gcdpp_impl::instance()->gcdpp_dispatch_get_global_queue(_priority);
    };
    
    inline std::shared_ptr<gcdpp_t_main_queue> gcdpp_dispatch_get_main_queue(void)
    {
        return gcdpp::gcdpp_impl::instance()->gcdpp_dispatch_get_main_queue();
    };
    
    template<class... ARGS>
    void gcdpp_impl::gcdpp_dispatch_async(std::shared_ptr<gcdpp_t_main_queue> _queue, std::function<void(ARGS... args)> _function, ARGS... args)
    {
        std::shared_ptr<gcdpp_t_task<std::function<void(ARGS...)>, ARGS... > > task_ = std::make_shared<gcdpp_t_task<std::function<void(ARGS...)>, ARGS... > >(_function, std::forward<ARGS>(args)...);
        _queue->append_task(task_);
    };
    
    template<class... ARGS>
    void gcdpp_dispatch_async(std::shared_ptr<gcdpp_t_main_queue> _queue, std::function<void(ARGS... args)> _function, ARGS... args)
    {
        gcdpp_impl::instance()->gcdpp_dispatch_async(_queue, _function, std::forward<ARGS>(args)...);
    };
};

#endif
