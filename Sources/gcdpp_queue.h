//
//  gcdpp_queue.h
//
//  Created by Sergey Sergeev on 6/12/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#ifndef gcdpp_queue_h
#define gcdpp_queue_h

#include "gcdpp_common.h"
#include "gcdpp_task.h"

namespace gcdpp
{
    class gcdpp_t_main_queue
    {
    private:
        
    protected:
        
        friend void gcdpp_dispatch_update_main_queue(void);
        
        std::string m_guid;
        std::queue<std::shared_ptr<gcdpp_t_i_task> > m_queue;
        
        void _Update(void);
        
    public:
        
        gcdpp_t_main_queue(const std::string& _guid);
        virtual ~gcdpp_t_main_queue(void);
        
        virtual void append_task(std::shared_ptr<gcdpp_t_i_task> _task);
    };
    
    
    class gcdpp_t_queue : public gcdpp_t_main_queue
    {
    private:
        
    protected:
        
        std::mutex m_mutex;
        std::thread m_thread;
        bool m_running;
        
        void _Thread(void);
        
    public:
        
        gcdpp_t_queue(const std::string& _guid);
        ~gcdpp_t_queue(void);
        
        void append_task(std::shared_ptr<gcdpp_t_i_task> _task);
    };
};


#endif
